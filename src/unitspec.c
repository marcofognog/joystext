#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
# include "joystext.h"
#include "../parser.tab.c"
#include "../lex.yy.c"
#include "parse_config.c"

void print_result(struct keymap keymaps[], int lines){
  for(int l=0; l<lines; l++){
    print_binary(keymaps[l].binary_buttons);
    printf(",%i,%i,%i, mode:%i\n", keymaps[l].keycode1, keymaps[l].keycode2,keymaps[l].keycode3, keymaps[l].mode);
    if((*keymaps[l].t_modified).repository !=0 ){
      for(int y=0; y<(*keymaps[l].t_modified).size; y++){
        printf(" - ");
        print_binary((*keymaps[l].t_modified).repository[y].binary_buttons);
        printf(",%i,%i,%i, mode:%i, pointer: %p\n",
            (*keymaps[l].t_modified).repository[y].keycode1,
            (*keymaps[l].t_modified).repository[y].keycode2,
            (*keymaps[l].t_modified).repository[y].keycode3,
            (*keymaps[l].t_modified).repository[y].mode,
            (*keymaps[l].t_modified).repository
            );
      }
    }
  }
}

TArray keytable1;
TArray keytable2;
TArray keytable3;

void assert_int_equal(int value, int expected){
  if(value == expected){
    printf("Nice\n");
  } else {
    printf("Fail, size should be %i, but is %i\n", expected, value);
  }
}

void test_parse_line_one_line(){
  char line[255] = "F1:a,00\n";
  parse_line(line, &keytable1);

  int expected = 1;
  assert_int_equal(keytable1.size, expected);
  print_result(keytable1.repository, keytable1.size);
}

void test_parse_line_two_lines(){
  char line_one[255] = "F1:a,00\n";
  char line_two[255] = "F2:b,00\n";

  parse_line(line_one, &keytable2);
  parse_line(line_two, &keytable2);

  int expected = 2;
  assert_int_equal(keytable2.size, expected);
  print_result(keytable2.repository, keytable2.size);
}

void test_parse_line_remap_lines(){
  char line[255] = "F1:a,00\n";
  parse_line(line, &keytable3);

  char line1[255] = "S4:=,00\n";
  parse_line(line1, &keytable3);

  char line2[255] = "S4:super+k,00\n";
  parse_line(line2, &keytable3);

  int expected = 3;
  assert_int_equal(keytable3.size, expected);
  print_result(keytable3.repository, keytable3.size);
}

int main(int argc, char *argv[]){
  test_parse_line_one_line();
  test_parse_line_two_lines();
  test_parse_line_remap_lines();
}
