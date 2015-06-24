#pragma once

#include "ncurses.h"
#include "panel.h"
#include "menu.h"

class NCPanel;

extern MENU * active_menu;        ///< aktivne menu
extern ITEM * cur_item;           ///< aktivna polozka v menu
extern WINDOW * active_win;       ///< aktivne okno

extern NCPanel * activePanel;     ///< aktivny panel
extern NCPanel * inactivePanel;   ///< neaktivny panel

