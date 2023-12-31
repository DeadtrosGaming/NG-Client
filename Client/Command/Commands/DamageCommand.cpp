#include "DamageCommand.h"

#include "../../Module/ModuleManager.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself (relies on falldamage)", "<amount>") {
	registerAlias("dmg");
}

DamageCommand::~DamageCommand() {
}

bool DamageCommand::execute(std::vector<std::string>* args) {
	assert(Game.getLocalPlayer() != nullptr);
	float amount = stof(args->at(1));
	if (amount <= 0.0f) {
		clientMessageF("%sPlease enter a number greater than 0.", RED);
		return true;
	}
	auto noFallMod = moduleMgr->getModule<NoFall>();
	bool isEnabled = noFallMod->isEnabled();
	if (isEnabled) {
		noFallMod->setEnabled(false);
		Game.getLocalPlayer()->causeFallDamage(amount + 3.0f);
		noFallMod->setEnabled(true);
	} else {
		Game.getLocalPlayer()->causeFallDamage(amount + 3.0f);
	}
	return true;
}
