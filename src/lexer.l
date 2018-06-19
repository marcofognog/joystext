/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb1-5.l,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */

/* recognize tokens for the calculator and print them out */

%{
# include "parser.tab.h"
%}

%%
":"     { return COLON; }

([A|F|S1-4]{2})      {
  yylval.s = strdup(yytext);
  return BUTTON;
}

(\.|<|>|\*)          {
  yylval.c = yytext[0];
  return TYPEOP;
}

(\'[A-Z a-z 0-9]+\')$   {
  yylval.s = strdup(yytext);
  return NAME;
}

"\+"          {
  yylval.c = yytext[0];
  return PLUS;
}

^"mode"  {
  yylval.s = strdup(yytext);
  return MODE_TOKEN;
}

^"start"  {
  yylval.s = strdup(yytext);
  return START;
}

^"select"  {
  yylval.s = strdup(yytext);
  return SELECT;
}

"remap"  {
  yylval.s = strdup(yytext);
  return REMAP_TOKEN;
}

"{"  {
  yylval.c = yytext[0];
  return OBRACKT;
}

"}"  {
  yylval.c = yytext[0];
  return CBRACKT;
}

[a-zA-Z0-9_][a-zA-Z0-9_]* {
  yylval.s = strdup(yytext);
  return COMMAND;
}


\n      { return EOL; }
"#".*
[ \t]   { /* ignore white space */ }
.       { yyerror(yytext); }
%%
