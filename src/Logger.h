#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "constants.h"

//! Aplikacny logger. Moze byt pouzity aj ako Singleton.
class Logger
{
private:
	std::string logfile;  ///< nazov suboru, do ktoreho logujeme
	std::ofstream ofs;    ///< vystupny stream
	int level;            ///< log level


public:
	static const int ERROR    = 0;   ///< loglevel oznacujuci chyby
	static const int WARNING  = 1;   ///< loglevel oznacujuci upozornenia
	static const int INFO     = 2;   ///< loglevel oznacujuci informacne hlasky
	static const int DEBUG    = 4;   ///< loglevel zahrnajuci debug spravy

	static Logger * defaultLogger;   ///< singleton instancia

	/*!
	 * \brief Vytvori logger.
	 * \param logfile cesta k suboru, do ktoreho sa ma logovat.
	*/
	Logger(const std::string & logfile):
		logfile(logfile), ofs(logfile, std::fstream::out | std::fstream::app), level(Logger::INFO)
	{
		if ( ofs.bad() )
		{
			std::cerr << "Could not open logfile " << LOGFILE << "!" << std::endl;
			exit(1);
		}
	}

	~Logger() { ofs.close(); }

	/*!
	 * \brief Pristup k singleton instancii objektu.
	 * \return default logger
	*/
	static Logger & getDefault();


	/*!
	 * \brief Uzatvori default logger (singleton instanciu)
	*/
	static void closeDefault();


	/*!
	 * \brief Nastavi loglevel.
	 * \param hodnota log levelu
	*/
	void setLevel(int level)
	{
		this->level = level;
	}

	/*!
	 * \brief Zaloguje spravu na danom leveli.
	 * \param level log-level
	 * \param msg sprava na ulozenie do logu
	*/
	void log(int level, const std::string & msg)
	{
		if ( level > this->level ) return;
		ofs << msg << std::endl;
	}

	/*!
	 * \brief Vytvori zaznam v INFO logu.
	 * \param msg sprava, ktoru chceme ulozit do logu.
	*/
	inline void info(const std::string & msg)
	{
		log(Logger::INFO, msg);
	}

	/*!
	 * \brief Vytvori zaznam v ERROR logu.
	 * \param msg sprava, ktoru chceme ulozit do logu.
	*/
	inline void error(const std::string & msg)
	{
		log(Logger::ERROR, msg);
	}

	/*!
	 * \brief Vytvori zaznam vo WARNING logu.
	 * \param msg sprava, ktoru chceme ulozit do logu.
	*/
	inline void warning(const std::string & msg)
	{
		log(Logger::WARNING, msg);
	}

	/*!
	 * \brief Vytvori zaznam v DEBUG logu.
	 * \param msg sprava, ktoru chceme ulozit do logu.
	*/
	inline void debug(const std::string & msg)
	{
		log(Logger::DEBUG, msg);
	}

};
