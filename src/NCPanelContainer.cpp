#include "NCPanel.h"
#include "NCFolderView.h"
#include "NCPanelContainer.h"


NCPanelContainer::NCPanelContainer(int height, int y, int panels):
	NCWidget(height, NCObject::AUTO_MAX, y, 0), current(0)
{
	wbkgd(getWindow(), COLOR_PAIR(1));

	for (int i = 0; i < panels; i++)
	{
		NCPanel * p = new NCPanel(getHeight(), getWidth()/panels, y, getWidth()/panels*i);
		NCFolderView * w = new NCFolderView(*p, ".");
		p->setWidget(w);
		mPanels.push_back(p);
	}
}

NCPanelContainer::~NCPanelContainer()
{
	for (unsigned i = 0; i < mPanels.size(); i++)
		delete mPanels[i];
	mPanels.clear();
}


void NCPanelContainer::changePanels()
{
	int curr = 0;
	for (curr = 0; curr < mPanels.size(); curr++)
	{
		MENU * menu = mPanels[curr]->getWidget()->getMenu();

		set_menu_grey(menu, COLOR_PAIR(5));
		set_menu_fore(menu, COLOR_PAIR(5));
		set_menu_back(menu, COLOR_PAIR(5));

		if ( mPanels[curr]->isActive() )
		{
			mPanels[curr]->setActive(false);
			break;
		}
	}

	curr = (curr+1) % mPanels.size();

	setActive( mPanels[curr] );
}

void NCPanelContainer::setActive(const NCPanel * panel)
{
	for (int i = 0; i < mPanels.size(); i++)
		if ( mPanels[i] == panel )
		{
			mPanels[i]->setActive(true);
			MENU * menu = mPanels[i]->getWidget()->getMenu();

			set_menu_grey(menu, COLOR_PAIR(3));
			set_menu_fore(menu, COLOR_PAIR(4));
			set_menu_back(menu, COLOR_PAIR(1));
			current = i;
			break;
		}
}
