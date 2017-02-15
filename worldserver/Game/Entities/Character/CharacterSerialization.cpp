#include "Character.h"

void Character::SerializeGuid(WorldPacket& data)
{
    data << GetGuid();
}

void Character::SerializeIdentity(WorldPacket& data)
{
    data << (quint8) 0; // idType
    data << GetSession()->GetAccountInfos().id;
}

void Character::SerializeName(WorldPacket& data)
{
    data.WriteString(GetName(), STRING_SIZE_2);
}

void Character::SerializeBreed(WorldPacket& data)
{
    data << GetBreed();
}

void Character::SerializeHP(WorldPacket& data)
{
    data << GetHealth();
}

void Character::SerializePosition(WorldPacket& data)
{
    data << GetPositionX();
    data << GetPositionY();
    data << GetPositionZ();
    data << GetInstanceId();
    data << GetDirection();

    // dimBagPosition
    data << (quint8) 1;
    {
        data << quint32(0); //x
        data << quint32(0); //y
        data << quint16(0); //z
        data << quint16(0); //instanceid
    }
}

void Character::SerializeAppearance(WorldPacket& data)
{
    data << GetGender();
    data << GetSkinColor();
    data << GetHairColor();
    data << GetPupilColor();
    data << GetSkinColorFactor();
    data << GetHairColorFactor();
    data << GetClothIndex();
    data << GetFaceIndex();
    data << qint16(-1); //currentTitle
}

void Character::SerializeShortcutInventories(WorldPacket& data)
{
    data << quint16(8);

    for (quint8 i = 0; i < 4; ++i)
    {
        data << quint8(0); // type
        data << quint16(0); // size
    }

    for (quint8 i = 0; i < 4; ++i)
    {
        data << quint8(1); // type
        data << quint16(0); // size
    }
}

void Character::SerializeEmoteInventory(WorldPacket& data)
{
    data << quint16(1); // Size
    data << quint32(20015); // EmoteId
}

void Character::SerializeLandmarkInventory(WorldPacket& data)
{
    data << quint16(1); // Size
    data << quint8(30); // LandmarkId
}

void Character::SerializeDiscoveredItems(WorldPacket& data)
{
    data << quint16(1); // ZaapsCount
    data << quint32(19249);

    data << quint16(0); // dragosCount
    data << quint16(0); // boatscount
    data << quint16(0); // cannonCount
    data << quint16(0); // phoenixCount
    data << qint32(-1); // selectedPhoenix
}

void Character::SerializeSpellInventory(WorldPacket& data)
{
    data << quint16(0); // spellInventoryVersion
    data << quint32(0); // lockedSpellId

    data << quint16(3); // Spell size

    // Spell 0
    data << quint8(1); // type
    data << quint64(29107958004580983); // uid
    data << quint32(3692); // spellId
    data << quint16(0); // level
    data << quint64(0); // Xp
    data << quint8(0); // skillSize

    // Spell 1
    data << quint8(1); // type
    data << quint64(29107958004580985); // uid
    data << quint32(3690); // spellId
    data << quint16(0); // level
    data << quint64(0); // Xp
    data << quint8(0); // skillSize

    // Spell 2
    data << quint8(1); // type
    data << quint64(29107958004580984); // uid
    data << quint32(3691); // spellId
    data << quint16(0); // level
    data << quint64(0); // Xp
    data << quint8(0); // skillSize

    data << quint8(0); // needSpellRestat
}

void Character::SerializeInventories(WorldPacket& data)
{
    data << quint16(0); // questInventory size
    data << quint16(0); // temporaryInventory size
    data << quint16(0); // cosmeticsInventory size
    data << quint16(0); // petCosmeticsInventory size
}

void Character::Character::SerializeEquipmentInventory(WorldPacket& data)
{
    data << quint16(0); // Count
}

void Character::SerializeBags(WorldPacket& data)
{
    data << quint16(2); // Bags count

    // Bag 0
    data << quint64(29107958004580982); // uid
    data << quint32(2603); // refId
    data << quint8(1); // position
    data << quint16(4); // maxSize
    data << quint16(0); // item count

    // Bag 1
    data << quint64(29107958004580979); // uid
    data << quint32(2175); // refId
    data << quint8(0); // position
    data << quint16(30); // maxSize
    data << quint16(0); // item count
}

void Character::SerializeBreedSpecific(WorldPacket& data)
{
    data << quint8(0); // hasOsaSpecific
}

void Character::SerializeSkillInventory(WorldPacket& data)
{
    QList<quint32> skills;
    skills << 68 << 69 << 1 << 70 << 2 << 71 << 3 << 4 << 5
           << 6 << 7 << 37 << 76 << 42 << 8 << 77 << 9
           << 72 << 73 << 14 << 74 << 75 << 62 << 61 << 60;

    data << quint16(skills.size()); // SkillInventory size

    for (quint8 i = 0; i < skills.size(); ++i)
    {
        data << quint32(skills.at(i)); // refId
        data << quint16(0); // level
        data << quint64(0); // xp
    }
}

