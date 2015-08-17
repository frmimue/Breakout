#include "Breakout.h"


int main() {

	Breakout& breakout = Breakout(glm::vec2(800.0f, 600.0f));
	breakout.run();


	return 0;
}