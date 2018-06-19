# include "../parser.tab.h"
# include <string.h>
# include <stdlib.h>

typedef struct NumberedMode{
  char name[200];
  int num;
} NumberedMode;

int current_mode = 0;
int remap = 0;
char *remap_button;
NumberedMode modes[10];

int get_mode_num(char * mode_name){
  int i = 0;
  int res;
  for(i; i < 9; i++){
    res = strcmp(mode_name, modes[i].name);
    if(res == 0){
      return modes[i].num;
      break;
    }
  }
  return -1;
}

void add_mode(char * mode_name, int position){
  strcpy(modes[position].name, mode_name);
  modes[position].num = position;
}

void print_modes(){
  int i = 0;
  for(i; i<9; i++){
    printf("name: %s, num: %i\n", modes[i].name, modes[i].num);
  }
}

void gen_mode(char *parsed_text) {
  current_mode = next_num();
  add_mode(parsed_text, current_mode);
}

void action_definition(char type_operand, char *action, char *cmd) {
  int type_val = 0;
  if (type_operand != '0'){
    switch (type_operand) {
      case '<' :
        type_val = 1;
        break;
      case '>' :
        type_val = 2;
        break;
      case '.' :
        type_val = 3;
        break;
    }
  }
  if (remap){
    char *remap_str;
    remap_str = malloc(40);
    snprintf(remap_str, 40, "%s:=,%i,%i\n", remap_button, current_mode, 0);
    printf(remap_str);
  }
  char *cmd_str;
  cmd_str = malloc(40);
  snprintf(cmd_str, 40, "%s:%s,%i,%i\n", action, cmd, current_mode, type_val);
  printf(cmd_str);
}

int find_max(int a[], int n) {
  int c, max, index;
  max = a[0];
  index = 0;
  for (c = 1; c < n; c++) {
    if (a[c] > max) {
       index = c;
       max = a[c];
    }
  }
  return index;
}

int next_num(){
  int res;
  int nums[10];
  int length = 0;

  int i = 0;
  for(i; i<9; i++){
    if (modes[i].name[0] != '\0'){
      nums[i] = modes[i].num;
      length++;
    }
  }
  res = find_max(&nums, length);
  if(length == 0){
    return 0;
  }else{
    return (res + 1);
  }
}

char * build_combo_command(char * s1, char * s2){
  char *buff;
  buff = malloc(20);
  snprintf(buff, 20, "%s+%s", s1, s2);
  return buff;
}

char * build_named_command(char * cmd, char * cmd_arg){
  int num = get_mode_num(cmd_arg);
  int res = 0;
  if (num != -1){
    res = num;
  } else {
    res = next_num();
    add_mode(cmd_arg, res);
  }

  char *complete_cmd;
  complete_cmd = malloc(20);
  snprintf(complete_cmd, 20, "switch_to_mode%i", res);
  return complete_cmd;
}

void close_remap() {
  remap = 0;
}

void open_remap(char *parsed_text) {
  remap_button = parsed_text;
  remap = 1;
}

char * concat(char *s1, char * s2){
  char *buf;
  buf = malloc(20);
  snprintf(buf, 20, "%s+%s", s1,s2);
  return buf;
}
