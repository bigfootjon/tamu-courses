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
std::map<std::string, std::string> definemap;

%}

%option yylineno

SINGLE_COMMENT		\/\/
MULTI_COMMENT_BEGIN	\/\*
MULTI_COMMENT_END	\*\/
OCTOTHORP		#
CHARS			[a-zA-Z0-9]*
%%

{SINGLE_COMMENT}[^\n]* {}

\r {}

\n {
	printf("%s", yytext);
}

{MULTI_COMMENT_BEGIN} {
	multicomment = true;
}

{MULTI_COMMENT_END} {
	if (multicomment == false) {
		printf("%s", yytext);
	} else {
		multicomment = false;
	}
}

{OCTOTHORP}define.*$ {
	char* define_keyword = strtok(yytext, " ");
	char* name = strtok(NULL, " ");
	char* replacement = strtok(NULL, "\0");

	bool error = false;
	for (int i = 0; i < strlen(name); ++i) {
		if (!isalpha(name[i]) || islower(name[i])) {
			ReportError::InvalidDirective(yylineno);
			error = true;
			break;
		}
	}

	if (!error) {
		definemap.insert(std::make_pair(std::string(name), std::string(replacement)));
	}
}

{OCTOTHORP}{CHARS} {
	char* name = yytext + 1;
	try {
		std::string out = definemap.at(std::string(name));
		printf("%s", out.c_str());
	} catch (...) {
		ReportError::InvalidDirective(yylineno);
	}
}

. {
	if (!multicomment) {
		printf("%s", yytext);
	}
}
