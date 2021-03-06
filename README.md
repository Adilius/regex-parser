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
 
## Build

Either build by running the regex-parser.sln file containing the Visual Studio 2019 project file.
Or build it with a C++ compiler and including all the headers and main.cpp file.

## Run

Run regex-parser from terminal. 
`.\regex-parser.exe "Waterloo" input.txt`
First argument is the regex.
Second argument is the file containing the text



## Output
![output1](https://user-images.githubusercontent.com/43440295/80920120-064f4a00-8d6e-11ea-8e64-ca49e4631904.PNG)
![output2](https://user-images.githubusercontent.com/43440295/80920171-5a5a2e80-8d6e-11ea-8738-aee6b5827a95.PNG)
![output3](https://user-images.githubusercontent.com/43440295/80920296-20d5f300-8d6f-11ea-8068-083c6bf3264d.PNG)
