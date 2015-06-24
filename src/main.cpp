#include "NCScreen.h"
#include "Logger.h"

int main()
{
	Logger::getDefault().info("Logger initialized.");

	NCScreen scr;
	scr.loop();

	Logger::closeDefault();
	return 0;
}

