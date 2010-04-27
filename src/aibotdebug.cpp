#include <windows.h>
#include <stdio.h>
#include "BWAPI.h"
#include "stdarg.h"

#include <list>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

#include <BWAPI/Color.h>
#include <BWAPI/CoordinateType.h>
#include <BWAPI/Error.h>
#include <BWAPI/Flag.h>
#include <BWAPI/Race.h>
#include <BWAPI/Order.h>
#include <BWAPI/Latency.h>
#include <BWAPI/TilePosition.h>
#include <BWAPI/UnitType.h>
#include <BWAPI/TechType.h>
#include <BWAPI/UpgradeType.h>
#include <BWAPI/Input.h>
#include <BWAPI/Force.h>

using namespace BWAPI;

class TestUnit : public BWAPI::Unit {
public:
	int getID() const{
		return 0;
	}
	Player* getPlayer() const {
		return NULL;
	}
	UnitType getType() const {
		return BWAPI::UnitTypes::None;
	}
       UnitType getInitialType() const{
		return BWAPI::UnitTypes::None;
	}
       int getHitPoints() const{
		return 0;
	}
       int getInitialHitPoints() const {
		return 0;
	}
       int getShields() const {
		return 0;
	}
       int getEnergy() const {
		return 0;
	}
       int getResources() const {
		return 0;
	}
       int getInitialResources() const {
		return 0;
	}
       int getKillCount() const {
		return 0;
	}
       int getGroundWeaponCooldown() const {
		return 0;
	}
       int getAirWeaponCooldown() const {
		return 0;
	}
       int getSpellCooldown() const {
		return 0;
	}
       int getDefenseMatrixPoints() const {
		return 0;
	}

       int getDefenseMatrixTimer() const {
		return 0;
	}
       int getEnsnareTimer() const {
		return 0;
	}
       int getIrradiateTimer() const {
		return 0;
	}
       int getLockdownTimer() const {
		return 0;
	}
       int getMaelstromTimer() const {
		return 0;
	}
       int getPlagueTimer() const {
		return 0;
	}
       int getRemoveTimer() const {
		return 0;
	}
       int getStasisTimer() const {
		return 0;
	}
       int getStimTimer() const {
		return 0;
	}

       Position getPosition() const {
		   return BWAPI::Positions::None;
	}
       Position getInitialPosition() const {
		   return BWAPI::Positions::None;
	}
       TilePosition getTilePosition() const {
		   return BWAPI::TilePositions::None;
	}
       TilePosition getInitialTilePosition() const {
		   return BWAPI::TilePositions::None;
	}
       double getDistance(Unit* target) const {
		   return 0.0;
	}
	   double getDistance(Position target) const {
		   return 0.0;
	   }
       double getAngle() const {
		   return 0.0;
	   }
       double getVelocityX() const {
		   return 0.0;
	   }
       double getVelocityY() const {
		   return 0.0;
	   }

       Unit* getTarget() const {
		   return NULL;
	   }
       Position getTargetPosition() const {
		   return BWAPI::Positions::None;
	}
       Order getOrder() const {
		   return BWAPI::Orders::Attack1;
	}
	   Unit* getOrderTarget() const {
		   return NULL;
	   }
	   int getOrderTimer() const {
		   return 0;
	   }
	   Order getSecondaryOrder() const {
		   return BWAPI::Orders::Attack2;
	   }
	   Unit* getBuildUnit() const {
		   return NULL;
	   }
	   UnitType getBuildType() const {
		   return BWAPI::UnitTypes::None;
	   }
	   int getRemainingBuildTime() const {
		   return 0;
	   }
	   int getRemainingTrainTime() const {
		   return 0;
	   }
	   Unit* getChild() const {
		   return NULL;
	   }
	   std::list<UnitType > getTrainingQueue() const {
		   return *(new std::list<UnitType>);
	   }
	   Unit* getTransport() const {
		   return NULL;
	   }
	   std::list<Unit*> getLoadedUnits() const {
		   return *(new std::list<Unit *>);
	   }
	   int getInterceptorCount() const {
		   return 0;
	   }
       int getScarabCount() const {
		   return 0;
	   }
       int getSpiderMineCount() const {
		   return 0;
	   }
       TechType getTech() const {
		   return BWAPI::TechTypes::Archon_Warp;
	   }
       UpgradeType getUpgrade() const {
		   return BWAPI::UpgradeTypes::Adrenal_Glands;
	   }
       int getRemainingResearchTime() const {
		   return 0;
	   }
       int getRemainingUpgradeTime() const {
		   return 0;
	   }
       Position getRallyPosition() const {
		   return BWAPI::Positions::None;
	   }
       Unit* getRallyUnit() const {
		   return NULL;
	   }
       Unit* getAddon() const {
		   return NULL;
	   }
       Unit* getHatchery() const {
		   return NULL;
	   }
       std::set<Unit*> getLarva() const {
		   return *(new std::set<Unit*>);
	   }
       int getUpgradeLevel(UpgradeType upgrade) const {
		   return 0;
	   }

