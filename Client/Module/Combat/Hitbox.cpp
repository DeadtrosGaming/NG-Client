#include "Hitbox.h"

Hitbox::Hitbox() : Module(0x0, Category::COMBAT, "Increase an entitys hitbox size.") {
	// Registering Float Settings with Tooltips
	registerFloatSetting("Height", &height, height, 1.8f, 10, "Height: Set the height from 1.8 to 10");
	registerFloatSetting("Width", &width, width, 0.6f, 10, "Width: Adjust the width from 0.6 to 10");
}

Hitbox::~Hitbox() {
}

const char* Hitbox::getModuleName() {
	return ("Hitbox");
}

void findTarget(Entity* currentEntity, bool isRegularEntitie) {
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;
	if (currentEntity == 0)
		return;
	if (!currentEntity->isAlive() || currentEntity->damageTime >= 7)
		return;
	if (!Target::isValidTarget(currentEntity))
		return;
	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());
	if (dist < hitboxMod->range) {
		currentEntity->aabb->width = hitboxMod->width;
		currentEntity->aabb->height = hitboxMod->height;
	}
}
void Hitbox::onTick(GameMode* gm) {
	Game.forEachEntity(findTarget);
}