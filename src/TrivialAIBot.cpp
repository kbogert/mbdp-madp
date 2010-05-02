#include "TrivialAIBot.h"

using namespace BWAPI;

void TrivialAIModule::onStart()
{
  srand(time(0));
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

  }
}
void TrivialAIModule::onEnd(bool isWinner)
{
  if (isWinner)
  {
    //log win to file
  }
}
void TrivialAIModule::onFrame()
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


	for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++) {

		Unit * closestUnit = getClosestAndWeakestEnemy(*i);
		if (closestUnit == NULL) {
			if ((*i)->isIdle())
				Explore(*i);
			continue;
		}
		if (orders[*i] != closestUnit) {
			AttackUnit(*i, closestUnit);

			orders[*i] = closestUnit;

			if (closestUnit == NULL) {

			} else {
				Broodwar->printf("Attack! at: %d, %d", closestUnit->getPosition().x(), closestUnit->getPosition().y());
			}
		}


	} 

}

void TrivialAIModule::onUnitCreate(BWAPI::Unit* unit)
{

}
void TrivialAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay())
    Broodwar->sendText("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

}

void TrivialAIModule::onUnitMorph(BWAPI::Unit* unit)
{

}
void TrivialAIModule::onUnitShow(BWAPI::Unit* unit)
{
}
void TrivialAIModule::onUnitHide(BWAPI::Unit* unit)
{
}
void TrivialAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
}
void TrivialAIModule::onPlayerLeft(BWAPI::Player* player)
{
  Broodwar->sendText("%s left the game.",player->getName().c_str());
}
void TrivialAIModule::onNukeDetect(BWAPI::Position target)
{
}

bool TrivialAIModule::onSendText(std::string text)
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

void TrivialAIModule::drawStats()
{
  std::set<Unit*> myUnits = Broodwar->self()->getUnits();
  Broodwar->drawTextScreen(5,0,"I have %d units:",myUnits.size());
  std::map<UnitType, int> unitTypeCounts;
  for(std::set<Unit*>::iterator i=myUnits.begin();i!=myUnits.end();i++)
  {
    if (unitTypeCounts.find((*i)->getType())==unitTypeCounts.end())
    {
      unitTypeCounts.insert(std::make_pair((*i)->getType(),0));
    }
    unitTypeCounts.find((*i)->getType())->second++;
  }
  
}

void TrivialAIModule::showPlayers()
{
  std::set<Player*> players=Broodwar->getPlayers();
  for(std::set<Player*>::iterator i=players.begin();i!=players.end();i++)
  {
    Broodwar->printf("Player [%d]: %s is in force: %s",(*i)->getID(),(*i)->getName().c_str(), (*i)->getForce()->getName().c_str());
  }
}
void TrivialAIModule::showForces()
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
BWAPI::Unit * TrivialAIModule::getClosestEnemy(BWAPI::Unit * unit) {

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

BWAPI::Unit * TrivialAIModule::getClosestAndWeakestEnemy(BWAPI::Unit * unit) {

	double weaknessWeight = 0.5;

	// find the closest unit to me
	double closestDistance = 1000000000;
	BWAPI::Unit * closestUnit = NULL;

    // pick a visible enemy
	  for (std::set<Player *>::const_iterator iter = Broodwar->getPlayers().begin(); iter != Broodwar->getPlayers().end(); iter++) {
		  if ((*iter)->isEnemy(Broodwar->self())) {
			  for (std::set<Unit *>::const_iterator unititer = (*iter)->getUnits().begin(); unititer != (*iter)->getUnits().end(); unititer ++) {
				  double distance = unit->getPosition().getDistance((*unititer)->getPosition());
				  distance *= (1- weaknessWeight);
				  distance += weaknessWeight * ((*unititer)->getShields() + (*unititer)->getHitPoints());
				  if (distance < closestDistance) {
					 closestDistance = distance;
					 closestUnit = *unititer;
				  }
			  }
		  }
	  }
	return closestUnit;
}

void TrivialAIModule::Explore(BWAPI::Unit * explorer) {
		// explore in a random direction
		int x = rand() % (Broodwar->mapWidth());
		int y = rand() % (Broodwar->mapHeight());

		TilePosition pos(x, y);
		Broodwar->printf("Explore to: %d, %d", x, y);
		explorer->rightClick(pos);
}


void TrivialAIModule::AttackUnit(BWAPI::Unit * attacker, BWAPI::Unit * target) {
	if (target != NULL) {
		attacker->attackUnit(target);
	}

}

void TrivialAIModule::flee(BWAPI::Unit * unit) {

	// pick a point in the opposite direction from the closest enemy
	Unit * closestEnemy = getClosestEnemy(unit);
	if (closestEnemy != NULL) {
		int x = -1;
		int y = -1;
		int mult = 20;
		int d_x = 1000;
		int d_y = 1000;

		while ((abs(d_x) > 100 || abs(d_y) > 100) && mult > 0 ) {
			d_x = (unit->getPosition().x() - closestEnemy->getPosition().x()) * mult;
			d_y = (unit->getPosition().y() - closestEnemy->getPosition().y()) * mult;
			x = d_x + unit->getPosition().x();
			y = d_y + unit->getPosition().y();
			mult --;
		}

		Position pos(max(0,min(x,Broodwar->mapWidth() * 32)), max(0,min(y,Broodwar->mapHeight() * 32)));
		unit->rightClick(pos);

		Broodwar->printf("RUN AWAY! to: %d, %d (Mult %d)", pos.x(), pos.y(), mult);

	}
}

