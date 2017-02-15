#include "Cryptography/CryptographyMgr.h"
#include "Server/WorldSession.h"

void WorldSession::HandleClientVersion(WorldPacket& packet)
{
    QStringList ip = GetIp().split(".");

    WorldPacket data(SMSG_CLIENT_IP);

    for (quint8 i = 0; i < ip.size(); ++i)
        data << (quint8) ip.at(i).toUInt();

    SendPacket(data);

    quint8 version, change;
    quint16 revision;
    QString build;

    packet >> version;
    packet >> revision;
    packet >> change;
    build =  packet.ReadString();

    QString clientVersion = QString(QString::number(version) + "." + QString::number(revision) + "." + QString::number(change));
    SendClientVersionResult(clientVersion, sAuthConfig->GetString("AcceptClientVersion"));
}

void WorldSession::SendClientVersionResult(QString clientVersion, QString expectedVersion)
{
    QStringList version = expectedVersion.split(".");

    WorldPacket data(SMSG_CLIENT_VERSION_RESULT);
    data << (quint8)(clientVersion == expectedVersion);
    data << (quint8)version.at(0).toUShort();
    data << (quint16)version.at(1).toUShort();
    data << (quint8)version.at(2).toUShort();
    data.WriteString("-1");
    SendPacket(data);
}

void WorldSession::HandlePublicKeyRequest(WorldPacket& /*packet*/)
{
    QByteArray publicKey = sCryptographyMgr->GetPublicKey();

    WorldPacket data(SMSG_PUBLIC_KEY_RESULT);
    data << quint64(0x8000000000000000); // Salt
    data.WriteRawBytes(publicKey);
    SendPacket(data);
}

void WorldSession::HandleClientAuthToken(WorldPacket& packet)
{
    quint32 tokenLength;
    packet >> tokenLength;

    QString token = packet.ReadString((quint8) tokenLength);
    QSqlQuery result = sAuthDatabase->Query(SELECT_ACCOUNT_BY_TOKEN, QVariantList() << token);

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);

    if (!result.first())
    {
        data << (quint8) LOGIN_RESULT_ERROR_INVALID_LOGIN;
        SendPacket(data);

        return;
    }

    m_accountInfos.id               = result.value("account_id").toULongLong();
    m_accountInfos.username         = result.value("username").toString();
    m_accountInfos.pseudo           = result.value("pseudo").toString();
    m_accountInfos.gmLevel          = result.value("gm_level").toUInt();
    m_accountInfos.subscriptionTime = result.value("subscription_time").toUInt();

    data << (quint8) LOGIN_RESULT_SUCCESS;

    // if ban (=> ban check per realm?)
    // int banDuration in minutes

    data.StartBlock<quint16>();
    {
        // block number
        data << quint8(1);
        {
            data << quint8(0);      // block id
            data << quint32(6);     // block start

            data << quint8(0);      // block id

            data << quint64(result.value("account_id").toULongLong());
            data << quint32(1); // m_subscriptionLevel
            data << quint32(0); // antiAddictionLevel
            data << quint64(m_accountInfos.subscriptionTime);

            // Admin rights => TODO
            for (quint8 i = 1; i <= MAX_ADMIN_RIGHT; ++i)
                data << quint32(0);

            data.WriteString(m_accountInfos.pseudo);

            data << (quint32) COMMUNITY_FR; // m_accountCommunity => TODO Community in accounts table

            // Account data (flags) TODO
            data << quint16(0); // flagCount
        }
    }
    data.EndBlock<quint16>();

    SendPacket(data);

    SendWorldSelectResult(true);

    // Send SMSG_FREE_COMPANION_BREED_ID

    SendClientCalendarSync();
    SendSystemConfiguration();
    SendAdditionalSlotsUpdate();
    SendCharactersList();
}

// TODO ! An other token for reconnect????
void WorldSession::HandleAuthTokenRequest(WorldPacket& packet)
{
    quint64 address;
    quint16 languageLength;

    packet >> address;
    packet >> languageLength;
    QString language = packet.ReadString(languageLength);

    // Hardcoded token for now
    QString token = "74aed5af0c8551977d418cee34fa394bfd398565ba7b018d74c59999449ca";
    qDebug() << "Received token : " << token;

    WorldPacket data(MSG_AUTH_TOKEN);
    data.WriteString(token, STRING_SIZE_4);
    SendPacket(data);

    SendCompanionList();
}
