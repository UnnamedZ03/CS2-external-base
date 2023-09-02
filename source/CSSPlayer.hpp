#pragma once

/* @NOTE: I retrieved this with a little reversing, nothing complicated and I regularly post new ones. */
constexpr DWORD64 s_dwEntityList_Offset = 0x1679C38;
constexpr DWORD64 viewmatrix_Offset = 0x1713CF0;
constexpr DWORD64 localplayer_Offset = 0x1713348;

/* @NOTE: You can obtain such offsets by using source2gen */
constexpr DWORD64 s_dwPawnIsAlive_Offset = 0x804;
constexpr DWORD64 s_dwPawnHealth_Offset = 0x808;
constexpr DWORD64 s_dwPlayerPawn_Offset = 0x5dc;
constexpr DWORD64 s_dwSanitizedName_Offset = 0x720;
constexpr DWORD64 s_Position_Offset = 0x12AC;
constexpr DWORD64 s_teamnum_Offset = 0x3bf;
constexpr DWORD64 s_bIsLocalPlayerController_Offset = 0x6A0;

inline DWORD64 g_dwEntList = 0;
inline DWORD64 client = 0;

class C_BaseEntity;
class CEntityIdentity
{
public:
    C_BaseEntity* m_pPrevByClass()
    {
        C_BaseEntity* pPrevByClass1 = driver::read<C_BaseEntity*>((DWORD64)(this) + 0x68);
        C_BaseEntity* pPrevByClass = driver::read<C_BaseEntity*>((DWORD64)pPrevByClass1);
        
        return pPrevByClass;
    }

    C_BaseEntity* m_pNextByClass()
    {
        C_BaseEntity* pNextByClass1 = driver::read<C_BaseEntity*>((DWORD64)(this) + 0x70);
        C_BaseEntity* pNextByClass = driver::read<C_BaseEntity*>((DWORD64)pNextByClass1);

        return pNextByClass;
    }

    std::string m_designerName()
    {
        std::string sBuffer = { };
        sBuffer.resize(32);

        DWORD64 pDesignerName = driver::read<DWORD64>((DWORD64)(this) + 0x20);
        if (!pDesignerName)
            return { };

        sBuffer = driver::read_str(pDesignerName);

        return sBuffer;
    }
};

class C_BaseEntity
{
public:
    static C_BaseEntity* GetBaseEntity(int nIdx)
    {
        std::uint64_t ListEntry = driver::read<std::uint64_t>(g_dwEntList + (8 * (nIdx & 0x7FFF) >> 9) + 16);
        if (!ListEntry)
            return 0;
        C_BaseEntity* ListEntry2 = driver::read<C_BaseEntity*>((ListEntry + 120 * (nIdx & 0x1FF)));

        return ListEntry2;
    }
public:
    CEntityIdentity* m_pEntityIdentity()
    {
        CEntityIdentity* a = driver::read<CEntityIdentity*>((DWORD64)(this) + 0x10);
        return a;
    }
};

class C_CSPlayerPawn
{
public:
    static C_CSPlayerPawn* GetPlayerPawn(std::uint32_t uHandle)
    {
        std::uint64_t ListEntry = driver::read<std::uint64_t>(g_dwEntList + 0x8 * ((uHandle & 0x7FFF) >> 9) + 16);
        if (!ListEntry)
            return 0;

        C_CSPlayerPawn* pCSPlayerPawn = driver::read<C_CSPlayerPawn*>(ListEntry + 120 * (uHandle & 0x1FF));

        return pCSPlayerPawn;
    }
};

class CCSPlayerController : public C_BaseEntity
{
public:
    std::string m_sSanitizedPlayerName()
    {
        std::string sBuffer = { };
        sBuffer.resize(32);

        DWORD64 SanitizedPlayerName = driver::read<DWORD64>(((DWORD64)(this) + 0x720));
        if (!SanitizedPlayerName)
            return { };

        sBuffer = driver::read_str(SanitizedPlayerName);
        return sBuffer;
    }

    int Teamnum()
    {
        int team = driver::read<int>((DWORD64)(this) + s_teamnum_Offset);
        return team;
    }

    int m_iPawnHealth()
    {
        DWORD64 health = driver::read<DWORD64>((DWORD64)(this) + s_dwPawnHealth_Offset);
        return health;
    }

    vec3 pos(C_CSPlayerPawn* pawn)
    {
        return driver::read<vec3>((DWORD64)pawn + 0x12AC);
    }


    bool m_bIsLocalPlayerController()
    {
        return driver::read<bool>((DWORD64)(this) + s_bIsLocalPlayerController_Offset);
    }

    C_CSPlayerPawn* m_hPlayerPawn()
    {
        std::uint32_t playerpawn = driver::read<std::uint32_t>((DWORD64)(this) + s_dwPlayerPawn_Offset);
        return C_CSPlayerPawn::GetPlayerPawn(playerpawn);
    }
};
