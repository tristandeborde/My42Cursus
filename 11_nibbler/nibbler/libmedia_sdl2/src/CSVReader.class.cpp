#include "CSVReader.class.hpp"
#include "Exception.class.hpp"
#include <fstream>

CSVReader::CSVReader(std::string &filename) :
	_file_name(filename) {}

static void split(std::vector<std::string> &vec, std::string &s, const std::string &delm) {
	size_t pos = 0;

	while ((pos = s.find(delm)) != std::string::npos) {
		vec.push_back(s.substr(0, pos));
		s.erase(0, pos + delm.length());
	}
	vec.push_back(s.substr(0, pos));
}

std::vector<std::vector<std::string> > CSVReader::getData(bool header) const{
	std::ifstream file(_file_name);
	std::vector<std::vector<std::string> > data_list;
	std::string line;

	if (!file) {
		throw Exception("Error opening CSV file");
	}

	while (getline(file, line)) {
		if (header == true) {
			header = false;
			continue;
		}
		std::vector<std::string> vec;
		split(vec, line, this->_delimeter);
		data_list.push_back(std::move(vec));
	}
	file.close();
	return data_list;
}
