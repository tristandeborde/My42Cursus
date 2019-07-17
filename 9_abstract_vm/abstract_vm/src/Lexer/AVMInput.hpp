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
	std::string	getContent();
	void 		readStd();
	void 		readFile(char const **av);
	void 		printUsage(void);

private:
	AVMInput();
	AVMInput(const AVMInput &);
	AVMInput & operator=(const AVMInput &);
	std::string _content;
};

#endif
