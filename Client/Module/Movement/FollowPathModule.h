#pragma once

#include "../Module.h"
#include "../../path/JoePathFinder.h"
#include "../../path/JoeMovementController.h"
#include "../../path/goals/JoeGoal.h"
#include <functional>

class FollowPathModule : public Module {
private:
	std::shared_ptr<JoePathFinder> pathFinder;
	std::unique_ptr<JoeMovementController> movementController;
	std::shared_ptr<JoePath> path;
	std::shared_ptr<JoePath> nextPath;
	int engageDelay = -1;
public:
	std::shared_ptr<JoeGoal> goal;

	FollowPathModule();

	const char *getModuleName() override;
	void startSearch(Vec3i startNode, BlockSource* region, float searchTimeout, std::function<void(bool, JoePath)> callback);
	void onTick(GameMode *mode) override;
	void onEnable() override;
	void onDisable() override;
	void onLevelRender() override;
	void onMove(MoveInputHandler *handler) override;
};
