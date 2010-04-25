#include "MBDPAIModule.h"
#include "JESPDynamicProgrammingPlanner.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "SimulationResult.h"

#include "argumentHandlers.h"
#include "argumentUtils.h"


using namespace BWAPI;
using namespace std;

using namespace ArgumentHandlers;


void MBDPAIModule::onStart()
{
#ifndef _DEBUG  
  // Enable some cheat flags
  Broodwar->enableFlag(Flag::UserInput);
  // Uncomment to enable complete map information
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  show_visibility_data=false;

  if (Broodwar->isReplay())
  {
    Broodwar->printf("The following players are in this replay:");
    for(std::set<Player*>::iterator p=Broodwar->getPlayers().begin();p!=Broodwar->getPlayers().end();p++)
    {
      if (!(*p)->getUnits().empty() && !(*p)->isNeutral())
      {
        Broodwar->printf("%s, playing as a %s",(*p)->getName().c_str(),(*p)->getRace().getName().c_str());
      }
    }
  }
  else
  {
    Broodwar->printf("The match up is %s v %s",
      Broodwar->self()->getRace().getName().c_str(),
      Broodwar->enemy()->getRace().getName().c_str());

#endif
	// Initialize planner

	ArgumentHandlers::Arguments args;
//	args.infiniteHorizon = 1;
	args.horizon = 3;
	args.dpf = "D:/CSCI-6900/problems/broadcastChannel.dpomdp";
//	args.problem_type = ProblemType::DT;
	DecPOMDPDiscreteInterface & decpomdp = * ArgumentUtils::GetDecPOMDPDiscreteInterfaceFromArgs(args);
    
    //Initialization of the planner with typical options for JESP:
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    params.SetComputeJointActionObservationHistories(false);
    params.SetComputeJointObservationHistories(false);
    params.SetComputeJointBeliefs(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);

    planner = new JESPDynamicProgrammingPlanner (params,args.horizon,&decpomdp);

#ifndef _DEBUG
	Broodwar->printf("JESP planner initialized"); 
  }
#endif
}
void MBDPAIModule::onEnd(bool isWinner)
{
  if (isWinner)
  {
    //log win to file
  }
}
void MBDPAIModule::onFrame()
{
  if (show_visibility_data)
  {    
    for(int x=0;x<Broodwar->mapWidth();x++)
    {
      for(int y=0;y<Broodwar->mapHeight();y++)
      {
        if (Broodwar->isExplored(x,y))
        {
          if (Broodwar->isVisible(x,y))
            Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Green);
          else
            Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Blue);
        }
        else
          Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Red);
      }
    }
  }

  if (Broodwar->isReplay())
    return;

  drawStats();

  static long long counter = 0;
  counter ++;

  // perform observations, update state variables

	// right now we only observe our own units

	for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++) {

		if (unitObservations.find((*i)->getID()) == unitObservations.end()) {
			unitObservations[(*i)->getID()] = new UnitObservation();
		}
		UnitObservation * obs = unitObservations[(*i)->getID()];

		if ((*i)->isIdle()) {
			obs->lastOrder = UnitObservation::Idle;
		}

		if (obs->lastHealth > (*i)->getShields() + (*i)->getHitPoints()) {
			// unit has just been attacked
			obs->attackedEventDate = clock() + ATTACK_STATE_LASTS_MS;
		}
		obs->lastHealth = (*i)->getShields() + (*i)->getHitPoints();
	}

  // update planner, run plan()

    if (counter % 30 != 1) return;

    planner->Plan();
    double V = planner->GetExpectedReward();
	JointPolicyPureVector * jp = planner->GetJointPolicyPureVector();



/*	for (int i = 0; i < jp->GetNrAgents(); i ++) {
		for (int j = 0; j < jp->GetNrDomainElements(i); j++) {
//			Broodwar->printf("ActionIndex for %d : %d", i, jp->GetActionIndex(i,j));

		}

	}
	*/
//		Broodwar->printf("Joint Action: %s", planner->GetJointAction(jp->GetJointActionIndex(0))->SoftPrintBrief().c_str());


  // enact policy

		std::string policy = planner->GetJointAction(jp->GetJointActionIndex(0))->SoftPrintBrief();

		for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++) {
			if (policy == "wait_send"){
				// gonna map this to a flee

				// if the unit is already fleeing, then don't change
				if (unitObservations[(*i)->getID()]->lastOrder != UnitObservation::Flee) {
					unitObservations[(*i)->getID()]->lastOrder = UnitObservation::Flee;
					flee(*i);
				}
			} else {
				// gonna map this to a attack

				// if the unit is already attacking, then don't change
				if (unitObservations[(*i)->getID()]->lastOrder != UnitObservation::Attack) {
					unitObservations[(*i)->getID()]->lastOrder = UnitObservation::Attack;
					attackClosest(*i);
				}
			}
		}
}

void MBDPAIModule::onUnitCreate(BWAPI::Unit* unit)
{

}
void MBDPAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay())
    Broodwar->sendText("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

}

void MBDPAIModule::onUnitMorph(BWAPI::Unit* unit)
{

}
void MBDPAIModule::onUnitShow(BWAPI::Unit* unit)
{
}
void MBDPAIModule::onUnitHide(BWAPI::Unit* unit)
{
}
void MBDPAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
}
void MBDPAIModule::onPlayerLeft(BWAPI::Player* player)
{
  Broodwar->sendText("%s left the game.",player->getName().c_str());
}
void MBDPAIModule::onNukeDetect(BWAPI::Position target)
{
}

