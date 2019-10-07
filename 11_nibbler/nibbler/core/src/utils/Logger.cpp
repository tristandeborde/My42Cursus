#include "Logger.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <ctime>
#include <iomanip>
#include <string>

#include <thread>
#include <mutex>
#include <chrono>

namespace Logger
{
	namespace
	{
		std::ostream * log_stream	= nullptr;
		std::string * filename		= nullptr;
		std::thread * chrono_thread = nullptr;
		std::chrono::steady_clock::time_point * last = nullptr;
		bool chrono_thread_run		  = false;
		std::mutex * mlock			  = nullptr;
		std::string * log_base_folder = nullptr;

		void			create_log_dir() {
			struct stat statbuff {};

			if (stat(log_base_folder->c_str(), &statbuff) == 0) {
				if (S_ISDIR(statbuff.st_mode) == 0) {
					throw LoggerException(*log_base_folder + " exists and is not a folder");
				}
			}
			else {
				char * error_stat = strerror(errno);

				if (mkdir(log_base_folder->c_str(), 0775) == -1) {
					char * error_mkdir = strerror(errno);
					std::stringstream ss;

					ss << "fail to create .logs file, ";

					ss << "stat error : " << error_stat << ", ";
					ss << "mkdir error : " << error_mkdir << ".";
					throw LoggerException(ss.str());
				}
			}
		}

		std::string		build_date() {
			std::stringstream ss;
			time_t t;
			struct tm now {};

			t = time(nullptr);
			localtime_r(&t, &now);

			// Year
			ss << (now.tm_year + 1900) << "-";

			// Month
			ss << std::setfill('0') << std::setw(2)
			   << (now.tm_mon + 1) << "-";

			// Day
			ss << std::setfill('0') << std::setw(2)
			   << now.tm_mday << " ";

			// Hour
			ss << std::setfill('0') << std::setw(2)
			   << now.tm_hour << ":";

			// Min
			ss << std::setfill('0') << std::setw(2)
			   << now.tm_min << ":";

			// Sec
			ss << std::setfill('0') << std::setw(2)
			   << now.tm_sec;

			return (ss.str());
		}	// build_date

		std::string		build_header() {
			std::string res;

			for (size_t i = 0; i < 80; i++)
				res += "#";
			res += "\n";
			for (size_t i = 0; i < 5; i++)
				res += "#";
			for (size_t i = 5; i < 75; i++)
				res += " ";
			for (size_t i = 75; i < 80; i++)
				res += "#";
			res += "\n";
			for (size_t i = 0; i < 5; i++)
				res += "#";
			for (size_t i = 5; i < 34; i++)
				res += " ";
			res += "BOMBLER  LOG";
			for (size_t i = 46; i < 75; i++)
				res += " ";
			for (size_t i = 75; i < 80; i++)
				res += "#";
			res += "\n";
			for (size_t i = 0; i < 5; i++)
				res += "#";
			for (size_t i = 5; i < 75; i++)
				res += " ";
			for (size_t i = 75; i < 80; i++)
				res += "#";
			res += "\n";
			for (size_t i = 0; i < 80; i++)
				res += "#";
			res += "\n\n";
			res += "[" + build_date() + "]\n";
			res += "  Bombler initialized\n";
			res += "  Logger ok\n";
			return (res);
		}	// build_header

		std::string		build_tag_prefix(const std::string & tag, bool dashx3 = true) {
			std::string prefix;

			prefix = tag + " " + build_date();
			if (dashx3)
				prefix += " --- ";
			return (prefix);
		}

		std::string		build_prefix(eLogType type) {
			std::string	tag;

			switch (type) {
				case eLogType::Debug:
					tag = "[ DEBUG ]";
					break;
				case eLogType::Info:
					tag = "[ INFO  ]";
					break;
				case eLogType::Warning:
					tag = "[ WARN  ]";
					break;
				case eLogType::Error:
					tag = "[ ERROR ]";
					break;
				case eLogType::Libmedia:
					tag = "[  LIB  ]";
					break;
			}
			return (build_tag_prefix(tag));
		}

