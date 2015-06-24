#pragma once

#include <vector>
#include "NCPanel.h"
#include "NCWidget.h"

//! Widget, ktory obsahuje jednotlive instancie panelov.
class NCPanelContainer : public NCWidget
{
public:

	/*!
	 * \brief Vytvori kontajner o zadanej sirke so zadanym poctom panelov.
	 * \param height sirka celeho kontajneru
	 * \param y vertikalna pozicia pre umiestnenie kontajneru
	*/
	NCPanelContainer(int height, int y, int panels);

	~NCPanelContainer();

	/*!
	 * \brief Nastavi dalsi panel ako aktivny.
	*/
	void changePanels();

	/*!
	 * \brief Nanovo vykresli vsetky panely.
	*/
	void redraw() const
	{
		NCWidget::redraw();
		for (unsigned i = 0; i < mPanels.size(); i++)
		{
			mPanels[i]->redraw();
		}
	}

	/*!
	 * \brief Nastavi panel ako aktivny.
	 * \param panel Pointer na NCPanel, ktory chceme nastavit ako aktivny.
	*/
	void setActive(const NCPanel * panel);

	/*!
	 * \brief Vrati working directory z dalsieho panela.
	 * \return working directory dalsieho panela
	*/
	inline const std::string  getNextPanelPath() const
	{
		int next = (current+1) % mPanels.size();
		return mPanels[next]->getWidget()->getCurrentPath();
	}


private:
	std::vector<NCPanel*> mPanels;  ///< odkazy na instancie jednotlivych panelov
	int current;                    ///< index do mPanels oznacujuci aktivny panel
};
 
