#include "main.h"

CClientPlayer::CClientPlayer(int nID, int gID)
{
	this->ped = NULL;
	CPlayerPed::SetupPlayerPed(gID);
	CWorld::Players[gID].m_pPed->m_nPedStatus = 2;
	this->ped = CWorld::Players[gID].m_pPed;
	this->ped->Teleport({ VCCOOP_DEFAULT_SPAWN_POSITION });
	this->ped->SetModelIndex(7);

	this->gameID = gID;
	this->networkID = nID;
	
	gLog->Log("[CClientPlayer]GameID: %d\nNetwork ID: %d\nPed pointer: 0x%X\n\n", gID, nID, ped);

	gGame->remotePlayerPeds[gID] = this->ped;
	gGame->remotePlayers++;
}

CClientPlayer::CClientPlayer(int nID)
{
	this->gameID = 0;
	this->networkID = nID;
	this->ped = FindPlayerPed();
}

CClientPlayer::~CClientPlayer()
{

}

void CClientPlayer::SyncPlayer(PlayerSyncData spd)
{
	this->syncData = spd;

	ped->m_nModelIndex = spd.iModelIndex;
	ped->m_dwAnimGroupId = spd.iCurrentAnimID;
	ped->m_fHealth = spd.Health;
	ped->m_fRotationCur = spd.Rotation;
	ped->m_fRotationDest = spd.Rotation;
	ped->m_fArmour = spd.Armour;

	gGame->remotePlayerKeys[this->gameID] = spd.playerKeys;
	gGame->remotePlayerLookFrontX[this->gameID] = spd.playerLook;
}

PlayerSyncData CClientPlayer::BuildSyncData()
{
	PlayerSyncData spd;
	spd.Health = ped->m_fHealth;
	spd.iCurrentAnimID = ped->m_dwAnimGroupId;
	spd.Armour = ped->m_fArmour;
	spd.iModelIndex = ped->m_nModelIndex;
	spd.Rotation = ped->m_fRotationCur;

	spd.CurrWep = 0;
	spd.WepModelIndex = 0;
	spd.Ammo = 0;

	spd.iInteriorID = 0;

	spd.playerKeys = *(GTA_CONTROLSET*)0x7DBCB0;
	spd.playerLook = *(CAMERA_AIM*)0x7E4978;
	
	this->syncData = spd;

	return spd;
}