#include "op.h"
#include "token.h"
#include "object.h"
#include "re.h"
#include "concatenation.h"
#include "simple_re.h"
#include "basic_re.h"
#include "elementary_re.h"
#include "character.h"
#include "program.h"
#include "any.h"
#include "group.h"
#include "star.h"
#include "count.h"

#include <iostream>
#include <string>
#include <fstream>	//To read file
#include <streambuf>	//To read file

//https://stackoverflow.com/questions/265457/regex-grammar
/* BNF Grammar of Regular Expressions
<program_parse>     ::=     <RE>
<RE>                ::=     <simple-RE>
<simple-RE>         ::=     <concatenation> | <basic-RE>
<concatenation>     ::=     <basic-RE> <simple-RE>
<basic-RE>          ::=     <star> | <count> | <elementary-RE>
<elementary-RE>     ::=     <character> | <group> | <any>
<star>              ::=     <elementary-RE> "*"
<count>             ::=     <elementary-RE> "{" digits "}"
<character>         ::=     any non metacharacter
<group>             ::=     "(" <RE> ")"
<any>               ::=     "."
*/

/*
+ eller, passar ett av två alternativ. Syntax: OP1+OP2
* flera, passar ett eller flera upprepningar av en operand. Syntax: OP*
() infångningsgrupp, deluttryck. Uttrycket parsas separat. Syntax: (EXPR)
. tecken. matchar varlfritt tecken. Syntax: .
{} räknare. matchar precis N stycken operander. Syntax: OP{3}
*/

using IT = std::string::iterator;

//Functions to create regex tree
op* program_parse(IT& first, IT& last);
op* regExp(IT& first, IT& last);
op* simple_re_expr(IT& first, IT& last);
op* concatenation_expr(IT& first, IT& last);
op* basic_re_expr(IT& first, IT& last);
op* star_expr(IT& first, IT& last);
op* count_expr(IT& first, IT& last);
op* elementary_re_expr(IT& first, IT& last);
op* character_expr(IT& first, IT& last);
op* group_expr(IT& first, IT& last);
op* any_expr(IT& first, IT& last);

//Prints parse tree
void print(op* op, size_t i = 0);

//Runs parse tree
void execute(op* parse_tree, std::string source);

