#include "NoFriends.h"

NoFriends::NoFriends() : Module(0x0, Category::PLAYER, "Ignores friend list check.") {
}

NoFriends::~NoFriends() {
}

const char* NoFriends::getModuleName() {
	return ("NoFriends");
}
