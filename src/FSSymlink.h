#pragma once

#include "FSObject.h"
#include "FSDir.h"
#include <string>
#include "third_party.h"

//! Trieda reprezentujuca symlink.
class FSSymlink: public FSDir
{
public:
	
	/*!
	 * \brief Vytvori instanciu triedy reprezentujucu symbolicky link.
	 * \param path cesta k symlinku na disku
	*/
	FSSymlink(const std::string path):
		FSDir(path)
	{}

	/*!
	 * \brief Vrati zastupnu hodnotu za velkost.
	 * \return string
	*/	
	inline const std::string getSize() const {
		return "<SYM-" + std::string((hasChild() ? "D" : "F" )) + ">";
	}

	/*!
	 * \brief Zistenie, ci symlink ukazuje na subor alebo na priecinok
	 * \return boolean hodnota
	*/
	inline bool hasChild() const
	{
		return "YEP\n" == exec("bash -c '[ -d " + getAbsolutePath() + " ]' && echo YEP || echo NOPE");
	}
	
private:

};

