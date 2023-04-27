//여기에서 symboltable 처리하는 함수 이용해서 token 매치되었을 때 처리해줘야함
%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
%}
//errortypes는 tn.h에 정의함
letter [A-Za-z_]
digit [0-9]
%%
//주석은 여러 줄 주석(/* */)과 한 줄(//)로 나누어 처리

"{"				return(TBEGIN);
"}"				return(TEND);
"("				return(TSMALLBL);
")"				return(TSMALLBR);
"["				return(TBIGBL);
"]"				return(TBIGBR);

":="			return(TASSIGN);
"+"				return(TPLUS);
"-"				return(TMINUS);
"/"				return(TSLASH);
"*"				return(TSTAR);
"%"				return(TMOD);
"="             return(TASSIGN);

{digit}+		return(TNUM);
\.				return(TDOT);
"const" 		return(TCONST);
"else" 			return(TELSE);
"if" 			return(TIF);
"int" 			return(TINT);
"return" 		return(TRETURN);
"void" 			return(TVOID);
"while" 		return(TWHILE);

"==" 			return(TEQUAL);
"!="			return(TNOTEQU);
"<"				return(TLESS);
">"				return(TGREAT);
"<=" 			return(TLESSE);
">=" 			return(TGREATE);

"!"				return(TNOT);
"&&" 			return(TAND);
"||" 			return(TOR);
"++"			return(TINC);
"--"			return(TDEC);

"\""			return(TBQUOTE);
"\'"			return(TSQUOTE);

"+="			return(TADDASSIGN);
"-="			return(TSUBASSIGN);
"*=" 			return(TMULASSIGN);
"/=" 			return(TDIVASSIGN);
"%=" 			return(TMODASSIGN);

","				return(TCOMMA);
";"				return(TSEMI);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?	return(TNUMBER);
{letter}({letter}|{digit})*					return(TIDENTIFIER);
"//".* 										return(TCOMMENT);
"/*"([^*]|"*"+[^*/])*"*"+"/"				return(TCOMMENTS);
[\s|\t|\n]									return(TSEPARATOR);
.											return(TERROR);
%%
int yywrap()
{
	printf("End\n");
	return 1;
}
