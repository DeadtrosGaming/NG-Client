#pragma once
#include "../Utils/DrawUtils.h"

class GuiUtils {
public:
	static void drawCrossLine(Vec2 pos, Mc_Color col, float lineWidth, float crossSize, bool secondCross);
	static void drawArrow(Vec2 pos, Mc_Color col, float lineWidth, float arrowSize, bool isUpArrow);
};