       bool exists() const { return true; }
       bool isAccelerating() const { return true; }
       bool isBeingConstructed() const { return true; }
       bool isBeingHealed() const { return true; }
       bool isBlind() const { return true; }
       bool isBraking() const { return true; }
       bool isBurrowed() const { return true; }
       bool isCarryingGas() const { return true; }
       bool isCarryingMinerals() const { return true; }
       bool isCloaked() const { return true; }
       bool isCompleted() const { return true; }
       bool isConstructing() const { return true; }
       bool isDefenseMatrixed() const { return true; }
       bool isEnsnared() const { return true; }
       bool isFollowing() const { return true; }
       bool isGatheringGas() const { return true; }
       bool isGatheringMinerals() const { return true; }
       bool isHallucination() const { return true; }
       bool isIdle() const { return true; }
       bool isIrradiated() const { return true; }
       bool isLifted() const { return true; }
       bool isLoaded() const { return true; }
       bool isLockedDown() const { return true; }
       bool isMaelstrommed() const { return true; }
       bool isMorphing() const { return true; }
       bool isMoving() const { return true; }
       bool isParasited() const { return true; }
       bool isPatrolling() const { return true; }
       bool isPlagued() const { return true; }
       bool isRepairing() const { return true; }
       bool isResearching() const { return true; }
       bool isSelected() const { return true; }
       bool isSieged() const { return true; }
       bool isStartingAttack() const { return true; }
       bool isStasised() const { return true; }
       bool isStimmed() const { return true; }
       bool isTraining() const { return true; }
       bool isUnderStorm() const { return true; }
       bool isUnpowered() const { return true; }
       bool isUpgrading() const { return true; }
       bool isVisible() const { return true; }
       bool isBeingGathered() const { return true; }

       bool attackMove(Position position) { return true; }
       bool attackUnit(Unit* target) { return true; }
       bool rightClick(Position position) { return true; }
       bool rightClick(Unit* target) { return true; }
       bool train(UnitType type) { return true; }
       bool build(TilePosition position, UnitType type) { return true; }
       bool buildAddon(UnitType type) { return true; }
       bool research(TechType tech) { return true; }
       bool upgrade(UpgradeType upgrade) { return true; }
       bool stop() { return true; }
       bool holdPosition() { return true; }
       bool patrol(Position position) { return true; }
       bool follow(Unit* target) { return true; }
       bool setRallyPosition(Position target) { return true; }
       bool setRallyUnit(Unit* target) { return true; }
       bool repair(Unit* target) { return true; }
       bool returnCargo() { return true; }
       bool morph(UnitType type) { return true; }
       bool burrow() { return true; }
       bool unburrow() { return true; }
       bool siege() { return true; }
       bool unsiege() { return true; }
       bool cloak() { return true; }
       bool decloak() { return true; }
       bool lift() { return true; }
       bool land(TilePosition position) { return true; }
       bool load(Unit* target) { return true; }
       bool unload(Unit* target) { return true; }
       bool unloadAll() { return true; }
       bool unloadAll(Position position) { return true; }
       bool cancelConstruction() { return true; }
       bool haltConstruction() { return true; }
       bool cancelMorph() { return true; }
       bool cancelTrain() { return true; }
       bool cancelTrain(int slot) { return true; }
       bool cancelAddon() { return true; }
       bool cancelResearch() { return true; }
       bool cancelUpgrade() { return true; }
       bool useTech(TechType tech) { return true; }
       bool useTech(TechType tech, Position position) { return true; }
       bool useTech(TechType tech, Unit* target) { return true; }
};

class TestPlayer : public BWAPI::Player {
private:
	std::set<Unit*> unitSet;
public:
	int getID() const {
		return 0;
	}
	std::string getName() const {
		return std::string("");
	}
	const std::set<Unit*>& getUnits() const {
		return unitSet;
	}
	Race getRace() const {
		return Races::Terran;
	}
	PlayerType playerType() const {
		return PlayerTypes::Human;
	}
	Force* getForce() const {
		return NULL;
	}
	bool isAlly(Player* player) const {
		return true;
	}
       bool isEnemy(Player* player) const {
		return true;
	}
       bool isNeutral() const{
		return false;
	}
       TilePosition getStartLocation() const {
		   return TilePositions::None;
	}
       bool isVictorious() const {
		return true;
	}
       bool isDefeated() const {
		return true;
	}
       bool leftGame() const {
		return true;
	}

