#include "parse_config.c"

void print_result(struct keymap keymaps[]){
  for(int l=0; l<number_of_lines; l++){
    print_binary(keymaps[l].binary_buttons);
    printf(",%i,%i,%i, mode:%i\n", keymaps[l].keycode1, keymaps[l].keycode2,keymaps[l].keycode3, keymaps[l].mode);
    if((*keymaps[l].t_modified).repository !=0){
      for(int y=0; y<(*keymaps[l].t_modified).size; y++){
        printf(" - ");
        print_binary((*keymaps[l].t_modified).repository[y].binary_buttons);
        printf(",%i,%i,%i, mode:%i\n",
            (*keymaps[l].t_modified).repository[y].keycode1,
            (*keymaps[l].t_modified).repository[y].keycode2,
            (*keymaps[l].t_modified).repository[y].keycode3,
            (*keymaps[l].t_modified).repository[y].mode
            );
      }
    }
  }
}

int main(int argc, char *argv[]){
  parse_config(argc, argv);
  print_result(keymaps);
}
