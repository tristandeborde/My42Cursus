#include "AVMInput.hpp"
#include "Exceptions/Exceptions.hpp"

AVMInput::AVMInput(int ac, char const **av): _ac(ac), _av(av)
{
	return;
}

AVMInput::~AVMInput(void) {
	return;
}

void		AVMInput::read() {
	if (this->_ac == 1)
		this->readStd();
	else if (this->_ac == 2)
		this->readFile(this->_av);
	else
		throw(badUsageException());
	return;
}

void		AVMInput::readStd(void)
{
	std::string 		line;
	std::stringstream	stream;

	while (std::getline(std::cin, line))
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
		throw(noFileException());
}

std::string AVMInput::getContent(void)
{
	return (this->_content);
}