		void			rotate_log(size_t line_size) {
			std::lock_guard<std::mutex> guard(*mlock);
			auto * ofstream = dynamic_cast<std::ofstream *>(log_stream);
			std::string file;

			// check size
			if (static_cast<size_t>(log_stream->tellp()) + line_size < Max_filesize * 1024 * 1024) {
				return;
			}
			// close current
			ofstream->close();
			// try to delete oldest log file
			file = *filename + ".log";
			if (Max_files > 1)
				file = *filename + "_" + std::to_string(Max_files - 1) + ".log";
			std::remove(file.c_str());
			// rotate all log files
			for (int i = Max_files - 1; i > 0; i--) {
				std::rename((*filename + "_" + std::to_string(i - 1) + ".log").c_str(),
				  (*filename + "_" + std::to_string(i) + ".log").c_str());
			}
			// rename latest logfile
			if (Max_files > 1)
				std::rename((*filename + ".log").c_str(), (*filename + "_" + std::to_string(1) + ".log").c_str());
			// open new
			ofstream->open(*filename + ".log");
			if (ofstream->is_open() == false) {
				delete ofstream;
				throw LoggerException("Fail open new log file");
			}
			log_stream = ofstream;
		}

		void			log_effective(const std::string &msg) {
			std::lock_guard<std::mutex> guard(*mlock);

			*last = std::chrono::steady_clock::now();
			*log_stream << msg << std::endl;
		}

		void			main_chrono_thread(void) {
			auto one_sec   = ++std::chrono::seconds::zero();
			auto threshold = std::chrono::seconds(Threshold_idle);

			while (true) {
				{
					std::lock_guard<std::mutex> guard(*mlock);

					if (chrono_thread_run == false)
						return;
				}

				std::this_thread::sleep_for(one_sec);
				if (std::chrono::steady_clock::now() - *last > threshold)
					log_effective(build_tag_prefix("[ IDLE  ]", false));
			}
		}
	}	// namespace

	void	init() {
		std::ofstream * ofstream;

		log_base_folder	  = new std::string(BASEPATH);
		*log_base_folder += "/.logs/";

		last  = new std::chrono::steady_clock::time_point();
		mlock = new std::mutex();

		static_assert(Max_files >= 1, "Max_files needs to be at least 1");
		if (log_stream != nullptr)
			throw LoggerException("The init function has already been called");
		create_log_dir();
		filename = new std::string(*log_base_folder + build_date());
		ofstream = new std::ofstream();
		ofstream->open(*filename + ".log");
		if (ofstream->is_open() == false) {
			delete ofstream;
			throw LoggerException("Fail open the file");
		}
		log_stream = ofstream;

		*last = std::chrono::steady_clock::now();
		chrono_thread_run = true;
		if ((chrono_thread = new std::thread(main_chrono_thread)) == nullptr) {
			throw LoggerException("Cannot start chrono thread");
		}

		log_effective(build_header());
	}

	void	end() {
		if (log_stream == nullptr)
			return;

		{
			std::lock_guard<std::mutex> guard(*mlock);
			chrono_thread_run = false;
		}

		chrono_thread->join();
		delete chrono_thread;
		chrono_thread = nullptr;

		dynamic_cast<std::ofstream *>(log_stream)->close();
		delete log_stream;
		delete filename;
		delete last;
		delete mlock;
		delete log_base_folder;
		filename		= nullptr;
		mlock			= nullptr;
		last			= nullptr;
		log_stream		= nullptr;
		log_base_folder = nullptr;
	}

	void	log(eLogType type, const std::string & msg) {
		std::string	line;
		std::string	treated_msg;
		std::string::size_type pos;

		treated_msg = msg;
		pos			= 0;
		while ((pos = treated_msg.find('\n', pos)) != std::string::npos)
			treated_msg.replace(pos, 1, "\\n");
		pos = 0;
		while ((pos = treated_msg.find('\r', pos)) != std::string::npos)
			treated_msg.replace(pos, 1, "\\r");
		line = build_prefix(type) + treated_msg;
		rotate_log(line.size());
		log_effective(line);
	}
}	// namespace Logger
