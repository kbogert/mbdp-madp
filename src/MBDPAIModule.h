#pragma once
#include <BWAPI.h>
#include <windows.h>

#include "SimulationDecPOMDPDiscrete.h"

DWORD WINAPI AnalyzeThread();

class MBDPAIModule : public BWAPI::AIModule
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

	void attackClosest(BWAPI::Unit * attacker);
	void flee(BWAPI::Unit * unit);

  void drawStats();
  void showPlayers();
  void showForces();
  
  bool show_visibility_data;

  PlanningUnitDecPOMDPDiscrete* planner;
};