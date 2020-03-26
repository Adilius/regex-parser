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

int main()
{
    std::string source ="Waterloo I was defeated, you won the war"
						"Waterloo promise to love you for ever more"
						"Waterloo couldn't escape if I wanted to"
						"Waterloo knowing my fate is to be with you"
						"Waterloo finally facing my Waterloo";
    std::string input = "o+o";

	//Get iterators to begin and end
	IT begin = input.begin();
	IT end = input.end();

    std::cout << "Hello World!\n";
}