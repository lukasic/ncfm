#include <string>
#include <vector>
#include <sstream>
#include "constants.h"
#include <iostream>
#include "shared.h"
#include "third_party.h"
#include "FSPath.h"

FSPath::FSPath(const std::string argPath)
{
	std::string path = argPath;

	if ( path[0] == '~' && path[1] == PATH_SEPARATOR_CH )
	{
		std::string homedir = exec("cd ~/ && pwd | tr -d '\n' ");
		path.erase(path.begin(), path.begin()+1);
		path = homedir + path;
	}

	if ( path[0] == '.' && path[1] == '.' )
	{
		path.erase(path.begin(), path.begin()+2);
		path = exec("cd .. && pwd | tr -d '\n'") + path;
	}

	if ( path[0] == '.' && path[1] == PATH_SEPARATOR_CH )
	{
		path.erase(path.begin(), path.begin()+2);
		path = exec("pwd | tr -d '\n'") + path;
	}

	if ( path[0] != PATH_SEPARATOR_CH )
		path = exec("pwd | tr -d '\n'") + PATH_SEPARATOR + path;

	std::string rebuilded;
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream iss(path);

	while ( token.clear(), getline(iss, token, PATH_SEPARATOR_CH) )
		if ( token == "" )
			continue;
		else if ( token != ".." )
			tokens.push_back(token);
		else
			if ( tokens.size() > 0 )
				tokens.pop_back();

	if ( tokens.size() == 0 )
	{
		name = "";
		directory = PATH_SEPARATOR;
	}

	else if ( tokens.size() == 1 )
	{
		name = tokens.back();
		tokens.pop_back();
		directory = PATH_SEPARATOR;
	}

	else
	{
		name = tokens.back();
		tokens.pop_back();

		directory.clear();
		directory = "";

		for ( unsigned i = 0; i < tokens.size(); i++ )
			directory += PATH_SEPARATOR + tokens[i];
	}
}


const std::string FSPath::getAbsolutePath() const
{
	if ( directory == "" && name == "" )
		return PATH_SEPARATOR;
	else if ( directory == PATH_SEPARATOR )
		return PATH_SEPARATOR + name;
	else
		return directory + PATH_SEPARATOR + name;
}
