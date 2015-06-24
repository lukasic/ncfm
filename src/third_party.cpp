#include <iostream>
#include <string>
#include <cstdlib>
#include "third_party.h"
#include "Logger.h"


std::string exec(const std::string & argCmd, bool err)
{
    std::string cmd = argCmd;
    if ( err )
        cmd += " 2>&1";

    Logger::getDefault().info( "exec(): " + cmd );

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[10000];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 10000, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);

    Logger::getDefault().info( result );

    return result;
}

