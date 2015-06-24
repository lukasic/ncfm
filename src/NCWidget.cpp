#include "ncurses.h"
#include "panel.h"
#include "NCWidget.h"

void NCWidget::show()
{
	update_panels();
	doupdate();
	refresh();
}
