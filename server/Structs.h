/*
*  Version: MPL 1.1
*
*  The contents of this file are subject to the Mozilla Public License Version
*  1.1 (the "License"); you may not use this file except in compliance with
*  the License. You may obtain a copy of the License at
*  http://www.mozilla.org/MPL/
*
*  Software distributed under the License is distributed on an "AS IS" basis,
*  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
*  for the specific language governing rights and limitations under the
*  License.
*
*  The Original Code is the YSI 2.0 SA:MP plugin.
*
*  The Initial Developer of the Original Code is Alex "Y_Less" Cole.
*  Portions created by the Initial Developer are Copyright (C) 2008
*  the Initial Developer. All Rights Reserved.
*
*  Contributor(s):
*
*  Peter Beverloo
*  Marcus Bauer
*  MaVe;
*  Sammy91
*  Incognito
*
*  Special Thanks to:
*
*  SA:MP Team past, present and future
*/

#pragma once

#include "Shared/Network/BitStream.h"
#include "PacketPriority.h"
#include "CVector.h"
#include "Types.h"

#include "GDK/sampgdk.h"

#include <map>
#include <cstdio>

class CGangZonePool;
#define PAD(a, b)			char a[b]

// SA-MP defines
//#define	MAX_PLAYERS					500
//#define	MAX_OBJECTS					1000
//#define	MAX_GANG_ZONES				1024
//#define	MAX_PICKUPS					4096
//#define	MAX_TEXT_DRAWS				2048
//#define	MAX_PLAYER_TEXT_DRAWS		256
//#define	MAX_VEHICLES				2000
#define	MAX_ATTACHED_OBJECTS		10
//#define	MAX_PLAYER_NAME				24
//#define	MAX_3DTEXT_GLOBAL			1024
//#define	MAX_3DTEXT_PLAYER			1024
//#define	MAX_MENUS					128
//#define	INVALID_PLAYER_ID			65535
#define	MAX_FILTER_SCRIPTS			16
/*
#define WEAPON_BRASSKNUCKLE				1
#define WEAPON_GOLFCLUB					2
#define WEAPON_NITESTICK				3
#define WEAPON_KNIFE					4
#define WEAPON_BAT						5
#define WEAPON_SHOVEL					6
#define WEAPON_POOLSTICK				7
#define WEAPON_KATANA					8
#define WEAPON_CHAINSAW					9
#define WEAPON_DILDO					10
#define WEAPON_DILDO2					11
#define WEAPON_VIBRATOR					12
#define WEAPON_VIBRATOR2				13
#define WEAPON_FLOWER					14
#define WEAPON_CANE						15
#define WEAPON_GRENADE					16
#define WEAPON_TEARGAS					17
#define WEAPON_MOLTOV					18
#define WEAPON_COLT45					22
#define WEAPON_SILENCED					23
#define WEAPON_DEAGLE					24
#define WEAPON_SHOTGUN					25
#define WEAPON_SAWEDOFF					26
#define WEAPON_SHOTGSPA					27
#define WEAPON_UZI						28
#define WEAPON_MP5						29
#define WEAPON_AK47						30
#define WEAPON_M4						31
#define WEAPON_TEC9						32
#define WEAPON_RIFLE					33
#define WEAPON_SNIPER					34
#define WEAPON_ROCKETLAUNCHER			35
#define WEAPON_HEATSEEKER				36
#define WEAPON_FLAMETHROWER				37
#define WEAPON_MINIGUN					38
#define WEAPON_SATCHEL					39
#define WEAPON_BOMB						40
#define WEAPON_SPRAYCAN					41
#define WEAPON_FIREEXTINGUISHER			42
#define WEAPON_CAMERA					43
#define WEAPON_NIGHTVISION              44
#define WEAPON_INFRARED              	45
#define WEAPON_PARACHUTE				46
#define WEAPON_VEHICLE					49
#define WEAPON_DROWN					53
#define WEAPON_COLLISION				54

#define PLAYER_STATE_NONE						(0)
#define PLAYER_STATE_ONFOOT						(1)
#define PLAYER_STATE_DRIVER						(2)
#define PLAYER_STATE_PASSENGER					(3)
#define PLAYER_STATE_EXIT_VEHICLE				(4) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER		(5) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER	(6) // (used internally)
#define PLAYER_STATE_WASTED						(7)
#define PLAYER_STATE_SPAWNED					(8)
#define PLAYER_STATE_SPECTATING					(9)
*/
#define AFK_ACCURACY					1500

typedef int                 INT;
typedef unsigned int        UINT;

enum CON_VARTYPE { CON_VARTYPE_FLOAT, CON_VARTYPE_INT, CON_VARTYPE_BOOL, CON_VARTYPE_STRING };

#define CON_VARFLAG_DEBUG		1
#define CON_VARFLAG_READONLY	2
#define CON_VARFLAG_RULE		4	// Gets sent with a RULES query responce

typedef void(*VARCHANGEFUNC)();

struct ConsoleVariable_s
{
#pragma pack( 1 )
	CON_VARTYPE VarType;
	DWORD VarFlags;
	void* VarPtr;
	VARCHANGEFUNC VarChangeFunc;
};

#pragma pack(push, 1)
typedef struct Text3DLabels_t  // size 0x21
{
	char* text;                                     // + 0x00
	uint color;                         // + 0x04
	float posX;                                     // + 0x08
	float posY;                                     // + 0x0C
	float posZ;                                     // + 0x10
	float drawDistance;                     // + 0x14
	bool useLineOfSight;            // + 0x18
	int virtualWorld;                  // + 0x19
	ushort attachedToPlayerID;    // + 0x1D
	ushort attachedToVehicleID;   // + 0x1F
} C3DText;
#pragma pack(pop)

#pragma pack(push, 1)
class C3DTextPool
{
public:
	BOOL                    m_bIsCreated[MAX_3DTEXT_GLOBAL];
	C3DText					m_TextLabels[MAX_3DTEXT_GLOBAL];
};
#pragma pack(pop)

