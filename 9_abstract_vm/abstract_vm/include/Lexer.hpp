#ifndef LEXER_HPP
# define LEXER_HPP

# include <map>
# include <vector>
# include <string>
# include "Token.hpp"

class Lexer {

public:

	Lexer(void);
	virtual ~Lexer(void);

	void	findTokenType(const std::string &identifier, int TokenType);
    void	findToken(const std::string &identifier, int line_nb);
	void	readLine(const std::string &line);
    void 	handleVar(const std::string &identifier, size_t fst_par, int line_nb);

	class badSyntaxException: public std::exception
	{
	public:
		virtual const char* what(int line_nb) const throw();
	};

    enum TokenType {
    	exit = 1,
        dump,
        push,
        pop,
        assert,
        add,
        sub,
        mul,
        div,
        mod,
        print,
    	int8,
    	int16,
    	int32,
    	flt,
    	dbl,
        error
    };

private:

	Lexer(const Lexer &);
	Lexer & operator=(const Lexer &);
    std::map<std::string, Lexer::TokenType> p_authorized_instr;
	std::map<std::string, Lexer::TokenType> p_authorized_var;
    std::vector<Token::Token>               p_tokens;
	std::vector<Token::Token>               p_errors;
};

#endif
