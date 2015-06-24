#pragma once

#include "NCWidget.h"
#include "NCFolderView.h"
#include "panel.h"

//! Widget reprezentujuci panel - obalujuci FolderView alebo jemu podobnu strukturu.
class NCPanel : public NCWidget
{
public:
	/*!
     * \brief Vytvori instanciu NCPanelu na zadanych poziciach o zadanych rozmeroch.
     * \param heigh vyska
     * \param width sirka
     * \param x x-pozicia
     * \param y y-pozicia
    */
	NCPanel(int height, int width, int y, int x);
	
	virtual ~NCPanel() {}

	/*!
     * \brief Nastavi panel ako aktivny alebo neaktivny.
     * \param boolean
    */
	void setActive(bool b);

	/*!
     * \brief Getter - zisti, ci je panel aktivny alebo nie.
     * \return boolean
    */
    
	inline bool isActive() const 
	{
		return is_active;
	}

	/*!
     * \brief Getter - vrati panel, do ktoreho sa widget zobrazuje.
     * \return PANEL
    */
	inline PANEL * getPanel() const {
		return panel;
	}

	/*!
     * \brief Nastavi widget, ktory sa ma v paneli zobrazovat.
     * \param widget
    */
	inline void setWidget(NCFolderView * widget)
	{
		this->widget = widget;
	}

	/*!
     * \brief Zisti, ci polozka s danym menom je priecinok/symlink/archiv.
     * \return NCPanelWidget
    */
	inline NCFolderView * getWidget() const {
		return this->widget;
	}


private:
	PANEL *panel;            ///< panel, do ktoreho zobrazujeme widget
	bool is_active;          ///< aktivny/neaktivny panel
	NCFolderView * widget;   ///< widget, ktory sa zobrazuje
};

