#pragma once

#include "NCPanelContainer.h"
#include "NCRowMenu.h"


//! Trieda reprezentujuca hlavne okno aplikacie.
class NCScreen
{
public:
	/*!
	 * \brief Vytvori instanciu hlavneho okna aplikacie a vykresli objekty. Tato instancia by mala byt jedina.
	*/
	NCScreen();

	/*!
	 * \brief Spusti aktivnu smycku pre prijimanie a vykonavanie prikazov.
	*/
	void loop();

	/*!
	 * \brief Vykresli na obrazovku nanovo vsetky objekty a widgety.
	*/
	void redrawAll();

	/*!
	 * \brief Zresetuje obsah statusbaru.
	*/
	void clearStatusBar();

private:
	NCPanelContainer * panels;   ///< hlavny widget okna 
	NCRowMenu * mainMenu;        ///< horne menu
	NCRowMenu * commandsMenu;    ///< menu prikazov

	int width;   ///< sirka okna
	int height;  ///< vyska okna
};
