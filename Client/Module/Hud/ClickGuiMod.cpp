#include "ClickGuiMod.h"
#include "../../Menu/ClickGui.h"

ClickGuiMod::ClickGuiMod() : Module(VK_TAB, Category::HUD, "The clickgui - toggle everything just by clicking on it!") {
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	return ("ClickGui");
}

void ClickGuiMod::onEnable() {
	Game.getClientInstance()->releaseMouse();
}

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	Game.getClientInstance()->grabMouse();
	Opacity = 0;
}

void ClickGuiMod::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys())
		Game.getClientInstance()->releaseMouse();
}
void ClickGuiMod::onLoadConfig(void* conf) {
	Module::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
}
void ClickGuiMod::onSaveConfig(void* conf) {
	Module::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
}