#include "op.h"
#include "token.h"
#include "object.h"
#include "re.h"
#include "substitute.h"
#include "concatenation.h"
#include "simple_re.h"
#include "basic_re.h"
#include "elementary_re.h"
#include "character.h"
#include "program.h"
#include "any.h"
#include "group.h"

#include <iostream>
#include <string>

//https://stackoverflow.com/questions/265457/regex-grammar
/* BNF Grammar of Regular Expressions
<program_parse>     ::=     <RE>
<RE>                ::=     <substitute> | <simple-RE>
<substitute>        ::=     <simple-RE> "+" <RE>
<simple-RE>         ::=     <concatenation> | <basic-RE>
<concatenation>     ::=     <basic-RE> <simple-RE>
<basic-RE>          ::=     <star> | <count> | <lowercase> | <capturegroup> | <elementary-RE>
<elementary-RE>     ::=     <character> | <group> | <any>
<star>              ::=     <elementary-RE> "*"
<lowercase>         ::=     <elementary-RE> \I
<capturegroup>      ::=     <elementary-RE> \O <count>
<count>             ::=     <elementary-RE> "{" <digit> "}"
<character>         ::=     any non metacharacter | "\" metacharacter
<group>             ::=     "(" <RE> ")"
<digit>             ::=     "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>               ::=     "."
*/

/*
+ eller, passar ett av två alternativ. Syntax: OP1+OP2
* flera, passar ett eller flera upprepningar av en operand. Syntax: OP*
() infångningsgrupp, deluttryck. Uttrycket parsas separat. Syntax: (EXPR)
. tecken. matchar varlfritt tecken. Syntax: .
{} räknare. matchar precis N stycken operander. Syntax: OP{3}
\I ignorera versalisering. Syntax EXPR\I
\O{} vilken infångningsgrupp som ska ges som output. Syntax: EXPR\O{2}. Default \O{0} hela matchningen.
*/

using IT = std::string::iterator;

op* program_parse(IT& first, IT& last);

//<program_parse>     ::=     <RE>
op* regExp(IT& first, IT& last);

//<RE>                ::=     <substitute> | <simple-RE>
op* substitute_expr(IT& first, IT& last); //TODO
op* simple_re_expr(IT& first, IT& last);

//<simple-RE>         ::=     <concatenation> | <basic-RE>
op* concatenation_expr(IT& first, IT& last);	//TODO
op* basic_re_expr(IT& first, IT& last);

//<basic-RE>          ::=     <star> | <count> | <lowercase> | <capturegroup> | <elementary-RE>
op* star_expr(IT& first, IT& last);	//TODO
op* counter_expr(IT& first, IT& last);	//TODO
op* lowercase_expr(IT& first, IT& last);	//TODO
op* capturegroup_expr(IT& first, IT& last);	//TODO
op* elementary_re_expr(IT& first, IT& last);

//<elementary-RE>     ::=     <character> | <group> | <any>
op* character_expr(IT& first, IT& last);
op* group_expr(IT& first, IT& last);
op* any_expr(IT& first, IT& last);

op* digit_expr(IT& first, IT& last);	//TODO

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
	op* re = regExp(first, last);
	expr->operands.push_back(re);
	return expr;
}

op* regExp(IT& first, IT& last) {
	//TODO substitute rule
	//op* substitute_or_simple = substitute_expr(first, last);
	op* substitute_or_simple = NULL;

	//Check if substitute or simple
	if (!substitute_or_simple) {
		substitute_or_simple = simple_re_expr(first, last);
	}

	re* expr = new re;
	expr->operands.push_back(substitute_or_simple);
	return expr;
}

//TODO
op* substitute_expr(IT& first, IT& last) {
	return nullptr;
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

	op* basic_re_child = nullptr;	//basic = star | count | lowercase | capturegroup | elementary_re
	//if (!basic) { basic = star_expr(first, last); }			//TODO
	//if (!basic) { basic = counter_expr(first, last); }		//TODO
	//if (!basic) { basic = lowercase_expr(first, last); }		//TODO
	//if (!basic) { basic = capturegroup_expr(first, last); }	//TODO

	//Check <basic-RE> is an <elementary-RE>
	if (!basic_re_child){
		basic_re_child = elementary_re_expr(first, last);
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

//TODO
op* star_expr(IT& first, IT& last) {
	return nullptr;
}

//TODO
op* counter_expr(IT& first, IT& last) {
	return nullptr;
};

//TODO
op* lowercase_expr(IT& first, IT& last) {
	return nullptr;
};

//TODO
op* capturegroup_expr(IT& first, IT& last) {
	return nullptr;
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
		//char_token = next_token(first, last);
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

//TODO
op* digit_expr(IT& first, IT& last) {
	return nullptr;
}

//Print parse tree
void print(op* op, size_t i) {

	//Prints space for indentation
	i++;
	for (size_t j = 0; j < i; j++) {
		std::cout << " |";
	}

	//Print class name
	std::cout << op->id() << " " << op->operands.size() << std::endl;

	//Iterate into class operands
	for (size_t childNode = 0; childNode < op->operands.size(); childNode++) {
		print(op->operands[childNode], i);
	}
}

//Executes parse tree
void execute(op* parse_tree, std::string source) {
	object* obj = new object;
	obj->lhs = source.begin();
	obj->rhs = source.begin();
	obj->end = source.end();

	object* parse = parse_tree->eval(obj);

	if (parse != nullptr) {
		for (; parse->lhs != parse->rhs; parse->lhs++) {
			std::cout << *parse->lhs;
		}
	}
	else {
		std::cerr << "EXIT FAILURE." << std::endl;
	}
}


int main() {

	std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
	std::string input = "(o.o)";

	//Get iterators to begin and end
	IT begin = input.begin();
	IT end = input.end();

	op* result = program_parse(begin, end);

	std::cout << "Source string:" << std::endl;
	std::cout << source << std::endl << std::endl;

	std::cout << "Regular Expression:" << std::endl;
	std::cout << input << std::endl << std::endl;

	std::cout << "Print parse tree:" << std::endl;
	print(result);
	std::cout << std::endl;

	/*
	std::cout << "Result of executed regex:" << std::endl;
	execute(result, source);
	std::cout << std::endl;
	*/
	
}