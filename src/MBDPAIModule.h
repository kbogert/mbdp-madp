#pragma once
#include <BWAPI.h>
#include <windows.h>

#include "SimulationDecPOMDPDiscrete.h"
#include <time.h>

#include <vector>
#include <set>
#include <map>
#include <sstream>

DWORD WINAPI AnalyzeThread();

#define ATTACK_STATE_LASTS_MS CLOCKS_PER_SEC

class UnitObservation {
public:
	enum Order {
		Attack,
		Flee,
		Idle
	};

	UnitObservation() {
		lastOrder = Idle;
		attackedEventDate = 0;
		lastHealth = -1;
	}

	Order lastOrder;
	clock_t attackedEventDate; // if in the past, unit is not under attack
	int lastHealth;
};

class MBDPAIModule : public BWAPI::AIModule
{
public:
  MBDPAIModule();
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
  JointPolicyPureVector * jp;
  bool initFinished;

  std::map<int, UnitObservation *> unitObservations;

  bool isUnderAttack(BWAPI::Unit * unit);
  bool isAttacking(BWAPI::Unit * unit);

  std::string parsePolicy(std::stringstream & policyStr, bool seeEnemyObs);
};