#pragma once

enum tnumber { 
	TEOF,

	//Comment
	TCOMMENT, TCOMMENTS,

	//Identifier & Constant
	TIDENT, TDNUMBER, TONUMBER, THNUMBER,

	//Keyword - const, else, if, int, return, void, while
	TCONST, TELSE, TIF, TINT, TRETURN, TVOID, TWHILE,

	//Operator 1 - Arithmetic operator - +, -, *, /, %
	TPLUS, TMINUS, TSTAR, TSLASH, TMOD,

	//Operator 2 - Assign operator - =, +=, -=, *=, /=, %=
	TASSIGN, TADDASSIGN, TSUBASSIGN, TMULASSIGN, TDIVASSIGN, TMODASSIGN,

	//Operator 3 - Logic operator - !, &&, ||
	TAND, TOR, TNOT,

	//Operator 4 - Relation operator - ==, !=, <, >, <=, >=
	TEQUAL, TNOTEQU, TLESS, TGREAT, TLESSE, TGREATE, 

	//Operator 5 - Increase & Decrease operator - ++, --
	TINC, TDEC, 

	//Special Symbols 1 - (, ), {, }, [, ]
	TSMALLBL, TSMALLBR, TBEGIN, TEND, TBIGBL, TBIGBR,

	//Special Symbols 2 - ,, ;
	TCOMMA, TSEMI,

	//Errors
	TLONGIDENTERR, TILLIDENTERR, TILLCHARERR,
};
