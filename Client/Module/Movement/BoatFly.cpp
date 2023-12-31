#include "BoatFly.h"

BoatFly::BoatFly() : Module(0x0, Category::MOVEMENT, "Fly A Boat (UP Arrow, Down Arrow)") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);
	registerFloatSetting("Vertical Speed", &upspeed, upspeed, 0.50f, 10.00f);
}

BoatFly::~BoatFly() {
}

const char* BoatFly::getModuleName() {
	return ("BoatFly");
}

static std::vector<Entity*> targetJoe;
void findHoe(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	int entityTypeId = currentEntity->getEntityTypeId();
	// PIG: 4876, HORSE:2118423, DONKEY: 2118424, MULE: 2118425, BOAT: 90
	if (entityTypeId != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetJoe.push_back(currentEntity);
	}
}

void BoatFly::onTick(GameMode* gm) {
	targetJoe.clear();
	Game.forEachEntity(findHoe);

	if (!targetJoe.empty()) {
		// keeps you in the air
		targetJoe[0]->velocity.y = 0.f;
		GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

		if (Game.canUseMoveKeys() && !targetJoe.empty()) {
			if (GameData::isKeyDown(VK_DOWN)) {
				targetJoe[0]->velocity.y -= upspeed;
			}
			if (GameData::isKeyDown(VK_UP)) {
				targetJoe[0]->velocity.y += upspeed;
			}
		}
	}
}

void BoatFly::onMove(MoveInputHandler* input) {
	targetJoe.clear();
	Game.forEachEntity(findHoe);

	if (!targetJoe.empty()) {
		float yaw = targetJoe[0]->yaw;
		if (targetJoe[0] && targetJoe[0] == nullptr) return;
		if (targetJoe[0]->isSneaking())
			return;
		Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (input->right) {
			yaw += 90.f;
			if (input->forward)
				yaw -= 20.f;

			else if (input->backward)
				yaw += 45.f;
		}
		if (input->left) {
			yaw -= 90.f;
			if (input->forward)
				yaw += 45.f;
			else if (input->backward)
				yaw -= 45.f;
		}

		if (input->backward && !input->left && !input->right)
			yaw += 180.f;

		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * speed2;
		moveVec.y = targetJoe[0]->velocity.y;
		moveVec.z = sin(calcYaw) * speed2;
		if (pressed) targetJoe[0]->lerpMotion(moveVec);
		if (!pressed) {
			targetJoe[0]->velocity.x = 0;
			targetJoe[0]->velocity.z = 0;
		}
	}
}