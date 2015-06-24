#include <string>
#include "FSObject.h"


void FSObject::setAttrs(
	const std::string date,
	const std::string owner,
	const std::string size,
	const std::string perms)
{
	this->date = date;
	this->owner = owner;
	this->size = size;
	this->perms = perms;
}