bool MBDPAIModule::onSendText(std::string text)
{
  if (text=="/show players")
  {
    showPlayers();
    return false;
  } else if (text=="/show forces")
  {
    showForces();
    return false;
  } else if (text=="/show visibility")
  {
    show_visibility_data=true;
  } else
  {
    Broodwar->printf("You typed '%s'!",text.c_str());
  }
  return true;
}

void MBDPAIModule::drawStats()
{
  std::set<Unit*> myUnits = Broodwar->self()->getUnits();
  Broodwar->drawTextScreen(5,0,"I have %d units:",myUnits.size());
  std::map<UnitType, int> unitTypeCounts;
  int underAttack = 0;
  int attacking = 0;
  for(std::set<Unit*>::iterator i=myUnits.begin();i!=myUnits.end();i++)
  {
	  if (isUnderAttack(*i))
		  underAttack ++;
	  if (isAttacking(*i))
		  attacking ++;
    if (unitTypeCounts.find((*i)->getType())==unitTypeCounts.end())
    {
      unitTypeCounts.insert(std::make_pair((*i)->getType(),0));
    }
    unitTypeCounts.find((*i)->getType())->second++;
  }
  int line=1;
  Broodwar->drawTextScreen(5,16*line,"Under Attack - %d",underAttack);
  line++;
  Broodwar->drawTextScreen(5,16*line,"Attacking - %d",attacking);
  
}

void MBDPAIModule::showPlayers()
{
  std::set<Player*> players=Broodwar->getPlayers();
  for(std::set<Player*>::iterator i=players.begin();i!=players.end();i++)
  {
    Broodwar->printf("Player [%d]: %s is in force: %s",(*i)->getID(),(*i)->getName().c_str(), (*i)->getForce()->getName().c_str());
  }
}
void MBDPAIModule::showForces()
{
  std::set<Force*> forces=Broodwar->getForces();
  for(std::set<Force*>::iterator i=forces.begin();i!=forces.end();i++)
  {
    std::set<Player*> players=(*i)->getPlayers();
    Broodwar->printf("Force %s has the following players:",(*i)->getName().c_str());
    for(std::set<Player*>::iterator j=players.begin();j!=players.end();j++)
    {
      Broodwar->printf("  - Player [%d]: %s",(*j)->getID(),(*j)->getName().c_str());
    }
  }
}
BWAPI::Unit * MBDPAIModule::getClosestEnemy(BWAPI::Unit * unit) {

	// find the closest unit to me
	double closestDistance = 1000000000;
	BWAPI::Unit * closestUnit = NULL;

    // pick a visible enemy
	  for (std::set<Player *>::const_iterator iter = Broodwar->getPlayers().begin(); iter != Broodwar->getPlayers().end(); iter++) {
		  if ((*iter)->isEnemy(Broodwar->self())) {
			  for (std::set<Unit *>::const_iterator unititer = (*iter)->getUnits().begin(); unititer != (*iter)->getUnits().end(); unititer ++) {
				  double distance = unit->getPosition().getDistance((*unititer)->getPosition());
				  if (distance < closestDistance) {
					 closestDistance = distance;
					 closestUnit = *unititer;
				  }
			  }
		  }
	  }
	return closestUnit;
}

void MBDPAIModule::attackClosest(BWAPI::Unit * attacker) {

	Unit * closestUnit = getClosestEnemy(attacker);
	  if (closestUnit != NULL) {
		  attacker->attackUnit(closestUnit);
		  Broodwar->printf("Attack! at: %d, %d", closestUnit->getPosition().x(), closestUnit->getPosition().y());

	  }
}

void MBDPAIModule::flee(BWAPI::Unit * unit) {

	// pick a point in the opposite direction from the closest enemy
	Unit * closestEnemy = getClosestEnemy(unit);
	if (closestEnemy != NULL) {
		int x = -1;
		int y = -1;
		int mult = 20;
		int d_x = 1000;
		int d_y = 1000;

		while ((abs(d_x) > 200 || abs(d_y) > 200) && mult > 0) {
			d_x = (unit->getPosition().x() - closestEnemy->getPosition().x()) * mult;
			d_y = (unit->getPosition().y() - closestEnemy->getPosition().y()) * mult;
			x = d_x + unit->getPosition().x();
			y = d_y + unit->getPosition().y();
			mult --;
		}

		Position pos(x, y);
		unit->rightClick(pos);

		Broodwar->printf("RUN AWAY! to: %d, %d (Mult %d)", pos.x(), pos.y(), mult);



	}
}

bool MBDPAIModule::isUnderAttack(BWAPI::Unit *unit) {
	if (unitObservations.find(unit->getID()) == unitObservations.end()) {
		return false;

	}

	return unitObservations[unit->getID()]->attackedEventDate >= clock();
}

bool MBDPAIModule::isAttacking(BWAPI::Unit *unit) {
	if (unitObservations.find(unit->getID()) == unitObservations.end()) {
		return false;

	}

	return unitObservations[unit->getID()]->lastOrder == UnitObservation::Attack;
}