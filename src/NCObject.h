#pragma once

#include "ncurses.h"

//! Abstraktna trieda reprezentujuca NCurses objekt zobrazitelny na presne urcenej pozicii.
class NCObject
{
public:
	static const int AUTO_MAX = -1;  ///< maximalna hodnota

	/*!
     * \brief Inicializuje vnutorne struktury.
     * \param height vyska objektu
     * \param width sirka objektu
     * \param y pozicia y
     * \param x pozicia x
    */
	NCObject(int height, int width, int y, int x):
		_height(height), _width(width), _x(x), _y(y)
	{
		int max_width, max_height;
		getmaxyx(stdscr, max_height, max_width);

		if ( _height == AUTO_MAX )
			_height = max_height - y;
		if ( _width == AUTO_MAX )
			_width = max_width - x;
	}

	/*!
     * \brief Getter - sirka objektu.
     * \return int
    */
	int getWidth() const { return _width; }

	/*!
     * \brief Getter - vyska objektu
     * \return int
    */
	int getHeight() const { return _height; }

	/*!
     * \brief Getter - pozicia X
     * \return int
    */
	int getX() const { return _x; }

	/*!
     * \brief Getter - pozicia Y
     * \param int
    */
	int getY() const { return _y; }

private:

	int _height;  ///< vyska objektu
	int _width;   ///< sirka objektu
	int _x;       ///< pozicia X
	int _y;       ///< pozicia Y
};
