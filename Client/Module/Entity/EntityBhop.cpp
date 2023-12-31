#include "EntityBhop.h"

EntityBhop::EntityBhop() : Module(0x0, Category::ENTITY, "so funny") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 1.5f);
	registerBoolSetting("Lowhop", &lowhop, lowhop);
	registerFloatSetting("Lowhop UpValue", &upVal, upVal, 0.05f, 0.50f);
}

EntityBhop::~EntityBhop() {
}

const char* EntityBhop::getModuleName() {
	return ("EntityBhop");
}
static std::vector<Entity*> targetKid;
void findKid(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	int entityTypeId = currentEntity->getEntityTypeId();
	// PIG: 4876, HORSE:2118423, DONKEY: 2118424, MULE: 2118425, BOAT: 90
	if (entityTypeId != 4876 && entityTypeId != 2118423 && entityTypeId != 2118424 && entityTypeId != 2118425 && entityTypeId != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetKid.push_back(currentEntity);
	}
}
void EntityBhop::onMove(MoveInputHandler* input) {
	targetKid.clear();
	Game.forEachEntity(findKid);

	if (!targetKid.empty()) {
		auto player = targetKid[0];
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();

		float calcYaw = (player->yaw + 90) * (PI / 180);
		Vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
		if (player->onGround && pressed && !input->isJumping && lowhop)
			player->velocity.y -= upVal;
	}
}