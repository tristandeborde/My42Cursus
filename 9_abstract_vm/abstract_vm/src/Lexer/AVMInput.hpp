#ifndef AVMINPUT_HPP
# define AVMINPUT_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

class AVMInput {

public:
	AVMInput(int ac, char const **av);
	virtual ~AVMInput(void);
	AVMInput() = delete;
	AVMInput(const AVMInput &) = delete;
	AVMInput & operator=(const AVMInput &) = delete;
	
	std::string	getContent();
	void		read();
	void 		readStd();
	void 		readFile(char const **av);

private:
	std::string _content;
	int				_ac;
	const char**	_av;
};

#endif
