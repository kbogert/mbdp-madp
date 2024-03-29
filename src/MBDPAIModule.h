#pragma once
#include <BWAPI.h>
#include <windows.h>

#include "SimulationDecPOMDPDiscrete.h"
#include <time.h>

#include <vector>
#include <set>
#include <map>

DWORD WINAPI AnalyzeThread();

#define ATTACK_STATE_LASTS_MS CLOCKS_PER_SEC

class PolicyTreeNode {
public:
	std::string action;
	std::map<std::string, PolicyTreeNode *> children;

};

class UnitObservation {
public:
	enum Order {
		Attack,
		Flee,
		Idle,
		Explore
	};

	UnitObservation() {
		lastOrder = Idle;
		attackedEventDate = 0;
		lastHealth = -1;
		lastPolicyTreeNode = NULL;
		lastTarget = NULL;
	}

	Order lastOrder;
	BWAPI::Unit * lastTarget;
	clock_t attackedEventDate; // if in the past, unit is not under attack
	int lastHealth;
	PolicyTreeNode * lastPolicyTreeNode;
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

	void flee(BWAPI::Unit * unit);

	BWAPI::Unit * getClosestEnemy(BWAPI::Unit * unit);
	BWAPI::Unit * getClosestAndWeakestEnemy(BWAPI::Unit * unit);

  void drawStats();
  void showPlayers();
  void showForces();
  
  bool show_visibility_data;

  PlanningUnitDecPOMDPDiscrete* planner;
  bool initFinished;

  std::map<int, UnitObservation *> unitObservations;

  void MBDPAIModule::Explore(BWAPI::Unit * explorer);
  bool isUnderAttack(BWAPI::Unit * unit);
  bool isAttacking(BWAPI::Unit * unit);
  void MBDPAIModule::AttackUnit(BWAPI::Unit * attacker, BWAPI::Unit * target);

  void parsePolicy(std::string & policyStr);

  std::map<int, PolicyTreeNode *> policyTree;

};