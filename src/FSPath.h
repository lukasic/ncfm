#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "constants.h"
#include <iostream>
#include "shared.h"
#include "third_party.h"

class FSPath
{
public:
	explicit FSPath(const std::string argPath);

	const std::string getAbsolutePath() const;

	inline const std::string & getName() const
	{
		return name;
	}

	inline const std::string & getDirectory() const
	{
		return directory;
	}


private:
	std::string name;
	std::string directory;

};

