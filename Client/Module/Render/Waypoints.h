#pragma once

#include "../Module.h"
#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/Json.hpp"
#include <sstream>
#include <optional>

struct WaypointInstance {
	Vec3 pos;
	int dimension;

	WaypointInstance(Vec3 pos, int dim) : pos(pos), dimension(dim){};
};

class Waypoints : public Module {
private:
	std::shared_ptr<std::map<std::string, WaypointInstance>> waypoints = std::make_shared<std::map<std::string, WaypointInstance>>();

public:
	Waypoints();
	~Waypoints();

	bool interdimensional = true;
	bool showCoordinates = false;
	float size = 0.6f;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onLoadConfig(void* confVoid) override;
	virtual void onSaveConfig(void* confVoid) override;

	bool add(std::string text, Vec3 pos, int dimension) {
		for (auto it = waypoints->begin(); it != waypoints->end(); it++) {
			if (text == it->first) {
				return false;
			}
		}
		waypoints->emplace(text, WaypointInstance(pos, dimension));
		return true;
	}

	bool remove(std::string name) {
		for (auto it = waypoints->begin(); it != waypoints->end(); it++) {
			if (name == it->first) {
				waypoints->erase(name);
				return true;
			}
		}
		return false;
	}

	std::optional<WaypointInstance> getWaypoint(std::string name) {
		if (waypoints->find(name) == waypoints->end())
			return {};

		return waypoints->at(name);
	};

	std::shared_ptr<std::map<std::string, WaypointInstance>> getWaypoints() {
		return waypoints;
	}
};