#pragma pack(push, 1)
class CPlayerText3DLabels // size 0x9802
{
public:
	C3DText				TextLabels[MAX_3DTEXT_PLAYER];	// + 0x0000
	BOOL				isCreated[MAX_3DTEXT_PLAYER];	// + 0x8400
	BYTE				unknown9800[MAX_3DTEXT_PLAYER];				// + 0x9400
	WORD				ownerID;
};
#pragma pack(pop)

#pragma pack(push, 1)
class CAimSyncData
{
public:
	BYTE			byteCameraMode;			// 0
	CVector			vecFront;				// 1 - 13
	CVector			vecPosition;			// 13 - 25
	float			fZAim;					// 25 - 29
	BYTE			byteWeaponState : 6;	// 29
	BYTE			byteCameraZoom : 2;		// 29
	BYTE			unk;					// 30 - 31
	WORD			wCameraObject;			// 31 - 33
	WORD			wCameraVehicle;			// 33 - 35
	WORD			wCameraPlayer;			// 35 - 37
	WORD			wCameraActor;			// 37 - 39
	// Size = 39
};
#pragma pack(pop)

class CVehicleSyncData
{
public:
	WORD			wVehicleId;				// 0x001F - 0x0021
	WORD			wUDAnalog;				// 0x0021 - 0x0023
	WORD			wLRAnalog;				// 0x0023 - 0x0025
	WORD			wKeys;					// 0x0025 - 0x0027
	float			fQuaternionAngle;		// 0x0027 - 0x002B
	CVector			vecQuaternion;			// 0x002B - 0x0037
	CVector			vecPosition;			// 0x0037 - 0x0043
	CVector			vecVelocity;			// 0x0043 - 0x004F
	float			fHealth;				// 0x004F - 0x0053
	BYTE			bytePlayerHealth;		// 0x0053 - 0x0054
	BYTE			bytePlayerArmour;		// 0x0054 - 0x0055
	BYTE			bytePlayerWeapon;		// 0x0055 - 0x0056
	BYTE			byteSirenState;			// 0x0056 - 0x0057
	BYTE			byteGearState;			// 0x0057 -	0x0058
	WORD			wTrailerID;				// 0x0058 - 0x005A
	union									// 
	{
		WORD			wHydraReactorAngle[2];
		float           fTrainSpeed;
	};
	// Size = 63
};

class CPassengerSyncData
{
public:
	WORD			wVehicleId;				// 0x005E - 0x0060
	BYTE			byteSeatFlags : 7;
	BYTE			byteDriveBy : 1;
	BYTE			bytePlayerWeapon;		// 0x0061 - 0x0062
	BYTE			bytePlayerHealth;		// 0x0062 - 0x0063
	BYTE			bytePlayerArmour;		// 0x0063 - 0x0064
	WORD			wUDAnalog;				// 0x0064 - 0x0066
	WORD			wLRAnalog;				// 0x0066 - 0x0068
	WORD			wKeys;					// 0x0068 - 0x006A
	CVector			vecPosition;			// 0x006A - 0x0076
	// Size = 24
};

class CSyncData
{
public:
	WORD			wUDAnalog;				// 0x0076 - 0x0078
	WORD			wLRAnalog;				// 0x0078 - 0x007A
	WORD			wKeys;					// 0x007A - 0x007C
	CVector			vecPosition;			// 0x007C - 0x0088
	float			fQuaternion[4];			// 0x0088 - 0x008C
	BYTE			byteHealth;				// 0x0098 - 0x0099
	BYTE			byteArmour;				// 0x0099 - 0x009A
	BYTE			byteWeapon;				// 0x009A - 0x009B
	BYTE			byteSpecialAction;		// 0x009B - 0x009C
	CVector			vecVelocity;			// 0x009C - 0x00A8
	CVector			vecSurfing;				// 0x00A8 - 0x00B4
	WORD			wSurfingInfo;			// 0x00B4 - 0x00B6
	union
	{
		DWORD		dwAnimationData;		// 0x00B6 - 0x00BA
		struct
		{
			WORD	wAnimIndex;
			WORD	wAnimFlags;
		};
	};
	// Size = 68
};

class CUnoccupiedSyncData // size 0x43
{
public:
	WORD wVehicleID;				// + 0x0000
	BYTE bytePassengerSlot;			// + 0x0002
	CVector vecRool;				// + 0x0003
	CVector vecDirection;			// + 0x000F
	CVector vecPosition;			// + 0x001B
	CVector vecVelocity;			// + 0x0027
	CVector vecTurnVelocity;		// + 0x0033
	float fHealth;					// + 0x003F
};

class CSpectatingSyncData		// size 0x12
{
public:
	WORD		wLeftRightKeysOnSpectating;				// + 0x0000
	WORD		wUpDownKeysOnSpectating;				// + 0x0002
	WORD		wKeysOnSpectating;						// + 0x0004
	CVector		vecPosition;							// + 0x0006
};

class CTrailerSyncData // size 0x36 = 54
{
public:
	WORD wTrailerID;				// + 0x0000
	CVector	vecRoll;				// + 0x0002
	CVector vecDirection;			// + 0x000E
	CVector vecPosition;			// + 0x001A
	CVector vecVelocity;			// + 0x0026
	DWORD pad;
};

class CAttachedObject // sizeof = 52 - 0x34
{
public:
	int				iModelID;
	int				iBoneiD;
	CVector         vecPos;
	CVector         vecRot;
	CVector         vecScale;
	DWORD			dwMaterialColor1;
	DWORD			dwMaterialColor2;
};

