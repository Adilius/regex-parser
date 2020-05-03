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
## Output
![output1](https://user-images.githubusercontent.com/43440295/80920120-064f4a00-8d6e-11ea-8e64-ca49e4631904.PNG)
![output2](https://user-images.githubusercontent.com/43440295/80920171-5a5a2e80-8d6e-11ea-8738-aee6b5827a95.PNG)
