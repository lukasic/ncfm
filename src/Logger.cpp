#include "Logger.h"

Logger * Logger::defaultLogger = nullptr;

Logger & Logger::getDefault()
{
	if ( Logger::defaultLogger == nullptr )
	{
		Logger::defaultLogger = new Logger( LOGFILE );

		#ifdef __DEBUG__
		Logger::defaultLogger->setLevel(Logger::DEBUG);
		#else
		Logger::defaultLogger->setLevel(LOGLEVEL);
		#endif
	}

	return * Logger::defaultLogger;
}

void Logger::closeDefault()
{
	delete Logger::defaultLogger;
	Logger::defaultLogger = nullptr;
}