typedef struct CTextdraw
{
	union
	{
		BYTE byteFlags;			// 25
		struct
		{
			BYTE byteBox : 1;
			BYTE byteLeft : 1;
			BYTE byteRight : 1;
			BYTE byteCenter : 1;
			BYTE byteProportional : 1;
			BYTE bytePadding : 3;
		};
	};
	float fLetterWidth;			// 1
	float fLetterHeight;		// 5
	DWORD dwLetterColor;		// 9
	float fLineWidth;			// 13
	float fLineHeight;			// 17
	DWORD dwBoxColor;			// 21
	BYTE byteShadow; // 26
	BYTE byteOutline; // 27
	DWORD dwBackgroundColor; // 31
	BYTE byteStyle; // 32
	BYTE byteSelectable; // 32
	float fX; // 33
	float fY; // 37
	WORD dwModelIndex; // 41
	CVector vecRot;
	float fZoom;
	WORD color1;
	WORD color2;
} _CTextdraw;

class CPlayerTextDraw
{
public:
	BOOL				bSlotState[MAX_PLAYER_TEXT_DRAWS];
	CTextdraw		    *TextDraw[MAX_PLAYER_TEXT_DRAWS];
	char				*szFontText[MAX_PLAYER_TEXT_DRAWS];
	bool				bHasText[MAX_PLAYER_TEXT_DRAWS];
};

#define MAX_PVARS               800
#define MAX_PVAR_NAME			40
/*
// PVar enumeration
#define PLAYER_VARTYPE_NONE		0
#define PLAYER_VARTYPE_INT		1
#define PLAYER_VARTYPE_STRING	2
#define PLAYER_VARTYPE_FLOAT	3
*/
typedef struct PVAR_DATA_t
{
	char			pVarName[MAX_PVAR_NAME + 1];
	BOOL			isReadOnly;
	int				pVarType;
	int				intValue;
	float			floatValue;
	char*			stringValue;
} PVAR_DATA;

class CPlayerVar
{
public:
	PVAR_DATA       pVars[MAX_PVARS];
	BOOL			isPVarActive[MAX_PVARS];
	int				upperIndex;
};

class CPlayerSpawnInfo // size  46
{
public:
	BYTE byteTeam;				// 0 - 1
	int iSkin;					// 1 - 5
	BYTE unk;					// 5 - 6
	CVector vecPos;				// 6 - 18
	float fRotation;			// 18 - 22
	int iSpawnWeapons[3];		// 22 - 34
	int iSpawnWeaponsAmmo[3];	// 34 - 46
};

class CBulletSyncData // sizeof = 40
{
public:
	BYTE			byteHitType;
	WORD			wHitID;
	CVector			vecHitOrigin;
	CVector			vecHitTarget;
	CVector			vecCenterOfHit;
	BYTE			byteWeaponID;
};

// 10505 - camera target
class CPlayer
{
public:
	CAimSyncData			aimSyncData;			// 0 - 39
	CVehicleSyncData		vehicleSyncData;		// 39 -
	CPassengerSyncData		passengerSyncData;		//
	CSyncData				syncData;				// 126 - 194
	CUnoccupiedSyncData		unoccupiedSyncData;		// 194 - 261
	CSpectatingSyncData		spectatingSyncData;		// 261 - 279
	CTrailerSyncData		trailerSyncData;		// 279 - 333
	DWORD					dwPlayerSyncUnused;		// 333 - 337
	DWORD					dwVehicleSyncUnused;	// 337 - 341
	BYTE					byteStreamedIn[MAX_PLAYERS];				// 341 - 1341
	BYTE					byteVehicleStreamedIn[MAX_VEHICLES];		// 1341 - 3341
	BYTE					byteSomethingUnused[1000];					// 3341 - 4341
	BYTE					byte3DTextLabelStreamedIn[1024];			// 4341  - 5365
	BYTE					bPickupStreamedIn[MAX_PICKUPS];				// 5365 - 9461
	BYTE					byteActorStreamedIn[MAX_PLAYERS];			// 9461 - 10461
	DWORD					dwStreamedInPlayers;						// 10461 - 10465
	DWORD					dwStreamedInVehicles;						// 10465 - 10469
	DWORD					dwStreamedInSomethingUnused;				// 10469 - 10473
	DWORD					dwStreamedIn3DTextLabels;					// 10479 - 10477
	DWORD					dwStreamedInPickups;						// 10477 - 10481
	DWORD					dwStreamedInActors;							// 10481 - 10485
	DWORD					bHasSetVehiclePos;	// 10485 - 10489
	DWORD					dwSetVehiclePosTick;// 10489 - 10493
	CVector					vecVehicleNewPos;	// 10493 - 10505
	BOOL					bCameraTarget;		// 10505
	DWORD					bHasSpawnInfo;		// 10509
	BOOL					bUpdateKeys;		// 50513
	CVector					vecPosition;		// 10517
	float					fHealth;			// 10529 - 10533
	float					fArmour;			// 10533 - 10537
	float					fQuaternion[4];		// 10537 - 10553
	float					fAngle;				// 10553 - 10557
	CVector					vecVelocity;		// 10557 - 10569
	WORD					wUDAnalog;			// 10569
	WORD					wLRAnalog;			// 10571
	DWORD					dwKeys;				// 10573 - 10577
	DWORD					dwOldKeys;			// 10577 - 10581
	BOOL					bEditObject;		// 10581 - 10585
	BOOL					bEditAttachedObject;// 10585 - 10589
	WORD					wDialogID;			// 10589 - 10591
	CPlayerTextDraw*		pTextdraw;			// 10591 - 10595
	CPlayerText3DLabels*	p3DText;			// 10595 - 10599
	WORD					wPlayerId;			// 10599 - 10601
	int						iUpdateState;		// 10601 - 10605
	//DWORD					dwLastSyncTick;		// 10605 - 10609
	CAttachedObject			attachedObject[MAX_ATTACHED_OBJECTS]; // 10605 - 11125
	BOOL					attachedObjectSlot[MAX_ATTACHED_OBJECTS]; // 11125 - 11165
	BOOL					bHasAimSync;		// 11165 - 11169
	BOOL					bHasTrailerSync;	// 11169 - 11173
	BOOL					bHasUnoccupiedSync;	// 11173 - 11177
	BYTE					byteState;			// 11177 - 11178
	CVector					vecCPPos;			// 11178 - 11190
	float					fCPSize;			// 11190 - 11194
	BOOL					bIsInCP;			// 11194 - 11198
	CVector					vecRaceCPPos;		// 11198 - 11210
	CVector					vecRaceCPNextPos;	// 11210 - 11222 
	BYTE					byteRaceCPType;		// 11222 - 11223 // TODO -> replace
	float					fRaceCPSize;		// 11223 - 11227
	BOOL					bIsInRaceCP;		// 11227 - 11231
	BOOL					bIsInModShop;		// 11231 - 11235
	WORD					wSkillLevel[11];	// 11235 - 11257
	int						iLastMarkerUpdate;	// 11257 - 11261
	CPlayerSpawnInfo		spawn;				// 11261 - 11307
	BOOL					bReadyToSpawn;		// 11307 - 11311
	BYTE					byteWantedLevel;	// 11311 - 11312
	BYTE					byteFightingStyle;  // 11312 - 11313
	BYTE					byteSeatId;			// 11313 - 11314
	WORD					wVehicleId;			// 11314 - 11316
	DWORD					iNickNameColor;		// 11316 - 11320
	BOOL					bShowCheckpoint;	// 11320 - 11324
	BOOL					bShowRaceCheckpoint;// 11324 - 11328
	int						iInteriorId;		// 11328 - 11332
	WORD					wWeaponAmmo[12];	// 11332 - 11356
	PAD(pad10, 28);								// 11356 - 11384
	BYTE					byteWeaponId[12];	// 11384 - 11396
	BYTE					byteWeaponID_unknown;// 11396 - 11397
	BYTE					byteCurrentWeapon;	// 11397 - 11398
	WORD					wTargetId;			// 11398 - 11400
	WORD					wTargetActorId;		// 11400 - 11402
	DWORD					dwLastShotTick;		// 11402 - 11406
	BYTE					dwLastShotWeapon;	// 11406 - 11407
	CBulletSyncData			bulletSyncData;		// 11407 - 11447	
	BYTE					m_byteTime;			// 11447 - 11448
	float					m_fGameTime;		// 11448 - 11452
	BYTE					byteSpectateType;	// 11452 - 11453
	DWORD					wSpectateID;		// 11453 - 11457
	DWORD					dwLastStreaming;	// 11457 - 11461
	DWORD					dwNPCRecordingType;	// 11461 - 11465
	FILE					*pRecordingFile;	// 11465 - 11469
	DWORD					dwFirstNPCWritingTime; // 11469 - 11473 
	PAD(unused, 9);								// 11473 - 11482
	CPlayerVar*				pPlayerVars;		// 11482 - 11486
	// Size = 9963
};

