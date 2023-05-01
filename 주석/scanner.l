%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
%}
letter	[a-zA-Z_]
digit	[0-9]
%%
"const"					return(TCONST);
"else"					return(TELSE);
"if"					return(TIF);
"int"					return(TINT);
"return"				return(TRETURN);
"void"					return(TVOID);
"while"					return(TWHILE);

"+"						return(TPLUS);
"-"						return(TMINUS);
"*"						return(TSTAR);
"/"						return(TSLASH);
"%"						return(TMOD);

"="						return(TASSIGN);
"+="					return(TADDASSIGN);
"-="					return(TSUBASSIGN);
"*="					return(TMULASSIGN);
"/="					return(TDIVASSIGN);
"%="					return(TMODASSIGN);

"!"						return(TNOT);
"&&"					return(TAND);
"||"					return(TOR);

"=="					return(TEQUAL);
"!="					return(TNOTEQU);
"<"						return(TLESS);
">"						return(TGREAT);
"<="					return(TLESSE);
">="					return(TGREATE);

"++"					return(TINC);
"--"					return(TDEC);


"("						return(TSMALLBL);
")"						return(TSMALLBR);
","						return(TCOMMA);
"{"						return(TBEGIN);
"}"						return(TEND);
"["						return(TBIGBL);
"]"						return(TBIGBR);
";"						return(TSEMI);

[ \t]					;
\n						numLine++;

[1-9][0-9]*|0			return(TDNUMBER);
0[0-7]+					return(TONUMBER);
0(x|X)[0-9A-Fa-f]*		return(THNUMBER);

{letter}({letter}|{digit})*		{
								if(yyleng > 12) 
									return(TLONGIDENTERR);
							
								else {
									int f = SymbolTable();
									if(!f)
										return(TIDENT);
									else
										return(TEXIST);
									}
								}
{digit}({letter}|{digit})*		return(TILLIDENTERR);

"/*"([^*]|\*+[^*/])*\**"*/"		return(TCOMMENTS);
"//".*							return(TCOMMENT);
.								return(TILLCHARERR);
%%

int yywrap()
{
	return 1;
}