#pragma once

#include "constants.h"

#include <string>
#include <vector>
#include "FSObject.h"
#include "ncurses.h"

#include "third_party.h"

//! Trieda reprezentujuca priecinok na disku.
class FSDir: public FSObject
{
public:	
	/*!
	 * \brief Vytvori objekt a nacita obsah priecinka.
	 * \param path cesta k priecinku, ktory sa ma reprezentovat.
	*/
	FSDir(const std::string & path):
		FSObject(path), hidden(false)
	{}

	~FSDir() { freeContent(); }
	
	/*!
	 * \brief Nastavenie zobrazovania skrytych suborov.
	 * \param v boolean hodnota - true pre zobrazenie, false pre skrytie suborov
	*/
	inline void hiddenFiles(bool v) { hidden = v; }
	
	/*!
	 * \brief Nacita obsah priecinka do internych struktur.
	*/
	void readContent();

	/*!
	 * \brief Vrati pocet suborov a priecinkov.
	 * \return pocet suborov a priecinkov
	*/
	inline int items() const { return content.size(); }

	inline virtual bool hasChild() const { return true; }


	inline virtual int getColor() const { return COLOR_RED; }

	/*!
	 * \brief Vrati velkost suboru na disku.
	 * \param velkost suboru
	*/
	inline const std::string   getSize() const { return std::string("<DIR>"); }

private:

	/*!
	 * \brief Uvolni alokovane prostriedky.
	*/
	void freeContent()
	{
		for (unsigned i = 0; i < content.size(); i++)
			delete content[i];
		content.clear();
	}

	std::vector<FSObject *> content;  ///< objekty reprezentujuce obsah priecinka na disku

	bool hidden;  ///< flag oznacujuci ci sa zobrazuju skryte subory

	friend class NCFolderView;  ///< trieda, ktora obaluje tuto triedu v NC podobe
};

