%{
#include <stdio.h>
#include <stdlib.h>
enum tokentypes {TEOF, TCONST, TELSE, TIF, TINT, TRETURN,
				TVOID, TWHILE, TEQUAL, TNOTEQU, TLESSE,
				TGREATE, TAND, TOR, TINC, TDEC, 
				TADDASSIGN, TSUBASSIGN, TMULASSIGN,
				TDIVASSIGN, TMODASSIGN, TIDENT, TNUMBER,
				TERROR
};
%}
%%
"const" 		return(TCONST);
"else"			return(TELSE);
"if"			return(TIF);
"int"			return(TINT);
"return"		return(TRETURN);
"void"			return(TVOID);
"while"			return(TWHILE);
"=="		 	return(TEQUAL);
"!="			return(TNOTEQU);
"<="			return(TLESSE);
">="		 	return(TGREATE);
"&&"			return(TAND);
"||"		 	return(TOR);
"++"			return(TINC);
"--"			return(TDEC);
"+="			return(TADDASSIGN);
"-="			return(TSUBASSIGN);
"*=" 			return(TMULASSIGN);
"/="			return(TDIVASSIGN);
"%=" 			return(TMODASSIGN);
[A-Za-z_][A-Za-z0-9_]* 							return(TIDENT);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?		return(TNUMBER);
"/*"([^*]|\*+[^*/])*\**"*/" 					;
"//".*											;
[ \t\n] 										;

. 	return(TERROR);

%%
int yywrap(){
		return 1;
}
void main()
{
	enum tnumber tn;  // token number

	while  ((tn = yylex()) != TEOF) {
		switch (tn) {
			case TCONST : printf("TCONST   %22s\n",yytext);  break;
			case TELSE : printf("TELSE   %22s\n",yytext);  break;
			case TIF : printf("TIF   %22s\n",yytext);  break;
			case TINT : printf("TINT   %22s\n",yytext);  break;
			case TRETURN : printf("TRETURN   %22s\n",yytext);  break;
			case TVOID : printf("TVOID   %22s\n",yytext);  break;
			case TWHILE : printf("TWHILE   %22s\n",yytext);  break;
			case TEQUAL : printf("TEQUAL   %22s\n",yytext);  break;
			case TNOTEQU : printf("TNOTEQU   %22s\n",yytext);  break;
			case TLESSE : printf("TLESSE   %22s\n",yytext);  break;
			case TGREATE : printf("TGREATE  %22s\n",yytext);  break;
			case TAND : printf("TAND   %22s\n",yytext);  break;
			case TOR : printf("TOR   %22s\n",yytext);  break;
			case TINC : printf("TINC   %22s\n",yytext);  break;
			case TDEC : printf("TDEC   %22s\n",yytext);  break;
			case TADDASSIGN : printf("TADDASSIGN   %22s\n",yytext);  break;
			case TSUBASSIGN : printf("TSUBASSIGN   %22s\n",yytext);  break;
			case TMULASSIGN : printf("TMULASSIGN   %22s\n",yytext);  break;
			case TDIVASSIGN : printf("TDIVASSIGN   %22s\n",yytext);  break;
			case TMODASSIGN : printf("TMODASSIGN   %22s\n",yytext);  break;

			case TIDENT : printf("TIDENT   %22s\n",yytext);  break;
			case TNUMBER : printf("TNUMBER   %22s\n",yytext);  break;

			case TERROR: printf("Error : %c\n", yytext[0]); break;
		}
	}
}
