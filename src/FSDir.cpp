#include "constants.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "FSDir.h"
#include "FSSymlink.h"
#include "FSFile.h"

bool directoriesFirst(const FSObject * x, const FSObject * y)
{
	return x->hasChild() == true && y->hasChild() == false;
}

void FSDir::readContent()
{
	freeContent();
	std::string command = "ls -lh";

	command += " " + getAbsolutePath() + "/";
	command += " | tail -n +2 ";
	command += " | ";
	command += AWK;

	std::string ls = exec(command);

	std::istringstream iss(ls);
	std::string line;

	while ( line.clear(), getline(iss, line) )
	{
		std::istringstream linestream(line);
		std::string filename;
		std::string date; 
		std::string size;
		std::string owner;
		std::string perms;

		getline(linestream, filename, '#');
		getline(linestream, date, '#');
		getline(linestream, size, '#');
		getline(linestream, owner, '#');
		getline(linestream, perms);

		if ( ! hidden && filename[0] == '.' )
			continue;

		if ( perms[0] == 'd' )
		{
			FSDir * d = new FSDir( getAbsolutePath() + PATH_SEPARATOR + filename);
			d->setAttrs(date, owner, size, perms);
			content.push_back((FSObject*) d);
		}
		else if ( perms[0] == 'l' )
		{
			FSSymlink * d = new FSSymlink( getAbsolutePath() + PATH_SEPARATOR + filename);
			d->setAttrs(date, owner, size, perms);
			content.push_back((FSObject*) d);
		}
		else
		{
			FSFile * f = new FSFile(getAbsolutePath() + PATH_SEPARATOR + filename);
			f->setAttrs(date, owner, size, perms);
			content.push_back((FSObject*) f);
		}
	}

	std::sort(content.begin(), content.end(), directoriesFirst);
}
