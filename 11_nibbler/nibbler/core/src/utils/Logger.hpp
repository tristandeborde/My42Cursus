#ifndef LOGGER_CLASS_HPP
#define	LOGGER_CLASS_HPP

#include <fstream>
#include <sstream>
#include <string>

#include "exceptions/LoggerException.class.hpp"

#ifndef BASEPATH

// not a constexpr value because it can be changed at compilation threw the -D flag
# define	BASEPATH "./"

#endif	// #ifndef BASEPATH

constexpr int Threshold_idle  = 5;
constexpr size_t Max_filesize = 128;// Mb
constexpr int Max_files		  = 2;

enum class eLogType{
	Debug,
	Info,
	Warning,
	Error,
	Libmedia
};

namespace Logger
{
	void			init();
	void			end();

	void log(eLogType, const std::string & msg);
}	// namespace Logger

template <typename T>
void		__build_ss_recu(std::stringstream &ss, const T &arg) {
	ss << ' ' << arg;
}

template <typename T, typename ... U>
void		__build_ss_recu(std::stringstream &ss, const T &arg, const U & ... args) {
	ss << ' ' << arg;
	__build_ss_recu(ss, args ...);
}

template <typename T, typename ... U>
void		LOG(eLogType t, T arg, U ... args) {
	std::stringstream ss;

	ss << arg;
	__build_ss_recu(ss, args ...);
	Logger::log(t, ss.str());
}

template <typename T>
void		LOG(eLogType t, T arg) {
	std::stringstream ss;

	ss << arg;
	Logger::log(t, ss.str());
}

#endif	// ifndef LOGGER_CLASS_HPP
