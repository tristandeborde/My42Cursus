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
	void 		readStd();
	void 		readFile(char const **av);
	void 		printUsage(void);

private:
	std::string _content;
};

#endif
