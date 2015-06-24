#include "ncurses.h"
#include "NCPanel.h"

// #include "NCPanelContainer.h"

#include "shared.h"

#include <cassert>


NCPanel::NCPanel(int height, int width, int y, int x):
	NCWidget(height, width, y, x)
{
	is_active = false;
	panel = new_panel( getWindow() );
	box(getWindow(), 0, 0);
}

void NCPanel::setActive(bool b)
{
	is_active = b;
	
	if ( b )
	{
		active_menu = widget->getMenu();
		active_win = widget->getWindow();
		activePanel = this;
	}

	else
	{
		inactivePanel = this;
	}
	
}