void Character::SerializeCraft(WorldPacket& data)
{
    QList<quint32> crafts;
    crafts << 72 << 71 << 73 << 64 << 75 << 74;

    data << quint16(crafts.size()); // Craft count

    for (quint8 i = 0; i < crafts.size(); ++i)
    {
        data << quint32(crafts.at(i)); // craftId
        data << quint64(0); // craftXp
        data << quint8(0); // hasPlantationCounter
        data << quint8(0); // hasNonDestructiveCollectCounter
        data << quint8(0); // hasdestructiveCollectCounter
        data << quint8(0); // hasRecipeCounter
        data << quint16(0); // rawLearnedRecipes size
    }
}

void Character::SerializeAptitudeInventory(WorldPacket& data)
{
    QList<quint16> aptitudes;
    aptitudes << 3 << 4 << 167 << 168 << 169 << 170;

    data << quint16(aptitudes.size()); // Count

    for (quint8 i = 0; i < aptitudes.size(); ++i)
    {
        data << quint16(aptitudes.at(i)); // referenceId
        data << quint16(0); // level
        data << quint16(0); // wonLevel
    }

    data << quint16(2); // availablePointsArray

    data << quint8(1); // aptitudeType
    data << quint32(0); // availablePoints
    data << quint32(0); // wonPoints

    data << quint8(0); // aptitudeType
    data << quint32(0); // availablePoints
    data << quint32(0); // wonPoints

    data << quint16(23); // Version
}

void Character::SerializeRunningEffects(WorldPacket& data)
{
    data << quint8(0); // hasInFightData
    data << quint8(1); // hasOutFightData
        data << quint16(0); // size
}

void Character::SerializeDimensionalBagForLocalClient(WorldPacket& data)
{
    data << GetGuid();
    data.WriteString(GetName(), STRING_SIZE_2);
    data << GetGuildId();
    data << quint8(9); // Rooms count

    // Bag rooms 0
    data << quint8(0); // Layout position
    data << quint16(0); // InteractiveElements count
    data << quint8(0); // hasRoomSpecificData
    data << quint8(1); // primaryGemLocked
    data << quint32(4262); // primaryGemitemRefId
    data << quint64(29107958004580981); // primaryGemUniqueId
    data << qint32(-1); // secondaryGemitemRefId
    data << qint64(-1); // secondaryGemUniqueId

    for (quint8 i = 1; i < 9; ++i)
    {
        data << quint8(i); // Layout position
        data << quint16(0); // InteractiveElements count
        data << quint8(0); // hasRoomSpecificData
        data << quint8(0); // primaryGemLocked
        data << qint32(-1); // primaryGemitemRefId
        data << qint64(-1); // primaryGemUniqueId
        data << qint32(-1); // secondaryGemitemRefId
        data << qint64(-1); // secondaryGemUniqueId
    }

    data << quint32(408); // CustomViewModelId
    data << quint8(1); // HasWallet
    data << quint32(0); // cash
    data << quint8(0); // dimensionalBagLocked

    data << quint16(1); // groupeEntriesSize
    data << quint8(0); // groupType
    data << quint8(1); // groupRights

    data << quint16(0); // IndividualEntriesSize
}

void Character::SerializeChallenges(WorldPacket& data)
{
    data << quint8(0); // hasCurrentScenarii
    data << quint8(1); // hasCurrentChallengeInfo
    data << quint16(0); // challenges size
    data << quint16(0); // pastScenarii
}

void Character::SerializeXP(WorldPacket& data)
{
    data << GetXP();
}

void Character::SerializeXPCharacteristics(WorldPacket& data)
{
    data << GetXPFreePoints();
    data << quint16(6); // xpBonusPoints size

    QList<quint8> characId;
    characId << 40 << 37 << 39 << 36 << 41 << 38;

    for (quint8 i = 0; i < characId.size(); ++i)
    {
        data << quint8(characId.at(i));
        data << quint16(0); // nbPoint
    }

    data << quint16(6); // m_characteristicBonusPoints size
    for (quint8 i = 0; i < characId.size(); ++i)
    {
        data << quint8(characId.at(i));
        data << quint16(0); // nbPoint
    }

    data << GetXPGauge();
}

void Character::SerializeTitles(WorldPacket& data)
{
    data << quint16(0); // availableTitlesCount
}

void Character::SerializeCitizenPoint(WorldPacket& data)
{
    data << quint16(0); // nationCitizenScoresSize
    data << quint16(0); // offendedNationsSize
}

