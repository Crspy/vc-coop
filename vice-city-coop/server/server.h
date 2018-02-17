#pragma once

// Dependencies
#include <RakPeerInterface.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <RPC4Plugin.h>
#include <DirectoryDeltaTransfer.h>
#include <FileListTransfer.h>
#include <IncrementalReadInterface.h>
#include <RakNetStatistics.h>
using namespace RakNet;

// Standard includes
#include <Windows.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>



// INIH
#include "vendor\inih\INIReader.h"

// Lua
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

// Plugin-SDK
#include "plugin.h"
#include "game_vc\common.h"
#include "game_vc\eWeaponFire.h"
#include "game_vc\CSprite.h"
#include "game_vc\CSprite2d.h"
#include "game_vc\CCamera.h"
#include "game_vc\CWorld.h"
#include "game_vc\CStreaming.h"
#include "game_vc\CCivilianPed.h"
#include "game_vc\CPlayerInfo.h"
#include "game_vc\CPopulation.h"

// VCCOOP
#include "..\vccoop_main\config.h"
#include "CConfiguration.h"
#include "CLogger.h"
#include "CServerPlayer.h"
#include "CServerNetwork.h"

#include "CLua.h"

//------------------------------------------------------------------------------------------------

extern CConfiguration   *gConfig;
extern CLogger			*gLog;
extern CServerNetwork	*gServerNetwork;

using namespace std;
using namespace RakNet;