       int minerals() const {
		return 0;
		}
       int gas() const {
		return 0;
		}
       int cumulativeMinerals() const {
		return 0;
		}
       int cumulativeGas() const{
		return 0;
		}

       int supplyTotal() const {
		return 0;
		}
       int supplyUsed() const{
		return 0;
		}
       int supplyTotal(Race race) const{
		return 0;
		}
       int supplyUsed(Race race) const {
		return 0;
		}

       int allUnitCount(UnitType unit) const {
		return 0;
		}
       int completedUnitCount(UnitType unit) const {
		return 0;
		}
       int incompleteUnitCount(UnitType unit) const {
		return 0;
		}
       int deadUnitCount(UnitType unit) const {
		return 0;
		}
       int killedUnitCount(UnitType unit) const {
		return 0;
		}

       int  getUpgradeLevel(UpgradeType upgrade) const {
		return 0;
		}
       bool hasResearched(TechType tech) const{
		return false;
		}
       bool isResearching(TechType tech) const {
		return false;
		}
       bool isUpgrading(UpgradeType upgrade) const {
		return false;
		}

};


class TestGame : public BWAPI::Game {
private:
	TestPlayer * player;
    public :
		TestGame() {
			player = new TestPlayer();
		}
		std::set< Force* >& getForces() {
			return *(new std::set<Force *>);
		}
		std::set< Player* >& getPlayers() {
			return *(new std::set<Player *>);
		}
		std::set< Unit* >& getAllUnits(){
			return *(new std::set<Unit*>);
		}
		std::set< Unit* >& getMinerals(){
			return *(new std::set<Unit*>);
		}
       std::set< Unit* >& getGeysers(){
			return *(new std::set<Unit*>);
		}
       std::set< Unit* >& getNeutralUnits(){
			return *(new std::set<Unit*>);
		}

       std::set< Unit* >& getStaticMinerals(){
			return *(new std::set<Unit*>);
		}
       std::set< Unit* >& getStaticGeysers(){
			return *(new std::set<Unit*>);
		}
       std::set< Unit* >& getStaticNeutralUnits(){
			return *(new std::set<Unit*>);
		}

	   int getLatency(){
		   return 0;
	   }
	   int getFrameCount(){
		   return 0;
	   }
       int getMouseX(){
		   return 0;
	   }
       int getMouseY(){
		   return 0;
	   }
	   BWAPI::Position getMousePosition(){
		   return Position(0,0);
	   }
	   bool getMouseState(MouseButton button){
		   return false;
	   }
	   bool getMouseState(int button){
		   return false;
	   }
	   bool getKeyState(Key key){
		   return false;
	   }
       bool getKeyState(int key){
		   return false;
	   }
       int getScreenX(){
		   return 0;
	   }
       int getScreenY(){
		   return 0;
	   }
       BWAPI::Position getScreenPosition(){
		   return Position(0,0);
	   }
	   void setScreenPosition(int x, int y){}
	   void setScreenPosition(BWAPI::Position p){}
	   void pingMinimap(int x, int y){}
	   void pingMinimap(BWAPI::Position p){}

       bool isFlagEnabled(int flag){
		   return false;
	   }
	   void enableFlag(int flag) {}
       std::set<Unit*>& unitsOnTile(int x, int y){
			return *(new std::set<Unit*>);
		}
	   Error getLastError() const {
		   return 0;
	   }

       int mapWidth(){
		   return 0;
	   }
       int mapHeight(){
		   return 0;
	   }
       std::string mapFilename(){
		   return std::string("");
	   }
       std::string mapName(){
		   return std::string("");
	   }
       int getMapHash(){
		   return 0;
	   }

       int  getGroundHeight(int x, int y){
		   return 0;
	   }
       bool isWalkable(int x, int y){
		   return true;
	   }
       bool isBuildable(int x, int y){
		   return true;
	   }
       bool isVisible(int x, int y){
		   return true;
	   }
       bool isExplored(int x, int y){
		   return true;
	   }
       bool hasCreep(int x, int y){
		   return true;
	   }
       bool hasPower(int x, int y, int tileWidth, int tileHeight){
		   return true;
	   }

       bool isBuildable(TilePosition position){
		   return true;
	   }
       bool isVisible(TilePosition position){
		   return true;
	   }
       bool isExplored(TilePosition position){
		   return true;
	   }
       bool hasCreep(TilePosition position){
		   return true;
	   }
       bool hasPower(TilePosition position, int tileWidth, int tileHeight){
		   return true;
	   }

       bool canBuildHere(Unit* builder, TilePosition position, UnitType type){
		   return true;
	   }
       bool canMake(Unit* builder, UnitType type){
		   return true;
	   }
       bool canResearch(Unit* unit, TechType type){
		   return true;
	   }
       bool canUpgrade(Unit* unit, UpgradeType type){
		   return true;
	   }
       std::set< TilePosition >& getStartLocations(){
		   return *(new std::set<TilePosition>);
	   }

