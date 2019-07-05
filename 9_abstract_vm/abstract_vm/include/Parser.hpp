#ifndef PARSER_HPP
# define PARSER_HPP

class Parser {

public:

	Parser(void);
	virtual ~Parser(void);

private:
	
	Parser & operator=(const Parser &);
	Parser(const Parser &);

};

#endif
