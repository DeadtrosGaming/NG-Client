#include "Derp.h"

Derp::Derp() : Module(0x0, Category::MISC, "lol you stupid.") {
	registerBoolSetting("ihaveastroke", &epicStroke, epicStroke, "ihaveastroke: Toggle epic stroke mode");
	registerBoolSetting("packet mode", &packetMode, packetMode, "packet mode: Toggle packet mode");
}

Derp::~Derp() {
}

const char* Derp::getModuleName() {
	return "Derp";
}

void Derp::onTick(GameMode* gm) {
	if (packetMode) {
		MovePlayerPacket p(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
		if (epicStroke) {
			p.pitch = (float)(rand() % 360);
			p.yaw = (float)(rand() % 360);
		} else {
			p.pitch = (float)(counter % 360);
			p.yaw = (float)(counter % 360);
		}
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	} else {
		if (epicStroke) {
			gm->player->getActorHeadRotationComponent()->rot.x = (float)(rand() % 360);
			gm->player->getMobBodyRotationComponent()->bodyRot = (float)(rand() % 360);
		} else {
			gm->player->getActorHeadRotationComponent()->rot.x = (float)(counter % 360);
			gm->player->getMobBodyRotationComponent()->bodyRot = (float)(counter % 360);
		}
	}

	if (counter < 360)
		counter++;
	else
		counter = 0;
}
