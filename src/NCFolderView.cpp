#include <cstdlib>
#include <string>
#include "NCFolderView.h"
#include "NCPanel.h"
#include "shared.h"

#include <iomanip>      
#include <iostream>
#include <sstream>

#include "Logger.h"

NCFolderView::NCFolderView(NCPanel & parent, std::string dirname):
	parent(parent), dir(FSDir("./")), menu_items(nullptr), menu(nullptr), menu_items_count(0)
{
    panel_win = subwin(parent.getWindow(), parent.getHeight()-2, parent.getWidth()-2, 2, parent.getX()+1);
    
  	wbkgd(getWindow(),COLOR_PAIR(1));
    active_win = panel_win;

    keypad( panel_win, TRUE);

    reload();
}


void NCFolderView::reload()
{
	unpost_menu(menu);
	for (int i=0; i < menu_items_count ; i++){
    	free_item(menu_items[i]);
	}
	free_menu(menu);

	dir.readContent();
	menu_items_count = dir.items();

	menu_items = (ITEM **)calloc( dir.items() + 2 , sizeof(ITEM *));
	menu_items[0] = new_item( ".." , NULL );

    for(int i = 0; i < dir.items(); i++)
    {
    	char * cstr_a = new char [ dir.content[i]->getName().length()+1 ];
		std::strcpy (cstr_a, dir.content[i]->getName().c_str());
        
		std::ostringstream oss;
		oss.str("");
		oss << " | " << std::setw(7)  << dir.content[i]->getSize()
		    << " | " << std::left << std::setw(11) << dir.content[i]->getPerms()
		    << " | " << std::setw(16) << dir.content[i]->getOwner()
		    << " | " << dir.content[i]->getDate();

    	char * cstr_b = new char [ oss.str().length()+1 ];
		std::strcpy (cstr_b, oss.str().c_str());

    	menu_items[i+1] = new_item( cstr_a , cstr_b );
	}

	menu_items[ dir.items()+1 ] = nullptr;
	
	item_opts_off(menu_items[0], O_SELECTABLE);

	menu = new_menu((ITEM **) menu_items);
	active_menu = menu;
	
	set_menu_grey(menu, COLOR_PAIR(5) | A_REVERSE);
	set_menu_fore(menu, COLOR_PAIR(5));
	set_menu_back(menu, COLOR_PAIR(5));

	menu_opts_off( menu, O_ONEVALUE);

    set_menu_win( menu,  panel_win);
    curs_set(FALSE);
	set_menu_mark( menu, " + ");
	set_menu_format(menu, parent.getHeight()-2, 1);

	post_menu(menu);
	wrefresh(stdscr);
	wrefresh(parent.getWindow());
	wrefresh(panel_win);
	refresh();
}

bool NCFolderView::openDir(std::string dirname)
{
	Logger::getDefault().info( dir.getAbsolutePath() + "/" + dirname );
	dir = FSDir( dir.getAbsolutePath() + "/" + dirname );
	Logger::getDefault().info( dir.getAbsolutePath() );
	reload();

	for (unsigned i = 0; i < dir.items(); i++)
		Logger::getDefault().info( "> " + dir.content[i]->getName() );

	return false;
}


bool NCFolderView::isDir(const std::string name) const {
	for (int i = 0; i < dir.items(); i++)
		if ( dir.content[i]->getName() == name )
			return dir.content[i]->hasChild();

	return false;
}


