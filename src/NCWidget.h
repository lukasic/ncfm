#pragma once

#include "NCObject.h"
#include "ncurses.h"

//! Zobrazitelny NCurses objekt. Base-class pre specializovane objekty.
class NCWidget : public NCObject
{
public:

	NCWidget(int height, int width, int y, int x):
		NCObject(height, width, y, x)
	{
		win = newwin(getHeight(), getWidth(), getY(), getX());
	}

	inline WINDOW* getWindow()
	{
		return win;
	}

	inline void setBorder(int vert, int hor)
	{
		box(win, vert, hor);
	}

	inline void redraw() const
	{
		redrawwin(win);
		wrefresh(win);
	}

	virtual void show();

protected:
	WINDOW *win;

};