op* program_parse(IT& first, IT& last) {
	//If the regex is empty
	if (first == last) {
		return nullptr;
	}
	program* expr = new program;
	op* program_parse_child = regExp(first, last);
	expr->operands.push_back(program_parse_child);
	return expr;
}
op* regExp(IT& first, IT& last) {
	//Create empty child node
	op* regExp_child = nullptr;

	//TODO substitute rule
	//op* substitute_or_simple = substitute_expr(first, last);

	//Check if <simple-RE>
	if (!regExp_child) {
		regExp_child = simple_re_expr(first, last);
	}

	re* expr = new re;
	expr->operands.push_back(regExp_child);
	return expr;
}
op* simple_re_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Create child node
	op* simple_re_child = nullptr;

	//Check if basic-RE first
	simple_re_child = basic_re_expr(first, last);

	//If <basic-RE> did not enclose the whole expression
	//Try for <concatenation>
	if (first != last) {
		first = start;
		simple_re_child = concatenation_expr(first, last);
	}

	//If neither
	if (!simple_re_child) {
		first = start;
		return nullptr;
	}

	simple_re* expr = new simple_re;
	expr->operands.push_back(simple_re_child);
	return expr;
}
op* concatenation_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Create <concatenation> child node
	op* concatenation_child = nullptr;

	op* basic_re_op = basic_re_expr(first, last);
	//If first operand is not <basic-RE>
	if (!basic_re_op) {
		first = start;
		return nullptr;
	}

	op* simple_re_op = simple_re_expr(first, last);
	//If second operand is not <simple-RE>
	if (!simple_re_op) {
		first = start;
		return nullptr;
	}

	concatenation* expr = new concatenation;
	expr->operands.push_back(basic_re_op);
	expr->operands.push_back(simple_re_op);
	return expr;
}
op* basic_re_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Create empty child node
	op* basic_re_child = nullptr;

	//Check <basic-RE> is an <elementary-RE>
	if (!basic_re_child) {
		basic_re_child = elementary_re_expr(first, last);
	}

	//Check if <elementary-RE> is followed by syntax
	if (first != last) {
		token syntax_token = next_token(first, last);

		//Check <basic-RE> is an <star>
		if (syntax_token.id == token::STAR) {
			first = start;
			basic_re_child = star_expr(first, last);
			first++;
		}
		//Check <basic-RE> is an <count>
		if (syntax_token.id == token::LEFT_BRACKET) {
			first = start;
			basic_re_child = count_expr(first, last);

		}
	}

	//If failed to find basic-RE
	if (!basic_re_child) {
		first = start; 
		return nullptr;
	}

	basic_re* expr = new basic_re;
	expr->operands.push_back(basic_re_child);
	return expr;
}
op* star_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	op* star_child = nullptr;
	star_child = elementary_re_expr(first, last);

	star* expr = new star;
	expr->operands.push_back(star_child);
	return expr;
}
op* count_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	op* count_child = nullptr;
	count_child = elementary_re_expr(first, last);

	//Save digits in <count> {"123123"}
	std::string counttext = "";

	//Jump over first left bracket
	first++;

	token syntax_token = next_token(first, last);
	while (syntax_token.id == token::ID) {
		counttext.append(syntax_token.text);
		first++;
		syntax_token = next_token(first, last);
	}
	if (syntax_token.id == token::RIGHT_BRACKET) {
		first++;
	}
	else {
		std::cout << "Could not close <count> " << std::endl;
		return nullptr;
	}

	count* expr = new count;
	expr->countAmount = std::stoi(counttext);
	expr->operands.push_back(count_child);
	return expr;
};
op* elementary_re_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Create <elementary-RE> child node
	op* elementary_re_child = nullptr;

	//Check if <elementary-RE> is <character>
	if (!elementary_re_child){
		elementary_re_child = character_expr(first, last);
	}

	//Check if <elementary-RE> is <any>
	if (!elementary_re_child) {
		elementary_re_child = any_expr(first, last);
	}

	//Check if <elementary-RE> is <group>
	if (!elementary_re_child){
		elementary_re_child = group_expr(first, last);
	}	

	//If failed to find elementary_re
	if (!elementary_re_child) {
		first = start; 
		return nullptr;
	}

	elementary_re* expr = new elementary_re;
	expr->operands.push_back(elementary_re_child);
	return expr;
};
op* character_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Get token
	token char_token = next_token(first, last);
	character* expr = new character;

	//If character is a non metacharacter, append the text to <character> node and check next character
	if(char_token.id == token::ID) {
		expr->_id.append(char_token.text);
		first++;
	}

	//If we did not find any characters
	if (start == first) {
		return nullptr;
	}

	return expr;
};
op* group_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	IT prev_end = last;
	prev_end--;
	IT end = last;

	//Get token & return nullptr if not "("
	token par_token = next_token(first, last);
	if (par_token.id != token::LEFT_PARENTHESES) {
		return nullptr;
	}
	first++;

	while (first != end) {
		par_token = next_token(prev_end, end);
		if (par_token.id != token::RIGHT_PARENTHESES) {
			end--;
			prev_end--;
		}
		else {
			end--;
			break;
		}
	}

	//Check if group contains valid regex
	op* group_child = regExp(first, end);
	if (!group_child) {
		first = start;
		return nullptr;
	}

	//Get token & return nullptr if not ")"
	par_token = next_token(first, last);
	if (par_token.id != token::RIGHT_PARENTHESES) {
		return nullptr;
	}
	first++;

	group* expr = new group;
	expr->operands.push_back(group_child);
	return expr;
};
op* any_expr(IT& first, IT& last) {
	//Get token
	token any_token = next_token(first, last);

	//If token is <any>
	if(any_token.id == token::ANY){
		first++;
		any* expr = new any;
		return expr;
	}

	//If token is not <any>
	return nullptr;
};

//Print parse tree
void print(op* op, size_t i) {

	//Prints space for indentation
	i++;
	for (size_t j = 0; j < i; j++) {
		std::cout << " |";
	}

	//Print class name
	std::cout << op->id() << " ";
	//std::cout << op->operands.size();
	std::cout << std::endl;

	//Iterate into class operands
	for (size_t childNode = 0; childNode < op->operands.size(); childNode++) {
		print(op->operands[childNode], i);
	}
}

//Executes parse tree
void execute(op* parse_tree, std::string source) {
	//Create new object of source string
	object* obj = new object;
	obj->lhs = source.begin();
	obj->rhs = source.begin();
	obj->end = source.end();

	//Evaluate parse tree on source string
	object* parse = parse_tree->eval(obj);

	//If we got a valid parse, print it
	if (parse != nullptr) {
		while (parse->lhs != parse->rhs) {
			std::cout << *parse->lhs;
			parse->lhs++;
		}
		std::cout << std::endl;
		std::cout << std::endl << "EXIT_SUCCESS" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cerr << std::endl << "EXIT_FAILURE" << std::endl;
	}
}


int main(int argc, char* argv[]) {

	//Standards incase no command line arguments
	std::string text = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
	std::string input = ".*";

	//If we get a regex
	if (argc > 1) {
		input = argv[1];
	}

	//If we get a text
	if (argc > 2) {
		std::string fileName = argv[2];
		std::ifstream f(fileName);
		text.assign((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
	}

	//Get iterators to begin and end of text
	IT begin = input.begin();
	IT end = input.end();

	//Create parse tree
	op* result = program_parse(begin, end);
	
	//Print text
	std::cout << "Text string:" << std::endl;
	std::cout << text << std::endl << std::endl;

	//Print regex
	std::cout << "Regular Expression:" << std::endl;
	std::cout << input << std::endl << std::endl;

	//Print regex tree
	std::cout << "Parse tree:" << std::endl;
	print(result);
	std::cout << std::endl;
	
	//Print result of regex tree on text
	std::cout << "Result of executed regex:" << std::endl;
	execute(result, text);
	std::cout << std::endl;
}