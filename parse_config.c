#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

struct keymap {
  int binary_buttons[16];
  int keycode1;
  int keycode2;
  int keycode3;
};

struct keymap keymaps[200]; //make this dinamic.

int pressed_key(int *binary_buttons){
  int print_flag = 0;
  for (int i=0; i < 16; i++) {
    int b = binary_buttons[i] -0;
    if(b){
      print_flag = 1;
    }
  }
  return print_flag;
}

void print_binary(int *binary_buttons){
  for (int i=0; i < 16; i++) {
    printf("%i", binary_buttons[i]);
  }
}

int parse_config(int argc, char *argv[]){
  struct key {
    char name[32];
    int keycode[3];
  };

  struct key keys[120] = {
    {"a",{XK_a}},
    {"b",{XK_b}},
    {"c",{XK_c}},
    {"d",{XK_d}},
    {"e",{XK_e}},
    {"f",{XK_f}},
    {"g",{XK_g}},
    {"h",{XK_h}},
    {"i",{XK_i}},
    {"j",{XK_j}},
    {"k",{XK_k}},
    {"l",{XK_l}},
    {"m",{XK_m}},
    {"n",{XK_n}},
    {"o",{XK_o}},
    {"p",{XK_p}},
    {"q",{XK_q}},
    {"r",{XK_r}},
    {"s",{XK_s}},
    {"t",{XK_t}},
    {"u",{XK_u}},
    {"v",{XK_v}},
    {"w",{XK_w}},
    {"x",{XK_x}},
    {"y",{XK_y}},
    {"z",{XK_z}},
    {"shift",{XK_Shift_L}},
    {"semi_colon",{XK_semicolon}},
    {"colon",{XK_Shift_L,XK_colon}},
    {"slash",{XK_slash}},
    {"escape",{XK_Escape}},
    {"comma",{XK_comma}},
    {"dot",{XK_period}},
    {"minus",{XK_minus}},
    {"plus",{XK_Shift_L,XK_plus}},
    {"left_parenthesis",{XK_parenleft}},
    {"right_parenthesis",{XK_parenright}},
    {"right_square_bracket",{XK_bracketleft}},
    {"left_square_bracket",{XK_bracketright}},
    {"left_curly_bracket",{XK_Shift_L,XK_braceleft}},
    {"right_curly_bracket",{XK_Shift_L,XK_braceright}},
    {"exclamation",{XK_Shift_L,XK_exclam}},
    {"at",{XK_Shift_L,XK_at}},
    {"sharp",{XK_Shift_L,XK_numbersign}},
    {"dollar",{XK_Shift_L,XK_dollar}},
    {"percent",{XK_Shift_L,XK_percent}},
    {"question_mark",{XK_Shift_L,XK_question}},
    {"pipe",{XK_Shift_L,XK_bar}},
    {"asterisk",{XK_Shift_L,XK_asterisk}},
    {"underscore",{XK_Shift_L,XK_underscore}},
    {"double_quote",{XK_Shift_L,XK_quotedbl}},
    {"single_quote",{XK_quotedbl}},
    {"ampersand",{XK_Shift_L,XK_ampersand}},
    {"equal",{XK_equal}},
    {"less",{XK_Shift_L,XK_less}},
    {"greater",{XK_Shift_L,XK_greater}},
    {"space",{XK_space}},
    {"enter",{XK_Return}},
    {"backspace",{XK_BackSpace}},
    {"page_up",{XK_Page_Up}},
    {"end",{XK_End}},
    {"page_down",{XK_Page_Down}},
    {"home",{XK_Home}},
    {"arrow_up",{XK_Up}},
    {"arrow_right",{XK_Right}},
    {"arrow_down",{XK_Down}},
    {"arrow_left",{XK_Left}},
    {"one",{XK_1}},
    {"two",{XK_2}},
    {"three",{XK_3}},
    {"four",{XK_4}},
    {"five",{XK_5}},
    {"six",{XK_6}},
    {"seven",{XK_7}},
    {"eight",{XK_8}},
    {"nine",{XK_9}},
    {"zero",{XK_0}},
    {"tab",{XK_Tab}},
    {"ctrl",{XK_Control_L}},
    {"super",{XK_Super_L}}

  };

  struct button{
    char name[16];
    int binary[16];
  };

  struct button buttons[16] = {
    {"F1",     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F2",     {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F3",     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F4",     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"A1",     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
    {"A2",     {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}},
    {"A3",     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}},
    {"A4",     {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}},
    {"S1",     {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}},
    {"S2",     {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}},
    {"S3",     {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}},
    {"S4",     {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}},
    {"select", {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
    {"start",  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}},
    {"C1",     {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}},
    {"C2",     {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}}
  };

  FILE *fp = fopen(argv[1], "r");
  char line[255];
  if (fp == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[1]);
    exit(1);
  }

  int l;
  for (int i=0; i<200; i++){
    l = fgets(line, 255, (FILE*)fp);
    if(l != NULL){
      if(strcmp(line, "\n") != 0){
        char delimiter[2] = ":";
        char *signifier = strtok(line, delimiter);
        char *signified = strtok(NULL, delimiter); // This feels wierd

        //remove \n
        char *sanitized = strtok(signified, "\n");

        char *key1 = strtok(signifier, "+");
        char *key2 = strtok(NULL, "+");
        char *key3 = strtok(NULL, "+");
        char *key4 = strtok(NULL, "+");

        int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int k=0; k<16; k++){
          if(strcmp(key1, buttons[k].name) == 0){
            for(int j=0; j<16;j++){
              merged[j] = (merged[j] || buttons[k].binary[j]);
            }
          }
          if(key2 != NULL){
            if(strcmp(key2, buttons[k].name) == 0){
              for(int j=0; j<16;j++){
                merged[j] = (merged[j] || buttons[k].binary[j]);
              }
            }
          }
          if(key3 != NULL){
            if(strcmp(key3, buttons[k].name) == 0){
              for(int j=0; j<16;j++){
                merged[j] = (merged[j] || buttons[k].binary[j]);
              }
            }
          }
          if(key4 != NULL){
            if(strcmp(key4, buttons[k].name) == 0){
              for(int j=0; j<16;j++){
                merged[j] = (merged[j] || buttons[k].binary[j]);
              }
            }
          }
          for(int j=0;j<16;j++){
            keymaps[i].binary_buttons[j] = merged[j];
          }
        }

        char *keycode_name1;
        keycode_name1 = strtok(sanitized, "+");
        char *keycode_name2;
        keycode_name2 = strtok(NULL, "+");
        char *keycode_name3;
        keycode_name3 = strtok(NULL, "+");

        for(int k=0; k<120; k++){
          if(keycode_name1 != NULL){
            if(strcmp(keycode_name1, keys[k].name) == 0){
              keymaps[i].keycode1 = keys[k].keycode[0];
              if(keys[k].keycode[1] != 0)
                keymaps[i].keycode2 = keys[k].keycode[1];
            }
          }
          if(keycode_name2 != NULL){
            if(strcmp(keycode_name2, keys[k].name) == 0){
              if(keymaps[i].keycode2 == 0){
                keymaps[i].keycode2 = keys[k].keycode[0];
                if(keys[k].keycode[1] != 0)
                  keymaps[i].keycode3 = keys[k].keycode[1];
              }else{
                keymaps[i].keycode3 = keys[k].keycode[0];
              }
            }
          }
          if(keycode_name3 != NULL){
            if(strcmp(keycode_name3, keys[k].name) == 0){
              if(keymaps[i].keycode2 == 0)
                keymaps[i].keycode3 = keys[k].keycode[0];
            }
          }
        }

      }
    }
  }

  return 0;
}
