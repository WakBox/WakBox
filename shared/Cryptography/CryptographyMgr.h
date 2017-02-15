#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QtCore>

#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>

#include "Utils/Singleton.h"

class CryptographyMgr : public Singleton<CryptographyMgr>
{
public:
    CryptographyMgr();
    ~CryptographyMgr();

    bool Initialize();
    bool GenerateKeyPair();
    bool LoadKeyPair();

    QByteArray GetPublicKey() { return m_publicKey; }
    QByteArray Decrypt(QByteArray buffer);

private:
    CryptoPP::InvertibleRSAFunction m_privateKey;
    QByteArray m_publicKey;
};

#define sCryptographyMgr CryptographyMgr::Instance()

#endif
