#pragma once
#include <BWAPI.h>
#include <windows.h>

#include "SimulationDecPOMDPDiscrete.h"
#include <time.h>

DWORD WINAPI AnalyzeThread();

#define ATTACK_STATE_LASTS_MS 750

class UnitObservation {
public:
	enum Order {
		Attack,
		Flee,
		Idle
	};

	UnitObservation() {
		lastOrder = Idle;
		attackedEventDate = time(0);
		attackedEventDate --;
		lastHealth = -1;
	}

	Order lastOrder;
	time_t attackedEventDate; // if in the past, unit is not under attack
	int lastHealth;
};

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

	BWAPI::Unit * getClosestEnemy(BWAPI::Unit * unit);

  void drawStats();
  void showPlayers();
  void showForces();
  
  bool show_visibility_data;

  PlanningUnitDecPOMDPDiscrete* planner;

  std::map<int, UnitObservation *> unitObservations;
};