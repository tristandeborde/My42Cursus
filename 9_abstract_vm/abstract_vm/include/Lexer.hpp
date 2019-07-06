#ifndef LEXER_HPP
# define LEXER_HPP

# include <map>
# include <vector>
# include <string>
# include <sstream>
# include "TokenType.hpp"
# include "Token.hpp"
# include "LexerExceptions.hpp"
# include "MapHelper.hpp"

// Performs a lexical analysis of the provided code.


class Lexer {

public:

	Lexer(void);
	virtual ~Lexer(void);
	Lexer(const Lexer &) = delete;
	Lexer & operator=(const Lexer &) = delete;

	void		checkTokens(void);
	TokenType	findTokenType(const std::string &identifier);
	void 		handleVar(const std::string &identifier, size_t fst_par, int line_nb);
    void 		handleInstr(const std::string &identifier, int line_nb);
	void		findToken(const std::string &identifier, int line_nb);
	void		readLine(const std::string &line, int line_nb);
	void 		readLines(const std::string &lines);

private:

    std::map<std::string, TokenType> 		p_authorized_tokens;
    std::vector<Token::Token>               p_tokens;
};

#endif
