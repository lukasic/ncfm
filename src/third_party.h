#pragma once

#include <string>

/*!
 * \brief Spusti prikaz v systeme a ziska jeho vystup.
 *
 * Povodny zdroj: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
 *
 * \param argCmd prikaz, ktory sa ma spustit
 * \param err volitelny parameter - zachytit aj chybovy vystup (default false)
 * \return string vystup prikazu
*/
std::string exec(const std::string & cmd, bool err = false);

