#pragma once

#include <string>
#include <vector>

//! Pomocna trieda pre vygenerovanie prikazu, ktory sa ma spustit.
class Command
{
public:
	/*!
	 * \brief Vytvori instanciu prikazu.
	 * \param cmd aplikacia, ktora sa ma spusit
	*/
	explicit Command(const std::string & cmd):
		cmd(cmd)
	{}

	/*!
	 * \brief Prida novy argument.
	 * \param arg argument, ktory chceme pridat.
	*/
	inline void addArg(const std::string & arg)
	{
		args.push_back(arg);
	}

	/*!
	 * \brief Vybuduje prikaz, ktory je mozne predat dalej na spustenie.
	 * \return vygenerovany prikaz
	*/
	inline const std::string getCommand() const
	{
		std::string output = cmd;
		for (unsigned i = 0; i < args.size(); i++)
		{
			output += " ";
			output += args[i];
		}
		return output;
	}

private:
	std::string cmd;                ///< cesta k aplikacii a aplikacia
	std::vector<std::string> args;  ///< vektor argumentov

};