class CPlayerPool // sizeof = 99520
{
public:
	DWORD				dwVirtualWorld[MAX_PLAYERS];			// 0 - 4000
	DWORD				dwPlayersCount;							// 4000 - 4004
	DWORD				dwlastMarkerUpdate;						// 4004 - 4008
	float				fUpdatePlayerGameTimers;				// 4008 - 4012
	DWORD				dwScore[MAX_PLAYERS];					// 4012 - 8012
	DWORD				dwMoney[MAX_PLAYERS];					// 8012 - 12012
	DWORD				dwDrunkLevel[MAX_PLAYERS];				// 12012 - 16012
	DWORD				dwLastScoreUpdate[MAX_PLAYERS];			// 16012 - 20012
	char				szSerial[MAX_PLAYERS][101];				// 20012 - 121012				
	char				szVersion[MAX_PLAYERS][29];				// 121012 - 150012
	BOOL				bIsPlayerConnected[MAX_PLAYERS];		// 150012 - 154012
	CPlayer				*pPlayer[MAX_PLAYERS];					// 154012 - 158012
	char				szName[MAX_PLAYERS][25];				// 158012 - 183012
	BOOL				bIsAnAdmin[MAX_PLAYERS];				// 183012 - 187012
	BOOL				bIsNPC[MAX_PLAYERS];					// 187012 - 191012
	PAD(pad0, 8004);											// 191012 - 199016
	DWORD				dwPlayerPoolSize;						// 199016 - 199020
};

class CGameMode
{
public:
	AMX m_amx;
	bool m_bInitialised;
	bool m_bSleeping;
	float m_fSleepTime;
};

class CFilterScripts
{
public:
	void* m_pFilterScripts[MAX_FILTER_SCRIPTS];
	char m_szFilterScriptName[MAX_FILTER_SCRIPTS][255];
	int m_iFilterScriptCount;
};

#pragma pack(push, 1) // sizeof = 64
typedef struct _MATRIX4X4
{
	CVector right;
	DWORD  flags;
	CVector up;
	float  pad_u;
	CVector at;
	float  pad_a;
	CVector pos;
	float  pad_p;
} MATRIX4X4, *PMATRIX4X4;
#pragma pack(pop)

class CVehicleSpawn // size 36
{
public:
	int			iModelID;
	CVector		vecPos;
	float		fRot;
	int			iColor1;
	int			iColor2;
	int			iRespawnTime;
	int			iInterior;
};

class CVehicleModInfo // sizeof = 26
{
public:
	BYTE byteModSlots[14];                // + 0x0000
	BYTE bytePaintJob;                    // + 0x000E
	int iColor1;                             // + 0x000F
	int iColor2;                             // + 0x0010
};

class CVehicleParams // sizeof = 16
{
public:
	BYTE engine;
	BYTE lights;
	BYTE alarm;
	BYTE doors;
	BYTE bonnet;
	BYTE boot;
	BYTE objective; // 6

