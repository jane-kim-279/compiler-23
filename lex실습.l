%{
#include <stdio.h>
#include <stdlib.h>
enum tnumber { TEOF, TBEGIN, TEND, TIDEN, TASSIGN, TADD, TNUM, TSEMI, TDOT, TCONST, TELSE, TIF,
						TINT, TRETURN, TVOID, TWHILE, TEQUAL, TNOTEQU, TLESSE, TAND, TOR, TINC, TDEC,
						TADDASSIGN, TSUBASSIGN, TMULASSIGN, TDIVASSIGN, TMODASSIGN, TIDENT, TNUMBER}
%}
%%
"{"				return(TBEGIN);
"}"				return(TEND);
{letter}({letter}|{digit})*				return(TIDEN);
":="				return(TASSIGN);
"+"				return(TADD);
{digit}+			return(TNUM);
";"				return(TSEMI);
\.				return(TDOT);
"const" 	return(TCONST);
"else" 	return(TELSE);
"if" 	return(TIF);
"int" 	return(TINT);
"return" 	return(TRETURN);
"void" 	return(TVOID);
"while" 	return(TWHILE);
"==" 	return(TEQUAL);
"!="	return(TNOTEQU);
"<=" 	return(TLESSE);
">=" 	return(TGREATE);
"&&" 	return(TAND);
"||" 	return(TOR);
"++"	return(TINC);
"--"	return(TDEC);
"+="	return(TADDASSIGN);
"-="	return(TSUBASSIGN);
"*=" 	return(TMULASSIGN);
"/=" 	return(TDIVASSIGN);
"%=" 	return(TMODASSIGN);
[A-Za-z_][A-Za-z0-9_]* 							return(TIDENT);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?		return(TNUMBER);
"/*?([^*]|\*+[^*/])*\**"*/" 	;
"//".*								;
[ \t\n] 							;
. 									return(yytext[0]);

%%
void main()
{ enum tnumber tn;		//token number 
  printf("Start of Lex\n");
  while ( (tn=yylex()) != TEOF) {
	switch (tn) {
		case TBEGIN : printf("Begin\n"); break;
		case TEND: printf("\n"); break;
		case TIDEN	: printf("Identifier: %s\n", yytext); break;
		case TASSIGN : printf("Assignment_op\n"); break;
		case TADD : printf("Add_op\n"); break;
		case TNUM : printf("Number: %d\n", atoi(yytext)); break;
		case TSEMI : printf("Semicolon\n"); break;
		case TCONST: printf("TCONST %22s\n", yytext); break;
		case TELSE: printf("TELSE %22s\n", yytext); break;
		case TIF: printf("TIF %22s\n", yytext); break;
		case TINT: printf("TINT %22s\n", yytext); break;
		case TRETURN: printf("TRETURN %22s\n", yytext); break;
		case TVOID: printf("TVOID %22s\n", yytext); break;
		case TWHILE: printf("TWHILE %22s\n", yytext); break;
		case TEQUAL: printf("TEQUAL %19s\n", yytext); break;
		case TNOTEQU: printf("TNOTEQU %19s\n", yytext); break;
		case TLESSE: printf("TLESSE %19s\n", yytext); break;
		case TGREATE: printf("TGREATE %19s\n", yytext); break;
		case TAND: printf("TAND %21s\n", yytext); break;
		case TOR: printf("TOR %21s\n", yytext); break;
		case TINC: printf("TINC %21s\n", yytext); break;
		case TDEC: printf("TDEC %21s\n", yytext); break;
		case TADDASSIGN: printf("TADDASSIGN %16s\n", yytext); break;
		case TSUBASSIGN: printf("TSUBASSIGN %16s\n", yytext); break;
		case TMULASSIGN: printf("TMULASSIGN %16s\n", yytext); break;
		case TDIVASSIGN: printf("TDIVASSIGN %16s\n", yytext); break;
		case TMODASSIGN: printf("TMODASSIGN %16s\n", yytext); break;
		case TIDENT: printf("TIDENT %16s\n", yytext); break;
		case TNUMBER: printf("TNUMBER %18s\n", yytext); break;
		case TERROR: break;
	}
  }
}
int yywrap()
{
	return 1;
}
