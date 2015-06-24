#pragma once

#include "FSObject.h"
#include <string>

//! Reprezentuje subor na disku.
class FSFile: public FSObject
{
public:
	/*!
	 * \brief Vytvori objekt reprezentujuci subor na disku.
	 * \param path cesta k suboru
	*/
	FSFile(const std::string & path):
		FSObject(path)
	{}

	virtual bool hasChild() const
	{
		return false;
	}

private:

};
