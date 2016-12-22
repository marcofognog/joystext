#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

struct t_array;

typedef struct keymap {
  int binary_buttons[16];
  int is_func;
  int mode;
  int onpress;
  int keycode1;
  int keycode2;
  int keycode3;
  struct t_array * t_modified;
} Keymap;

typedef struct t_array{
  Keymap * repository;
  int size;
} TArray;

Keymap *keymaps;

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

int count_lines(FILE *fp){
  fseek(fp, 0, SEEK_SET);
  int counter = 0;
  char line[255];

  while(1){
    fgets(line, 255, (FILE*)fp);
    counter++;
    if(feof(fp))
      break;
  }
  fseek(fp, 0, SEEK_SET);
  //Why is counter off by one? Lets fix it anyway.
  counter--;
  return counter;
}

typedef struct command {
  int is_func;
  char name[32];
  int keycode[3];
} Command;

Command commands[150] = {
  {0,"a",{XK_a}},
  {0,"b",{XK_b}},
  {0,"c",{XK_c}},
  {0,"d",{XK_d}},
  {0,"e",{XK_e}},
  {0,"f",{XK_f}},
  {0,"g",{XK_g}},
  {0,"h",{XK_h}},
  {0,"i",{XK_i}},
  {0,"j",{XK_j}},
  {0,"k",{XK_k}},
  {0,"l",{XK_l}},
  {0,"m",{XK_m}},
  {0,"n",{XK_n}},
  {0,"o",{XK_o}},
  {0,"p",{XK_p}},
  {0,"q",{XK_q}},
  {0,"r",{XK_r}},
  {0,"s",{XK_s}},
  {0,"t",{XK_t}},
  {0,"u",{XK_u}},
  {0,"v",{XK_v}},
  {0,"w",{XK_w}},
  {0,"x",{XK_x}},
  {0,"y",{XK_y}},
  {0,"z",{XK_z}},
  {0,"A",{XK_Shift_L, XK_A}},
  {0,"B",{XK_Shift_L, XK_B}},
  {0,"C",{XK_Shift_L, XK_C}},
  {0,"D",{XK_Shift_L, XK_D}},
  {0,"E",{XK_Shift_L, XK_E}},
  {0,"F",{XK_Shift_L, XK_F}},
  {0,"G",{XK_Shift_L, XK_G}},
  {0,"H",{XK_Shift_L, XK_H}},
  {0,"I",{XK_Shift_L, XK_I}},
  {0,"J",{XK_Shift_L, XK_J}},
  {0,"K",{XK_Shift_L, XK_K}},
  {0,"L",{XK_Shift_L, XK_L}},
  {0,"M",{XK_Shift_L, XK_M}},
  {0,"N",{XK_Shift_L, XK_N}},
  {0,"O",{XK_Shift_L, XK_O}},
  {0,"P",{XK_Shift_L, XK_P}},
  {0,"Q",{XK_Shift_L, XK_Q}},
  {0,"R",{XK_Shift_L, XK_R}},
  {0,"S",{XK_Shift_L, XK_S}},
  {0,"T",{XK_Shift_L, XK_T}},
  {0,"U",{XK_Shift_L, XK_U}},
  {0,"V",{XK_Shift_L, XK_V}},
  {0,"W",{XK_Shift_L, XK_W}},
  {0,"X",{XK_Shift_L, XK_X}},
  {0,"Y",{XK_Shift_L, XK_Y}},
  {0,"Z",{XK_Shift_L, XK_Z}},
  {0,"shift",{XK_Shift_L}},
  {0,"semi_colon",{XK_semicolon}},
  {0,"colon",{XK_Shift_L,XK_colon}},
  {0,"slash",{XK_slash}},
  {0,"escape",{XK_Escape}},
  {0,"comma",{XK_comma}},
  {0,"dot",{XK_period}},
  {0,"minus",{XK_minus}},
  {0,"plus",{XK_Shift_L,XK_plus}},
  {0,"left_parenthesis",{XK_parenleft}},
  {0,"right_parenthesis",{XK_parenright}},
  {0,"right_square_bracket",{XK_bracketleft}},
  {0,"left_square_bracket",{XK_bracketright}},
  {0,"left_curly_bracket",{XK_Shift_L,XK_braceleft}},
  {0,"right_curly_bracket",{XK_Shift_L,XK_braceright}},
  {0,"exclamation",{XK_Shift_L,XK_exclam}},
  {0,"at",{XK_Shift_L,XK_at}},
  {0,"sharp",{XK_Shift_L,XK_numbersign}},
  {0,"dollar",{XK_Shift_L,XK_dollar}},
  {0,"percent",{XK_Shift_L,XK_percent}},
  {0,"question_mark",{XK_Shift_L,XK_question}},
  {0,"pipe",{XK_Shift_L,XK_bar}},
  {0,"asterisk",{XK_Shift_L,XK_asterisk}},
  {0,"underscore",{XK_Shift_L,XK_underscore}},
  {0,"double_quote",{XK_Shift_L,XK_quotedbl}},
  {0,"single_quote",{XK_quotedbl}},
  {0,"ampersand",{XK_Shift_L,XK_ampersand}},
  {0,"equal",{XK_equal}},
  {0,"less",{XK_Shift_L,XK_less}},
  {0,"greater",{XK_Shift_L,XK_greater}},
  {0,"space",{XK_space}},
  {0,"enter",{XK_Return}},
  {0,"backspace",{XK_BackSpace}},
  {0,"page_up",{XK_Page_Up}},
  {0,"end",{XK_End}},
  {0,"page_down",{XK_Page_Down}},
  {0,"home",{XK_Home}},
  {0,"arrow_up",{XK_Up}},
  {0,"arrow_right",{XK_Right}},
  {0,"arrow_down",{XK_Down}},
  {0,"arrow_left",{XK_Left}},
  {0,"one",{XK_1}},
  {0,"two",{XK_2}},
  {0,"three",{XK_3}},
  {0,"four",{XK_4}},
  {0,"five",{XK_5}},
  {0,"six",{XK_6}},
  {0,"seven",{XK_7}},
  {0,"eight",{XK_8}},
  {0,"nine",{XK_9}},
  {0,"zero",{XK_0}},
  {0,"tab",{XK_Tab}},
  {0,"ctrl",{XK_Control_L}},
  {0,"super",{XK_Super_L}},
  {1,"mouse_up",{0}},
  {1,"mouse_down",{1}},
  {1,"mouse_left",{2}},
  {1,"mouse_right",{3}},
  {1,"set_mouse_step_5",{4}},
  {1,"set_mouse_step_10",{5}},
  {1,"set_mouse_step_15",{6}},
  {1,"set_mouse_step_20",{7}},
  {1,"set_mouse_step_25",{8}},
  {1,"set_mouse_step_30",{9}},
  {1,"set_mouse_step_35",{10}},
  {1,"set_mouse_step_40",{11}},
  {1,"set_mouse_step_45",{12}},
  {1,"set_mouse_step_50",{13}},
  {1,"set_mouse_step_55",{14}},
  {1,"set_mouse_step_60",{15}},
  {1,"set_mouse_step_65",{16}},
  {1,"set_mouse_step_70",{17}},
  {1,"set_mouse_step_75",{18}},
};