	BYTE siren; // 7

	BYTE door_driver; // 8
	BYTE door_passenger;
	BYTE door_backleft;
	BYTE door_backright; // 11

	BYTE windows_driver; // 12
	BYTE windows_passenger;
	BYTE windows_backleft;
	BYTE windows_backright; // 15 - 16
};

class CVehicle
{
public:
	CVector			vecPosition;		// 0 - 12
	MATRIX4X4		vehMatrix;			// 12 - 76
	CVector			vecVelocity;		// 76 - 88
	CVector			vecTurnSpeed;		// 88 - 100
	WORD			wVehicleID;			// 100 - 102
	WORD			wTrailerID;			// 102 - 104
	WORD			wCabID;				// 104 - 106
	WORD			wLastDriverID;		// 106 - 108
	WORD			vehPassengers[7];	// 108 - 122
	DWORD			vehActive;			// 122 - 126
	DWORD			vehWasted;			// 126 - 130	
	CVehicleSpawn	customSpawn;		// 130 - 166
	float			fHealth;			// 166 - 170
	DWORD			vehDoorStatus;		// 170 - 174
	DWORD			vehPanelStatus;		// 174 - 178
	BYTE			vehLightStatus;		// 178 - 179
	BYTE			vehTireStatus;		// 179 - 180
	bool			bDead;				// 180 - 181
	WORD			wKillerID;			// 181 - 183
	CVehicleModInfo vehModInfo;			// 183 - 206
	char			szNumberplate[32 + 1]; // 206 - 239
	CVehicleParams	vehParamEx;			// 239 - 255
	BYTE			bDeathNotification; // 246 - 247
	BYTE			bOccupied;			// 247 - 248
	DWORD			vehOccupiedTick;	// 248 - 252
	DWORD			vehRespawnTick;		// 252 - 256
};

class CVehiclePool
{
public:
	BYTE				byteVehicleModelsUsed[212];			// 0 - 212
	int					iVirtualWorld[MAX_VEHICLES];		// 212 - 8212
	BOOL				bVehicleSlotState[MAX_VEHICLES];	// 8212 - 16212
	CVehicle			*pVehicle[MAX_VEHICLES];			// 16212 - 24212
	DWORD				dwVehiclePoolSize;					// 24212
};

class CObjectMaterial // sizeof = 212
{
public:
	BYTE			byteUsed;				// 197 - 198
	BYTE			byteSlot;				// 198 - 199
	WORD			wModelID;				// 199 - 201
	DWORD			dwMaterialColor;		// 201 - 205
	char			szMaterialTXD[64 + 1];	// 205 - 270
	char			szMaterialTexture[64 + 1]; // 270 - 335
	BYTE			byteMaterialSize;		// 335 - 336
	char			szFont[64 + 1];			// 336 - 401
	BYTE			byteFontSize;			// 401 - 402
	BYTE			byteBold;				// 402 - 403
	DWORD			dwFontColor;			// 403 - 407
	DWORD			dwBackgroundColor;		// 407 - 411
	BYTE			byteAlignment;			// 411 - 412
};

class CObject // sizeof = 3700
{
public:
	WORD				wObjectID;			// 0 - 2
	int					iModel;				// 2 - 6
	BOOL				bActive;			// 6 - 10
	MATRIX4X4			matWorld;			// 10 - 74 - pos - Object position
	CVector				vecRot; 			// 74 - 86 - Object rotation
	MATRIX4X4			matTarget;			// 86 - 150	- 
	BYTE				bIsMoving;			// 150 - 151
	BYTE				bNoCameraCol;		// 151 - 152
	float				fMoveSpeed;			// 152 - 156
	DWORD				unk_4;				// 156 -160
	float				fDrawDistance;		// 160 - 164
	WORD				wAttachedVehicleID;	// 164 - 166
	WORD				wAttachedObjectID;	// 166 - 168
	CVector				vecAttachedOffset;	// 168 - 180
	CVector				vecAttachedRotation;// 180 - 192
	BYTE				byteSyncRot;		// 192 - 193
	DWORD				dwMaterialCount;	// 193 - 197
	CObjectMaterial		Material[16];		// 197 - 3637
	char				*szMaterialText[16];// 3637 - 3653
};

class CObjectPool
{
public:
	BOOL m_bPlayerObjectSlotState[MAX_PLAYERS][MAX_OBJECTS];	// 0 
	BOOL m_bPlayersObject[MAX_OBJECTS];							// 4.000.000
	CObject *m_pPlayerObjects[MAX_PLAYERS][MAX_OBJECTS];		// 4.004.000
	BOOL m_bObjectSlotState[MAX_OBJECTS];						// 8.004.000
	CObject *m_pObjects[MAX_OBJECTS];							// 8.008.000
};

class CTextDrawPool
{
public:
	BOOL				bSlotState[MAX_TEXT_DRAWS];
	CTextdraw		    *TextDraw[MAX_TEXT_DRAWS];
	char				*szFontText[MAX_TEXT_DRAWS];
	bool				bHasText[MAX_TEXT_DRAWS][MAX_PLAYERS];
};

class CSAMPGangZonePool
{
public:
	float			fGangZone[MAX_GANG_ZONES][4];
	BOOL			bSlotState[MAX_GANG_ZONES];
};


#define MAX_MENU_TEXT_SIZE	32
#define MAX_ITEMS			12
#define MAX_COLUMNS			2

struct t_MenuInteraction
{
	BOOL	Menu;
	BOOL	Row[MAX_ITEMS];
	uchar	unknown[12];
};

class CMenu	// size 0xB84
{
public:

