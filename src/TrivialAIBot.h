#pragma once
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <BWAPI.h>
#include <time.h>

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <set>
#include <map>

class TrivialAIModule : public BWAPI::AIModule
{
public:
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual bool onSendText(std::string text);
  virtual void onPlayerLeft(BWAPI::Player* player);
  virtual void onNukeDetect(BWAPI::Position target);
  virtual void onUnitCreate(BWAPI::Unit* unit);
  virtual void onUnitDestroy(BWAPI::Unit* unit);
  virtual void onUnitMorph(BWAPI::Unit* unit);
  virtual void onUnitShow(BWAPI::Unit* unit);
  virtual void onUnitHide(BWAPI::Unit* unit);
  virtual void onUnitRenegade(BWAPI::Unit* unit);

protected:

	void flee(BWAPI::Unit * unit);

	BWAPI::Unit * getClosestEnemy(BWAPI::Unit * unit);
	BWAPI::Unit * getClosestAndWeakestEnemy(BWAPI::Unit * unit);

  void drawStats();
  void showPlayers();
  void showForces();
  
  bool show_visibility_data;

  void Explore(BWAPI::Unit * explorer);
  void AttackUnit(BWAPI::Unit * attacker, BWAPI::Unit * target);

  std::map<BWAPI::Unit *, BWAPI::Unit *> orders;
};


namespace BWAPI { Game* Broodwar; }
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
    BWAPI::BWAPI_init();
		break;
	case DLL_PROCESS_DETACH:
		break;
	}


	return TRUE;
}

 extern "C" __declspec(dllexport) BWAPI::AIModule* newAIModule(BWAPI::Game* game)
{
  BWAPI::Broodwar=game;
  return new TrivialAIModule();
}