typedef struct button{
  char name[16];
  int binary[16];
} Button;

Button buttons[16] = {
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

void populate_keycodes(Keymap * keymap, char command[], Command command_list[]){
  char *keycode_name1;
  keycode_name1 = strtok(command, "+");
  char *keycode_name2;
  keycode_name2 = strtok(NULL, "+");
  char *keycode_name3;
  keycode_name3 = strtok(NULL, "+");

  for(int k=0; k<120; k++){
    if(keycode_name1 != NULL){
      if(strcmp(keycode_name1, command_list[k].name) == 0){
        (*keymap).is_func = command_list[k].is_func;

        (*keymap).keycode1 = command_list[k].keycode[0];
        if(command_list[k].keycode[1] != 0)
          (*keymap).keycode2 = command_list[k].keycode[1];
      }
    }
    if(keycode_name2 != NULL){
      if(strcmp(keycode_name2, command_list[k].name) == 0){
        if((*keymap).keycode2 == 0){
          (*keymap).keycode2 = command_list[k].keycode[0];
          if(command_list[k].keycode[1] != 0)
            (*keymap).keycode3 = command_list[k].keycode[1];
        }else{
          (*keymap).keycode3 = command_list[k].keycode[0];
        }
      }
    }
    if(keycode_name3 != NULL){
      if(strcmp(keycode_name3, command_list[k].name) == 0)
        (*keymap).keycode3 = command_list[k].keycode[0];
    }
  }
}

int number_of_lines;

int parse_config(int argc, char *argv[]){

  FILE *fp = fopen(argv[1], "r");
  char line[255];
  if (fp == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[1]);
    exit(1);
  }

  number_of_lines= count_lines(fp);
  keymaps = calloc(number_of_lines, sizeof(Keymap));
  if (keymaps == NULL){
    perror("Failed allocating map of keys.");
    return (NULL);
  }

  int l;
  int next_line_is_a_modified_key = 0;
  for (int i=0; i<number_of_lines; i++){
    l = fgets(line, 255, (FILE*)fp);
    if(l != NULL){
      char delimiter[2] = ":";
      char *signifier = strtok(line, delimiter);
      char *signified = strtok(NULL, delimiter); // This feels wierd

      char *command = strtok(signified, ",");
      char *command_mode = strtok(NULL, ",");
      char *sanitized = strtok(command_mode, "\n");
      keymaps[i].onpress = atoi(&sanitized[1]);
      sanitized[1] = '\n';
      keymaps[i].mode = atoi(&sanitized[0]);

      char *key1 = strtok(signifier, "+");
      char *key2 = strtok(NULL, "+");
      char *key3 = strtok(NULL, "+");
      char *key4 = strtok(NULL, "+");
      char *key5 = strtok(NULL, "+");
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
        if(key5 != NULL){
          if(strcmp(key5, buttons[k].name) == 0){
            for(int j=0; j<16;j++){
              merged[j] = (merged[j] || buttons[k].binary[j]);
            }
          }
        }

        for(int j=0;j<16;j++){
          keymaps[i].binary_buttons[j] = merged[j];
        }
      }

      keymaps[i].t_modified = malloc(sizeof(TArray));
      if(strcmp(command, "=") == 0){
        next_line_is_a_modified_key = 1;
      }else{
        if(next_line_is_a_modified_key == 1){
          (*keymaps[i-1].t_modified).size++;
          int pos = (*keymaps[i-1].t_modified).size - 1;

          Keymap * new_keymaps = realloc(new_keymaps,(*keymaps[i-1].t_modified).size * sizeof(Keymap));

          for(int k=0;k<16;k++){
            if(k == 14){
              new_keymaps[pos].binary_buttons[k] =1;
            }else{
              new_keymaps[pos].binary_buttons[k] =0;
            }
          }
          new_keymaps[pos].is_func = keymaps[i].is_func;
          new_keymaps[pos].onpress = keymaps[i].onpress;
          (*keymaps[i-1].t_modified).repository = new_keymaps;

          next_line_is_a_modified_key = 0;
          populate_keycodes(&new_keymaps[pos], command, commands);
        }else{
          populate_keycodes(&keymaps[i], command, commands);
        }
      }
    }
  }

  return 0;
}
