/*
 * file:  dpp.l
 * ------------
 * Lex inupt file to generate the scanner for the preprocessor.
 * If you decide to use lex for the preprocesor, put your rules
 * here, otherwise the file can remain empty.
 */
%{

#include <map>
#include "errors.h"

bool multicomment = false;
char* preout = 0;
std::map<std::string, std::string> definemap;

typedef enum {
	P_Done, P_Output, P_None
} PreTypes;

%}

%option yylineno

SINGLE_COMMENT		\/\/
MULTI_COMMENT_BEGIN	\/\*
MULTI_COMMENT_END	\*\/
OCTOTHORP		#
CHARS			[a-zA-Z0-9]*
%%

{SINGLE_COMMENT}[^\n]* {
	return P_None;
}

\r {}

\n {
	preout = yytext;
	return P_Output;
}

{MULTI_COMMENT_BEGIN} {
	multicomment = true;
	return P_None;
}

{MULTI_COMMENT_END} {
	if (multicomment == false) {
		preout = yytext;
		return P_Output;
	}
	multicomment = false;
	return P_None;
}

{OCTOTHORP}define[^\r]* {
	char* define_keyword = strtok(yytext, " ");
	char* name = strtok(NULL, " ");
	for (int i = 0; i < strlen(name); ++i) {
		if (!isalpha(name[i]) || islower(name[i])) {
			ReportError::InvalidDirective(yylineno);
			return P_None;
		}
	}
	char* replacement = strtok(NULL, "\0");
	definemap.insert(std::make_pair(std::string(name), std::string(replacement)));
}

{OCTOTHORP}{CHARS} {
	char* name = yytext + 1;
	try {
		std::string out = definemap.at(std::string(name));
		preout = (char*)out.c_str();
		return P_Output;
	} catch (...) {
		ReportError::InvalidDirective(yylineno);
		return P_None;
	}
}

. {
	if (multicomment) {
		return P_None;
	} else {
		preout = yytext;
		return P_Output;
	}
}