	   void printf(const char* text, ...) {}
	   void sendText(const char* text, ...) {}
	   void changeRace(Race race) {}
       bool isMultiplayer(){
		   return true;
	   }
       bool isPaused() {
		   return false;
	   }
       bool isReplay() {
		   return false;
	   }
	   void startGame() {}
       void pauseGame() {}
       void resumeGame() {}
       void leaveGame()  {}
       void restartGame() {}
       void setLocalSpeed(int speed = -1) {}
       std::set<Unit*>& getSelectedUnits(){
		   return *(new std::set<Unit *>);
	   }
	   Player* self() {
		   return player;
	   }
	   Player* enemy() {
			return player;
	   }

	   void drawText(int ctype, int x, int y, const char* text, ...) {
	   }
	   void drawTextMap(int x, int y, const char* text, ...){}
       void drawTextMouse(int x, int y, const char* text, ...){}
       void drawTextScreen(int x, int y, const char* text, ...) {}

       void drawBox(int ctype, int left, int top, int right, int bottom, Color color, bool isSolid = false){}
       void drawBoxMap(int left, int top, int right, int bottom, Color color, bool isSolid = false) {}
       void drawBoxMouse(int left, int top, int right, int bottom, Color color, bool isSolid = false) {}
       void drawBoxScreen(int left, int top, int right, int bottom, Color color, bool isSolid = false) {}

       void drawTriangle(int ctype, int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid = false) {}
       void drawTriangleMap(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid = false) {}
       void drawTriangleMouse(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid = false) {}
       void drawTriangleScreen(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid = false) {}

       void drawCircle(int ctype, int x, int y, int radius, Color color, bool isSolid = false) {}
       void drawCircleMap(int x, int y, int radius, Color color, bool isSolid = false) {}
       void drawCircleMouse(int x, int y, int radius, Color color, bool isSolid = false) {}
       void drawCircleScreen(int x, int y, int radius, Color color, bool isSolid = false) {}

       void drawEllipse(int ctype, int x, int y, int xrad, int yrad, Color color, bool isSolid = false) {}
       void drawEllipseMap(int x, int y, int xrad, int yrad, Color color, bool isSolid = false) {}
       void drawEllipseMouse(int x, int y, int xrad, int yrad, Color color, bool isSolid = false) {}
       void drawEllipseScreen(int x, int y, int xrad, int yrad, Color color, bool isSolid = false) {}

       void drawDot(int ctype, int x, int y, Color color) {}
       void drawDotMap(int x, int y, Color color) {}
       void drawDotMouse(int x, int y, Color color) {}
       void drawDotScreen(int x, int y, Color color) {}

       void drawLine(int ctype, int x1, int y1, int x2, int y2, Color color) {}
       void drawLineMap(int x1, int y1, int x2, int y2, Color color) {}
       void drawLineMouse(int x1, int y1, int x2, int y2, Color color) {}
       void drawLineScreen(int x1, int y1, int x2, int y2, Color color) {}


};

using namespace std;
std::string parsePolicy(stringstream &policy, bool seeEnemyObs) {

	char policyStr[512]; 
	policy.getline(policyStr, 511);

	char s0[512], s1[512], s2[512], s3[512];
	
	if (sscanf(policyStr,"%511s %511s %511s %511s",s0,s1,s2,s3) <= 0)
		return std::string();

	if (strcmp(s1, "S") == 0 && seeEnemyObs) {
		return std::string(s3);
	} else if (strcmp(s1, "D") == 0 && ! seeEnemyObs) {
		return std::string(s3);
	}
	// try parsing the next line
	return parsePolicy(policy, seeEnemyObs);

}


// DLL function signature
typedef BWAPI::AIModule* (*newAIModule)(BWAPI::Game* game);
 
int main(int argc, char **argv)
{
	newAIModule createAIModule;
	BWAPI::AIModule * testModule;
 
	// Load DLL file
	HINSTANCE hinstLib = LoadLibrary(TEXT("MBDPAIBot2.dll"));
	if (hinstLib == NULL) {
		printf("%d", GetLastError());
		printf("ERROR: unable to load DLL\n");
		return 1;
	}
 
	// Get function pointer
	createAIModule = (newAIModule)GetProcAddress(hinstLib, "newAIModule");
	if (createAIModule == NULL) {
		printf("ERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}
 

	// Call function.

	BWAPI::Game * testGame = new TestGame();

	testModule = createAIModule(testGame);
 
	testModule->onStart();

	for (int i = 0; i < 1000; i ++) {
		testModule->onFrame();
	}

	// Unload DLL file
	FreeLibrary(hinstLib);
 
	return 0;
}