	BYTE	menuID;														// + 0x0000
	char	title[MAX_MENU_TEXT_SIZE];								// + 0x0001
	char	items[MAX_ITEMS][MAX_COLUMNS][MAX_MENU_TEXT_SIZE];	// + 0x0021
	char	headers[MAX_COLUMNS][MAX_MENU_TEXT_SIZE];					// + 0x0321
	BOOL	isInitiedForPlayer[MAX_PLAYERS];							// + 0x0361
	t_MenuInteraction interaction;										// + 0x0B31
	float	posX;														// + 0x0B71
	float	posY;														// + 0x0B75
	float	column1Width;												// + 0x0B79
	float	column2Width;												// + 0x0B7D
	BYTE	columnsNumber;												// + 0x0B81
	BYTE	itemsCount[MAX_COLUMNS];									// + 0x0B82

};

class CMenuPool
{
public:
	CMenu*		menu[MAX_MENUS];			//	+ 0x0000
	BOOL		isCreated[MAX_MENUS];		//	+ 0x0200
	BOOL		playerMenu[MAX_PLAYERS];	//	+ 0x0400
};

struct ScriptTimer_s // sizeof = 0x11B (283)
{
	char szScriptFunc[255];
	int iTotalTime;
	int iRemainingTime;
	BOOL bRepeating;
	BOOL bKilled;
	AMX* pAMX;
	int iParamCount;
	void* cellParams;
};

typedef std::map<DWORD, ScriptTimer_s*> DwordTimerMap;

class CScriptTimers
{
public:
	DwordTimerMap m_Timers;
	DWORD m_dwTimerCount;
};

typedef struct Pickup_t // size 0x14
{
	int	iModel;
	int	iType;
	CVector		vecPos;
} tPickup;

class CPickupPool_
{
public:
	tPickup	m_Pickup[MAX_PICKUPS];			// + 0x0000
	BOOL	m_bActive[MAX_PICKUPS];			// + 0xA000
	int		m_iWorld[MAX_PICKUPS];		// + 0xC000
	int		m_iPickupCount;
};

#define GAMESTATE_STOPPED	 0
#define GAMESTATE_RUNNING	 1
#define GAMESTATE_RESTARTING 2

class CActor
{
public:
	BYTE pad0;				// 0
	int iSkinID;			// 1 - 5
	CVector vecSpawnPos;	// 5 - 17
	float fSpawnAngle;		// 17 - 21
	DWORD pad4;				// 21 - 25
	DWORD pad5;				// 25 - 29
	BYTE pad6;				// 29 - 30
	char animation[140];	// 30 - 170
	WORD pad7;				// 170 - 171
	float fHealth;			// 172 - 176
	DWORD pad;				// 176 - 180
	float fAngle;			// 180 - 184
	CVector vecPos;			// 184 - 196
	DWORD pad8[3];			// 196 - 208
	BYTE byteInvulnerable;	// 208 - 209
	WORD wActorID;			// 209 - 211
};

class CActorPool
{
public:
	int iActorVirtualWorld[1000];
	BOOL bValidActor[1000];
	CActor* pActor[1000];
	DWORD dwActorPoolSize;
};

struct PlayerID
{
	unsigned int binaryAddress;
	unsigned short port;
};

#pragma pack(push, 1)
/// All RPC functions have the same parameter list - this structure.
struct RPCParameters
{
	/// The data from the remote system
	unsigned char *input;

	/// How many bits long \a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;

	/// Which instance of RakPeer (or a derived RakServer or RakClient) got this call
	void *recipient;

	/// You can return values from RPC calls by writing them to this BitStream.
	/// This is only sent back if the RPC call originally passed a BitStream to receive the reply.
	/// If you do so and your send is reliable, it will block until you get a reply or you get disconnected from the system you are sending to, whichever is first.
	/// If your send is not reliable, it will block for triple the ping time, or until you are disconnected, or you get a reply, whichever is first.
	RakNet::BitStream *replyToSender;
};
#pragma pack(pop)

/// \sa NetworkIDGenerator.h
typedef unsigned char UniqueIDType;
typedef unsigned short PlayerIndex;
typedef unsigned char RPCIndex;
const int MAX_RPC_MAP_SIZE = ((RPCIndex)-1) - 1;
const int UNDEFINED_RPC_INDEX = ((RPCIndex)-1);

/// First byte of a network message
typedef unsigned char MessageID;

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;

struct RakNetStatisticsStruct
{
	///  Number of Messages in the send Buffer (high, medium, low priority)
	unsigned messageSendBuffer[NUMBER_OF_PRIORITIES];
	///  Number of messages sent (high, medium, low priority)
	unsigned messagesSent[NUMBER_OF_PRIORITIES];
	///  Number of data bits used for user messages
	unsigned messageDataBitsSent[NUMBER_OF_PRIORITIES];
	///  Number of total bits used for user messages, including headers
	unsigned messageTotalBitsSent[NUMBER_OF_PRIORITIES];

	///  Number of packets sent containing only acknowledgements
	unsigned packetsContainingOnlyAcknowlegements;
	///  Number of acknowledgements sent
	unsigned acknowlegementsSent;
	///  Number of acknowledgements waiting to be sent
	unsigned acknowlegementsPending;
	///  Number of acknowledgements bits sent
	unsigned acknowlegementBitsSent;

	///  Number of packets containing only acknowledgements and resends
	unsigned packetsContainingOnlyAcknowlegementsAndResends;

	///  Number of messages resent
	unsigned messageResends;
	///  Number of bits resent of actual data
	unsigned messageDataBitsResent;
	///  Total number of bits resent, including headers
	unsigned messagesTotalBitsResent;
	///  Number of messages waiting for ack (// TODO - rename this)
	unsigned messagesOnResendQueue;

	///  Number of messages not split for sending
	unsigned numberOfUnsplitMessages;
	///  Number of messages split for sending
	unsigned numberOfSplitMessages;
	///  Total number of splits done for sending
	unsigned totalSplits;

	///  Total packets sent
	unsigned packetsSent;

	///  Number of bits added by encryption
	unsigned encryptionBitsSent;
	///  total bits sent
	unsigned totalBitsSent;