void Character::SerializePasseportInfo(WorldPacket& data)
{
    data << quint8(0); // isPassportActive
}

void Character::SerializeSocialStates(WorldPacket& data)
{
    data << quint8(0); // afkState
    data << quint8(0); // dndstate
}

void Character::SerializePet(WorldPacket& data)
{
    data << quint8(0); // hasPet
    data << quint8(0); // hasMount
}

void Character::SerializeAchievements(WorldPacket& data)
{
    data << quint16(0);
    /*
    data.StartBlock<quint16>();
    {
        data << quint32(3); // version
        data << quint8(0); // history size
        data << quint32(0); // nbVariables
        {
            data << quint32(313);
            data << quint64(1);

            data << quint32(220);
            data << quint64(1);
        }
        data << quint32(0); // nbAchievements
        data << quint32(0); // nbObjectives
        data << quint8(0); // numFollowed size
    }
    data.EndBlock<quint16>();*/
}

void Character::SerializeAccountInformation(WorldPacket& data)
{
    data << quint16(95); // adminRights size
    for (quint8 i = 0; i < 95; ++i)
        data << quint32(0); // adminRight

    data << quint32(1); // subscriptionLevel
    data << quint32(0); // forcedSubscriptionLevel
    data << quint32(0); // antiAddictionLevel
    data << quint64(0); // sessionStartTime (current timestamp ?)
    data << quint16(0); // additionalRights size

    data << quint8(0); // additionalSlots
    data << quint8(0); // vaultUpgrades
}

void Character::SerializeLockToClient(WorldPacket& data)
{
    data << quint16(1); // Locks size
    data << quint32(98); // lockId
    data << quint64(0); // lockDate
    data << quint64(1421755200000); // unlockDate
    data << quint32(0); // currentLockValue
    data << quint64(0); // currentLockValueLastChange
}

void Character::SerializeDimensionalBagViewsInventory(WorldPacket& data)
{
    QList<quint32> views;
    views << 510 << 835 << 838 << 478 << 406 << 509 << 507 << 834 << 837 << 840
          << 405 << 480 << 408 << 508 << 467 << 833 << 373 << 836 << 839 << 479
          << 19 << 410;

    data << quint16(views.size()); // Views Size
    for (quint8 i = 0; i < views.size(); ++i)
        data << quint32(views.at(i));
}

void Character::SerializePersonalEffects(WorldPacket& data)
{
    QList<quint32> guildEffects;
    guildEffects << 93962 << 93968 << 93598 << 93960 << 93966 << 93589
                 << 93608 << 93970 << 93963 << 93969;

    data << quint16(guildEffects.size()); // guildEffects size
    for (quint8 i = 0; i < guildEffects.size(); ++i)
        data << quint32(guildEffects.at(i));

    data << quint16(0); // havenWorldEffects size
    data << quint16(0); // antiAddictionEffects size
}

void Character::SerializeAntiAddiction(WorldPacket& data)
{
    data << quint8(0); // hasAddictionData
}

void Character::SerializeWorldProperties(WorldPacket& data)
{
    data << quint8(0); // hasProperties
}

void Character::SerializeVisibility(WorldPacket& data)
{
    data << quint8(1); // Visible
}

void Character::SerializeOccupation(WorldPacket& data)
{
    data << quint8(0); // hasOccupation
}

void Character::SerializeAptitudeBonusInventory(WorldPacket& data)
{
    data << quint8(1); // hasOptional
    data << quint16(0); // bonus size

    QList<quint32> avaiablePoints;
    avaiablePoints << 6 << 2 << 3 << 4 << 5;

    data << quint16(avaiablePoints.size()); // availablePoints size
    for (quint8 i = 0; i < avaiablePoints.size(); ++i)
    {
        data << quint32(avaiablePoints.at(i)); // categoryId
        data << quint16(0);
    }
}

void Character::SerializeNationId(WorldPacket& data)
{
    data << quint32(0);
}

void Character::SerializeNationSynchro(WorldPacket& data)
{
    data << quint64(0); // Ranks
    data << quint64(0); // Jobs
    data << quint64(0); // Votedate
    data << quint8(0); // Government Opionion => TODO : aWj.java
    data << quint8(0); // IsCandidate (bool)

    data << quint8(0); // pvpState
    data << quint64(0); // pvpDate
    data << quint8(0); // pvpRank
}

void Character::SerializeGuildLocalInfo(WorldPacket& data)
{
    data << quint16(0); // Guild info
    data << quint32(66); // havenWorldId
    data << float(0.0f); // moderationBonusLearningFactor
}

void Character::SerializeNationPvpMoney(WorldPacket& data)
{
    data << quint64(0); // pvpMoneyAmount
    data << quint64(0); // dailyPvpMoneyAmount
}



