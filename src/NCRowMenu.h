#pragma once

#include <vector>
#include <string>

//! NCurses Widget reprezentujuci jednoriadkove menu.
class NCRowMenu : public NCWidget
{
public:
	/*!
	 * \brief Vytvori jednoriadkove menu (widget) na zadanej pozicii.
	 * \param x horizontalna pozicia pre umiestnenie widgetu
	 * \param y vertikalna pozicia pre umiestnenie widgetu
	 * \param choices pole stringov obsahujuce popisy.
	*/
	NCRowMenu(int x, int y, const char ** choices);

	/*!
	 * \brief Inicializuje struktury a vykresli objekt.
	*/
	void setup();

private:
	std::vector<std::string> choices;  ///< zoznam poloziek


};
