#include "AVMInput.hpp"

AVMInput::AVMInput(int ac, char const **av)
{
	if (ac == 1)
		this->readStd();
	else if (ac == 2)
		this->readFile(av);
	else
		this->printUsage();
	return;
}

AVMInput::~AVMInput(void) {
	return;
}

void		AVMInput::readStd(void)
{
	std::string 		line;
	std::stringstream	stream;

	while (std::getline(std::cin, line) != 0)
	{
		stream << line << std::endl;
		if (!line.compare(";;"))
			break;
	}
	this->_content = stream.str();
}

void		AVMInput::readFile(char const **av)
{
	std::string filename(av[1]);
	std::ifstream file(filename);
	std::stringstream stream;

	if(file.is_open())
	{
		stream << file.rdbuf();
		this->_content = stream.str();
		file.close();
	}
	else
		std::cout << "Unable to open file";
}

void 		AVMInput::printUsage()
{
	this->_content = "usage: ./avm [./input_file]";
}

std::string AVMInput::getContent(void)
{
	return (this->_content);
}
