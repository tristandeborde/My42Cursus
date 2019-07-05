#include "Parser.hpp"

Parser::Parser(void) {
	return;
}

Parser::Parser(const Parser &) {
	*this = src;
	return;
}

Parser::~Parser(void) {
	return;
}

Parser & Parser::operator=(const Parser &) {
	return *this;
}

