#pragma once

#include <string>
#include <iostream>

//! Pomocna trieda pre vynimky v grafickom rozhrani.
class NCException
{
private:
	std::string msg;  ///< Informacie o vynimke.

public:
	/*!
	 * \brief Vytvori instanciu vynimky.
	 * \param msg informacie o vynimke.
	*/
	NCException(const std::string & msg): msg(msg) {}

};

