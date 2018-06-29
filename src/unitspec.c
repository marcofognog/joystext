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
    printf("Fail, the int should be %i, but is %i\n", expected, value);
  }
}

Keymap create_keymap(int is_func,
                     int mode,
                     int onpress,
                     int keycode1,int keycode2, int keycode3,
                     int b0,int b1,int b2,int b3,int b4,
                     int b5,int b6,int b7,int b8,int b9,
                     int b10, int b11, int b12, int b13, int b14, int b15){
  int buttons[16] = { b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15 };
  Keymap obj;

  memcpy(&obj.binary_buttons, &buttons, sizeof(buttons));
  obj.is_func = is_func;
  obj.mode = mode;
  obj.onpress = onpress;
  obj.keycode1 = keycode1;
  obj.keycode2 = keycode2;
  obj.keycode3 = keycode3;

  return obj;
}

void assert_keymap_equal(Keymap value, Keymap expected){
  assert_int_equal(value.keycode1, expected.keycode1);
  assert_int_equal(value.keycode2, expected.keycode2);
  assert_int_equal(value.keycode3, expected.keycode3);
  assert_int_equal(value.onpress, expected.onpress);
  assert_int_equal(value.mode, expected.mode);
  assert_int_equal(value.is_func, expected.is_func);

  if(memcmp(value.binary_buttons, expected.binary_buttons, sizeof(expected.binary_buttons)) == 0){
    printf("Equal buttons\n");
  } else{
    printf("-> buttons comparison failed. expected: ");
    print_binary(expected.binary_buttons);
    printf(" received: ");
    print_binary(value.binary_buttons);
    printf("\n");
  }
}

void test_parse_line_one_line(){
  char line[255] = "F1:a,00\n";
  parse_line(line, &keytable1);

  Keymap expected = create_keymap(0,0,0,97,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  int expected_size = 1;

  assert_keymap_equal(keytable1.repository[0], expected);
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
