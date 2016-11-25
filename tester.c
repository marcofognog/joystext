#include "parse_config.c"

void print_result(struct keymap keymaps[]){
  for(int l=0; l<200; l++){
    if(pressed_key(keymaps[l].binary_buttons)){
      print_binary(keymaps[l].binary_buttons);
      printf(",%i,%i,%i\n", keymaps[l].keycode1, keymaps[l].keycode2,keymaps[l].keycode3);
    }
  }
}

int main(int argc, char *argv[]){
  parse_config(argc, argv);
  print_result(keymaps);
}
