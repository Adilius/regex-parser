# Regular Expression Parser
Regular expression parser written in C++ for school project

## Grammar
```
<RE> ::= <simple-RE>
<simple-RE>	::=  concatenation> | <basic-RE> 
<concatenation> ::= <basic-RE> <simple-RE> 
<basic-RE>	::= <star> | <plus> | <count> | <elementary-RE>
<star>	::=	<elementary-RE> "*"
<count> ::= <elementary-Re>  "{" any number "}"
<elementary-RE>	::=	 <character> | <group> | <any> 
<group>	::=	"(" <RE> ")"
<any>	::=	"."
<character>	::= any non metacharacter
 ```
