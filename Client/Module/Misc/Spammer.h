#pragma once

#include "../Module.h"

class Spammer : public Module {
private:
	int Odelay = 0;
	bool bypass = true;
	int delay = 2;
	int length = 8;
	std::string message = "NG Client";

public:
	Spammer();
	~Spammer();

	inline std::string& getMessage() { return message; };
	inline int& getDelay() { return delay; };
	inline int& getLength() { return length; };
	inline bool& getBypass() { return bypass; };

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
