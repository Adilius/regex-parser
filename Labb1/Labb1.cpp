#include "op.h"
#include "token.h"
#include "object.h"
#include "plus.h"
#include "re.h"
#include "substitute.h"
#include "concatenation.h"
#include "simple_re.h"
#include "basic_re.h"
#include "elementary_re.h"
#include "character.h"
#include "program.h"

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
op* character_expr(IT& first, IT& last);	//TODO
op* group_expr(IT& first, IT& last);	//TODO
op* any_expr(IT& first, IT& last);	//TODO

op* digit_expr(IT& first, IT& last);	//TODO

//Prints parse tree
void print(op* op, size_t i = 0);

//Runs parse tree
void execute(op* parse_tree, std::string source);

//TODO
op* program_parse(IT& first, IT& last) {
	//If the string is empty
	if (first == last) {
		return nullptr;
	}
	op* re = regExp(first, last);
	program* expr = new program;
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

	//TODO
	//op* concatenation_or_basic = concatenation_expr(first, last);
	op* concatenation_or_basic = nullptr;

	//Check if basic_re
	if (!concatenation_or_basic) {
		concatenation_or_basic = basic_re_expr(first, last);

		//Check if neither
		if (!concatenation_or_basic) {
			//Assign first to old value again
			first = start;
			return nullptr;
		}
	}

	simple_re* expr = new simple_re;
	expr->operands.push_back(concatenation_or_basic);
	return expr;
}

//TODO
op* concatenation_expr(IT& first, IT& last) {
	return nullptr;
}

op* basic_re_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	op* basic = nullptr;	//basic = star | count | lowercase | capturegroup | elementary_re
	//if (!basic) { basic = star_expr(first, last); }			//TODO
	//if (!basic) { basic = counter_expr(first, last); }		//TODO
	//if (!basic) { basic = lowercase_expr(first, last); }		//TODO
	//if (!basic) { basic = capturegroup_expr(first, last); }	//TODO

	//If basic-RE is an elementary-RE
	if (!basic){
		basic = elementary_re_expr(first, last);
	}

	//If failed to find basic-RE
	if (!basic) {
		first = start; return nullptr;
	}

	basic_re* expr = new basic_re;
	expr->operands.push_back(basic);
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

	op* elementary = nullptr;

	//Check if elementary-RE is character
	if (!elementary){
		elementary = character_expr(first, last);
	}
	//if (!elementary) { elementary = group_expr(first, last); }	//TODO
	//if (!elementary) { elementary = any_expr(first, last); }		//TODO

	//If failed to find elementary_re
	if (!elementary) {
		first = start; 
		return nullptr;
	}

	elementary_re* expr = new elementary_re;
	expr->operands.push_back(elementary);
	return expr;
};

op* character_expr(IT& first, IT& last) {
	//Save iterator pointing at first
	IT start = first;

	//Get token
	token token = next_token(first, last);
	character* expr = new character;

	while (token.id == token.ID) {
		expr->_id += token.text;
		first++;
		token = next_token(first, last);
	}
	//If we didn't find any characters
	if (start == first) {
		return nullptr;
	}

	return expr;
};

//TODO
op* group_expr(IT& first, IT& last) {
	return nullptr;
};

//TODO
op* any_expr(IT& first, IT& last) {
	return nullptr;
};

//TODO
op* digit_expr(IT& first, IT& last) {
	return nullptr;
}

//Print parse tree
void print(op* op, size_t i) {
	i++;
	for (size_t j = 0; j < i; j++) {
		std::cout << " |";
	}

	//Print class name
	std::cout << op->id() << std::endl;

	//Iterate into class operands
	for (auto e : op->operands) {
		print(e, i);
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

	//std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
	std::string source = "Waterloo";
	std::string input = "loo";

	//Get iterators to begin and end
	IT begin = input.begin();
	IT end = input.end();

	op* result = program_parse(begin, end);

	std::cout << "Print parse tree:" << std::endl;
	print(result);

	std::cout << "Execute parse tree:" << std::endl;
	execute(result, source);

}