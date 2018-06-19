/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb1-5.y,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */

%{
# include <stdio.h>
# include "src/codegen.c"
%}

%union {
  char c;
  char *s;
}

%token <c> COLON CBRACKT OBRACKT
%token <c> TYPEOP PLUS

%token <s> REMAP_TOKEN MODE_TOKEN
%token <s> START SELECT BUTTON NAME COMMAND

%token EOL

%type <s> cmd
%type <s> combination

%define parse.error verbose

%%
jsl:
 | jsl definition EOL
 | jsl EOL
 ;

definition:
 | MODE_TOKEN NAME { gen_mode($2); };
 | TYPEOP BUTTON  COLON cmd { action_definition($1, $2, $4);  }
 | TYPEOP START   COLON cmd { action_definition($1, $2, $4);  }
 | TYPEOP SELECT  COLON cmd { action_definition($1, $2, $4);  }
 | BUTTON         COLON cmd { action_definition('0', $1, $3);  }
 | SELECT         COLON cmd { action_definition('0', $1, $3);  }
 | START          COLON cmd { action_definition('0', $1, $3);  }
 | combination    COLON cmd { action_definition('0', $1, $3);  }
 | open_remap jsl CBRACKT { close_remap();}
 ;

combination:
 | BUTTON PLUS combination { $$ = concat($1, $3);  }
 | SELECT PLUS combination { $$ = concat($1, $3); }
 | START PLUS combination  { $$ = concat($1, $3); }
 | BUTTON
 | SELECT
 | START
;

open_remap:
 | REMAP_TOKEN BUTTON OBRACKT { open_remap($2); }
 ;

cmd: COMMAND           { $$ = $1; };
| COMMAND NAME         { $$ = build_named_command($1, $2); };
| COMMAND PLUS cmd { $$ = build_combo_command($1, $3); };
%%

yyerror(char *s)
{
  fprintf(stderr, "Character not recognized: \"%s\"\n", s);
}
