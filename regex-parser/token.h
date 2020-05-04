#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using IT = std::string::iterator;

struct token {
	enum id {
		PLUS,
		STAR,
		ANY,
		LEFT_PARENTHESES,
		RIGHT_PARENTHESES,
		LEFT_BRACKET,
		RIGHT_BRACKET,
		BACKSLASH,
		ID,
		END_PROGRAM
	};
	id id = id::ID;
	std::string text = "";
};

token next_token(IT& first, IT& last) {
	if (first == last) {
		return token{ token::END_PROGRAM, ""};
	}

	token tk;

	switch (*first) {
		case '+':
			tk = { token::PLUS, "+" };
			break;
		case '*':
			tk = { token::STAR, "*" };
			break;
		case '.':
			tk = { token::ANY, "." };
			break;
		case '(':
			tk = { token::LEFT_PARENTHESES, "(" };
			break;
		case ')':
			tk = { token::RIGHT_PARENTHESES, ")" };
			break;
		case '{':
			tk = { token::LEFT_BRACKET, "{" };
			break;
		case '}':
			tk = { token::RIGHT_BRACKET, "}" };
			break;
		case '\\':
			tk = { token::BACKSLASH, "\\" };
			break;
		default:
			tk = { token::ID, std::string(first, first + 1) };
	}
	return tk;
}

#endif