	///  Number of sequenced messages arrived out of order
	unsigned sequencedMessagesOutOfOrder;
	///  Number of sequenced messages arrived in order
	unsigned sequencedMessagesInOrder;

	///  Number of ordered messages arrived out of order
	unsigned orderedMessagesOutOfOrder;
	///  Number of ordered messages arrived in order
	unsigned orderedMessagesInOrder;

	///  Packets with a good CRC received
	unsigned packetsReceived;
	///  Packets with a bad CRC received
	unsigned packetsWithBadCRCReceived;
	///  Bits with a good CRC received
	unsigned bitsReceived;
	///  Bits with a bad CRC received
	unsigned bitsWithBadCRCReceived;
	///  Number of acknowledgement messages received for packets we are resending
	unsigned acknowlegementsReceived;
	///  Number of acknowledgement messages received for packets we are not resending
	unsigned duplicateAcknowlegementsReceived;
	///  Number of data messages (anything other than an ack) received that are valid and not duplicate
	unsigned messagesReceived;
	///  Number of data messages (anything other than an ack) received that are invalid
	unsigned invalidMessagesReceived;
	///  Number of data messages (anything other than an ack) received that are duplicate
	unsigned duplicateMessagesReceived;
	///  Number of messages waiting for reassembly
	unsigned messagesWaitingForReassembly;
	///  Number of messages in reliability output queue
	unsigned internalOutputQueueSize;
	///  Current bits per second
	double bitsPerSecond;
	///  connection start time
	RakNetTime connectionStartTime;
};

#pragma pack(push, 1)
/// This represents a user message from another system.
struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// \deprecated You should use bitSize.
	unsigned int length;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};
#pragma pack(pop)

const PlayerID UNASSIGNED_PLAYER_ID =
{
	0xFFFFFFFF, 0xFFFF
};

#ifdef WIN32

class CCRakServer
{
public:
	~CCRakServer();
	virtual void _0();
	virtual bool Start(unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress = 0) = 0; // 4
	virtual void DisableSecurity(void); // 8
	virtual void SetPassword(const char *_password);	// 12
	virtual bool HasPassword(void);	// 16
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel = 0);	// 20
	virtual bool Send_ASD(const char *data, const int length, int priority, int reliability, char orderingChannel, PlayerID playerId, bool broadcast); // 24
	virtual bool Send(RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);	// 28
	virtual void _20(); // 
	virtual void _24();
	virtual Packet* Receive(void);
	virtual void CloseConnection(const PlayerID playerId); // 0x2C
	virtual void DeallocatePacket(Packet* asd);
	virtual void SetAllowedPlayers(unsigned short numberAllowed); // 0x34
	virtual unsigned short GetAllowedPlayers(void) const;
	virtual unsigned short GetConnectedPlayers(void);
	virtual void GetPlayerIPFromID(const PlayerID playerId, char returnValue[22], unsigned short *port);
	virtual void PingPlayer(const PlayerID playerId);
	virtual int GetAveragePing(const PlayerID playerId);
	virtual int GetLastPing(const PlayerID playerId); // 4C
	virtual int GetLowestPing(const PlayerID playerId);
	virtual void _54();
	virtual void _58();
	virtual void _5C();
	virtual void _60();
	virtual void _64();
	virtual void _68();
	virtual void _6C();
	virtual void _70();
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms));	// 74
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer);	// 78
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID);	// 7C
	virtual bool RPC(int* uniqueID, RakNet::BitStream* parameters, PacketPriority priority, PacketReliability reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast, bool shiftTimestamp); // 80
	virtual void _84();
	virtual void _88();
	virtual void _8C();
	virtual void _90();
	virtual void _94();
	virtual void _98();
	virtual void _9C();
	virtual void _A0();
	virtual void _A4();
	virtual void _A8();
	virtual void _AC();
	virtual void _B0();
	virtual void _B4();
	virtual void _B8();
	virtual void _BC();
	virtual void _C0();
	virtual void _C4();
	virtual void _C8();
	virtual void _CC();
	virtual const char* GetLocalIP(unsigned int index);
	virtual PlayerID GetInternalID(void) const;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead);
	virtual void SetRouterInterface(void *routerInterface);
	virtual void RemoveRouterInterface(void *routerInterface);
	virtual int GetIndexFromPlayerID(PlayerID playerId); // E4
	virtual PlayerID GetPlayerIDFromIndex(int index); // E8
	virtual void AddToBanList(const char *IP, unsigned int milliseconds = 0);
	virtual void RemoveFromBanList(const char *IP);
	virtual void ClearBanList(void);
	virtual bool IsBanned(const char *IP);
	virtual bool IsActivePlayerID(const PlayerID playerId);
	virtual void SetTimeoutTime(RakNetTime timeMS, const PlayerID target);
	virtual bool SetMTUSize(int size);
	virtual int GetMTUSize(void) const;
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength);
	virtual RakNetStatisticsStruct * const GetStatistics(const PlayerID playerId);
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
};

#else

