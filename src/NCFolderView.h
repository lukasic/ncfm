#pragma once

#include "menu.h"
#include "panel.h"
#include "ncurses.h"
//#include "NCPanelContainer.h"
#include "FSDir.h"
// #include "NCPanel.h"
#include <string>

class NCPanel;

//! Reprezentacia priecinka (FSDir) v grafickej (NCurses) podobe.
class NCFolderView
{
public:
    /*!
     * \brief Vytvori instanciu objektu, inicializuje struktury a nacita obsah priecinka.
     * \param parent odkaz na rodicovsky widget, v ktorom je toto view umiestnene.
     * \param dirname cesta k priecinku, ktory chceme zobrazit.
    */
	NCFolderView(NCPanel & parent, std::string dirname);

    /*!
     * \brief Getter - vrati MENU - zoznam priecinkov a suborov.
     * \return struktura MENU (menu.h)
    */
	MENU * getMenu() const { return menu; }
	
    /*!
     * \brief Vrati pod-okno, v ktorom je tento objekt vykresleny.
     * \param struktura okna WINDOW (ncurses.h)
    */
    WINDOW * getWindow() const { return panel_win; }

    /*!
     * \brief Znovu nacita obsah priecinka z disku.
    */
    void reload();

    /*!
     * \brief Zmeni aktualny priecinok.
     * \param dirname novy priecinok, ktory chceme reprezentovat.
    */
    bool openDir(const std::string dirname);

    /*!
     * \brief Zisti, ci polozka s danym menom je priecinok/symlink/archiv.
     * \param boolean
    */
    bool isDir(const std::string name) const;

    /*!
     * \brief Vrati absolutnu cestu pracovneho priecinka.
     * \param string - absolutna cesta
    */    
    inline std::string getCurrentPath() const { return dir.getAbsolutePath(); }

private:
	NCPanel & parent;      ///< odkaz na rodica
	FSDir dir;             ///< priecinok, ktory reprezentujeme

	ITEM ** menu_items;    ///< obsah priecinka - vykresleny do NC objektov
	MENU * menu;           ///< menu reprezentujuce obsah priecinka
    WINDOW * panel_win;    ///< pod-okno, do ktoreho sa vsetko vykresluje

    int menu_items_count;  ///< pocet suborov / poloziek v menu

	friend class NCPanelContainer;  ///< kontajner obalucujuci vsetky Panely a ich widgety
};
