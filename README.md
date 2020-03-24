# Regular Expression Parser
Regular expression parser written in C++ for school project

## Grammar
```
<RE> ::= <substitute>  |  <simple-RE>
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=  concatenation> | <basic-RE> 
<concatenation> ::= <basic-RE> <simple-RE> 
<basic-RE>	::= <star> | <plus> | <counter> | <lowercase> | <capture> | <elementary-RE>
<capture> ::= <elementary-RE> "\O" <counter>
<lowercase> ::= <elementary-RE> "\I"
<star>	::=	<elementary-RE> "*"
<counter> ::= <elementary-Re>  "{" <digit> "}"
<elementary-RE>	::=	 <char> | <group> | <any> 
<group>	::=	"(" <RE> ")"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<charachter>	::= <char> // char* to be exact
 ```