class CCRakServer
{
public:
	~CCRakServer();
	virtual bool _0(); 
	virtual void _4();
	virtual bool Start(unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress = 0) = 0;
	virtual void _C();
	virtual void _10();
	virtual void _14();
	virtual void _18();
	virtual void _1C();
	virtual bool SendGECI(RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);
	virtual bool Send(RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);
	virtual void _28();
	virtual void _2C();
	virtual void _30();
	virtual void _34();
	virtual void SetAllowedPlayers(unsigned short numberAllowed);
	virtual void _3C();
	virtual void _40();
	virtual void _44();
	virtual void _48();
	virtual void _4C();
	virtual int GetLastPing( const PlayerID playerId ); // 0x50
	virtual void _54();
	virtual void _58();
	virtual void _5C();
	virtual const char* GetLocalIP( unsigned int index );
	virtual PlayerID GetInternalID( void ) const;
	virtual void PushBackPacket( Packet *packet, bool pushAtHead );
	virtual void SetRouterInterface( void *routerInterface );
	virtual void RemoveRouterInterface( void *routerInterface );
	virtual void UnregisterAsRemoteProcedureCall_BAD( int* uniqueID );
	virtual void RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) ); // 120
	virtual void RegisterClassMemberRPC( int* uniqueID, void *functionPointer ); // 124
	virtual void UnregisterAsRemoteProcedureCall( int* uniqueID ); // 128
	virtual void UnregisterAsRemoteProcedureCall_4( int* uniqueID );
	virtual void UnregisterAsRemoteProcedureCall_5( int* uniqueID );
	virtual bool RPC(int* uniqueID, RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast, bool shiftTimestamp);
	virtual void _90();
	virtual void _94();
	virtual void _98();
	virtual void _9C();
	virtual void _A0();
	virtual void _A4();
	virtual void _A8();
	virtual void _AC();
	virtual void _B0();
	virtual void _B4();
	virtual void _B8();
	virtual void _BC();
	virtual void _C0();
	virtual void _C4();
	virtual void _C8();
	virtual void _CC();
	virtual void _D0();
	virtual void _D4();
	virtual void _D8();
	virtual void _DC();
	virtual void _E0();
	virtual void _E8();
	virtual int GetIndexFromPlayerID( PlayerID playerId ); // EC
	virtual PlayerID GetPlayerIDFromIndex( int index ); // F0 - 240 - 244
	virtual void AddToBanList( const char *IP, unsigned int milliseconds=0 ); // 244 - 248
	virtual void RemoveFromBanList( const char *IP ); // 248 - 252
	virtual void ClearBanList( void );
	virtual bool IsBanned( const char *IP );
	virtual bool IsActivePlayerID( const PlayerID playerId );
	virtual void SetTimeoutTime( RakNetTime timeMS, const PlayerID target );
	virtual bool SetMTUSize( int size );
	virtual int GetMTUSize( void ) const;
	virtual void AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength );
	virtual RakNetStatisticsStruct * const GetStatistics( const PlayerID playerId );
	virtual void ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
};
#endif

class CNetGame
{
public:
	CGameMode				*pGameModePool;			// 0
	CFilterScripts			*pFilterScriptPool;		// 4
	CPlayerPool				*pPlayerPool;			// 8
	CVehiclePool			*pVehiclePool;			// 12
#ifndef NEW_PICKUP_SYSTEM
	CPickupPool_			*pPickupPool;			// 16
#else
	CPickupPool				*pPickupPool;			// 16
#endif
	CObjectPool				*pObjectPool;			// 20
	CMenuPool				*pMenuPool;				// 24
	CTextDrawPool			*pTextDrawPool;			// 28
	C3DTextPool				*p3DTextPool;			// 32
	CGangZonePool			*pGangZonePool;			// 36 
	CActorPool				*pActorPool;			// 40 
	int						iCurrentGameModeIndex;	// 44
	int						iCurrentGameModeRepeat;	// 48
	BOOL					bFirstGameModeLoaded;	// 52
	BOOL					unkasdasd;				// 56
	CScriptTimers			*pScriptTimers;			// 60
	CCRakServer				*pRak;					// 64
	DWORD					dwSomethingTick;
	DWORD					dwUnk;
	DWORD					dwUnk1;
	BOOL					bLanMode;				// 
	BOOL					bShowPlayerMarkers;		// 84
	BYTE					byteShowNameTags;		// 
	BYTE					bTirePopping;			// 
	BYTE					byteAllowWeapons;		// 
	BYTE					byteStuntBonus;			// 91 - 92
	BYTE					byteDefaultCameraCollision; // 92 - 93
	BYTE					byteWeather;			// 93 - 94
	int						iGameState;				// 94 - 98
	float					fGravity;				// 98 - 102
	int						iDeathDropMoney;		// 102 - 106
	BYTE					unklofasz;				// 106 - 107
	BYTE					byteMode;				// 107 - 108
	BYTE					bLimitGlobalChatRadius;	// 108 - 109
	BYTE					bUseCJWalk;				// 109 - 110
	float					fGlobalChatRadius;		// 110 - 114
	float					fNameTagDrawDistance;	// 114 - 118
	BYTE					byteDisableEnterExits;	// 118 - 119
	BYTE					byteNameTagLOS;			// 119 - 120
	BYTE					bManulVehicleEngineAndLights; // 120 - 121
	BYTE					bLimitPlayerMarkers;	// 121 - 122
	float					fPlayerMarkesLimit;		// 122 - 126 
	BOOL					bVehicleFriendlyFire;	// 126 - 130
#ifndef _WIN32
	double					dElapsedTime;			// size = 8
#endif
	int						iSpawnsAvailable;		// 130 - 134
	CPlayerSpawnInfo		AvailableSpawns[300];	// 129 - 13929
};

enum PacketEnumeration : unsigned char
{
	ID_INTERNAL_PING = 6,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_AUTH_KEY,
	ID_BROADCAST_PINGS = 15,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_SET_RANDOM_NUMBER_SEED = 21,
	ID_RPC,
	ID_RPC_REPLY,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_RSA_PUBLIC_KEY_MISMATCH = 28,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_INITIALIZE_ENCRYPTION,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_PONG,
	ID_TIMESTAMP,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	ID_ADVERTISE_SYSTEM = 56,

	ID_VEHICLE_SYNC = 200,
	ID_AIM_SYNC = 203,
	ID_BULLET_SYNC = 206,
	ID_PLAYER_SYNC = 207,
	ID_MARKERS_SYNC,
	ID_UNOCCUPIED_SYNC,
	ID_TRAILER_SYNC,
	ID_PASSENGER_SYNC,
	ID_SPECTATOR_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONCE,
	ID_WEAPONS_UPDATE,
	ID_STATS_UPDATE,
};
