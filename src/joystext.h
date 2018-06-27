int print_parsed_lower_level_config = 0;
int read_lower_level_config_file = 0;

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

TArray ref_array;

