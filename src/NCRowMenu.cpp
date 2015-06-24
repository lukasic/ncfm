#include <cstdlib>

#include "ncurses.h"
#include "menu.h"

#include "NCObject.h"
#include "NCWidget.h"
#include "NCRowMenu.h"

#include "constants.h"

#include <string>


NCRowMenu::NCRowMenu(int x, int y, const char ** choices):
	NCWidget(1, NCObject::AUTO_MAX, y, x)
{
	int i = 0;
	while ( choices[i] != nullptr )
	{
		this->choices.push_back( choices[i] );
		i++;
	}

	setup();
}


void NCRowMenu::setup()
{
	wbkgd(getWindow(),COLOR_PAIR(2));

	ITEM **my_items;
	MENU *my_menu;
    WINDOW *my_menu_win;
	int i;

	my_items = (ITEM **) calloc(choices.size()+2, sizeof(ITEM *));
    for(i = 0; i < choices.size(); ++i)
    	my_items[i] = new_item(choices[i].c_str(), "NULL");
	
	my_menu = new_menu((ITEM **) my_items);

	set_menu_grey(my_menu, COLOR_PAIR(2));
	set_menu_fore(my_menu, COLOR_PAIR(2));
	set_menu_back(my_menu, COLOR_PAIR(2));

	menu_opts_off(my_menu, O_SHOWDESC);

    my_menu_win = getWindow();
    keypad(my_menu_win, FALSE);

	/* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
    //set_menu_sub(my_menu, derwin(my_menu_win, 10, 150, 3, 1));
	set_menu_format(my_menu, 1, 10);
	set_menu_mark(my_menu, " ");

    //box(my_menu_win, 0, 0);

	//wbkgdset(getWindow(), COLOR_PAIR(2));
	//wrefresh(getWindow());
	wrefresh(stdscr);
	
	refresh();

	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);

	//setBorder(0, 0);
}


