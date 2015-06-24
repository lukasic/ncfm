#pragma once

#include <string>
#include "ncurses.h"
#include "FSObject.h"
#include "FSPath.h"

//! Abstraktna trida pre reprezentaciu objektu na disku. Spolocna pre priecinky, subory, symlinky...
class FSObject
{
public:
	/*!
	 * \brief Inicializuje vnutorne struktury spolocne pre vsetky objekty ulozitelne na disku.
	 * \param path cesta k suboru, ktory sa reprezentuje
	*/
	FSObject(const std::string & path):
		path(path)
	{}

	virtual ~FSObject() {}

	/*!
	 * \brief Vrati farbu objektu v zozname.
	 * \param ncurses color hodnota
	*/
	virtual int getColor() const
	{
		return COLOR_WHITE;
	}

	/*!
	 * \brief Zisti, ci do objektu je mozne dalej vstupit a nacitat jeho strukturu.
	 * \return boolean hodnota
	*/
	virtual bool hasChild() const
	{
		return false;
	}

	/*!
	 * \brief Nastavi atributy pri inicializacii objektu.
	 * \param date  posledna modifikacia
	 * \param owner vlastnik / skupina
	 * \param size  velkost na disku
	 * \param perms opravnenia
	*/
	void setAttrs(const std::string date, const std::string owner, const std::string size, const std::string perms);

	/*!
	 * \brief Getter - datum poslednej zmeny
	 * \return datum poslednej zmeny
	*/
	virtual inline const std::string & getDate() const { return date; }


	/*!
	 * \brief Getter - vrati vlastnika a skupinu
	 * \return vlastnik:skupina
	*/
	virtual inline const std::string & getOwner() const { return owner; }


	/*!
	 * \brief Getter - velkost na disku
	 * \return skutocna velkost na disku
	*/
	virtual inline const std::string   getSize() const { return size; }
	

	/*!
	 * \brief Getter - opravenia
	 * \return opravnenia
	*/
	virtual inline const std::string & getPerms() const { return perms; }


	/*!
	 * \brief Vrati absolutnu cestu k objektu ulozenom na disku.
	 * \return string - absolutna cesta
	*/
	inline const std::string   getAbsolutePath() const { return path.getAbsolutePath(); }

	/*!
	 * \brief Vrati priecinok, v ktorom je dany objekt ulozeny.
	 * \return string - absolutna cesta
	*/
	inline const std::string & getDirectory() const { return path.getDirectory(); }

	/*!
	 * \brief Vrati nazov objektu.
	 * \return string - nazov suboru / priecinka
	*/
	inline const std::string & getName() const { return path.getName(); }

private:
	FSPath path;        ///< cesta
	std::string date;   ///< datum poslednej zmeny
	std::string owner;  ///< vlastnik
	std::string size;   ///< velkost na disku
	std::string perms;  ///< opravnenia
};
