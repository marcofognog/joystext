#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "parse_config.c"

int pointer_mode=0;
int pointer_step = 1;

void send_keycode(keysym){
  Display* display = XOpenDisplay(0);
  int val = XKeysymToKeycode(display, keysym);
  XTestFakeKeyEvent(display,val,1,0);
  XTestFakeKeyEvent(display,val,0,0);
  XFlush(display);
  XCloseDisplay(display);
}

void send_keycode_modified(modifier, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode = XKeysymToKeycode(display, modifier);
  XTestFakeKeyEvent(display,modcode,1,0);
  XTestFakeKeyEvent(display,keycode,1,0);
  XTestFakeKeyEvent(display,keycode,0,0);
  XTestFakeKeyEvent(display,modcode,0,0);
  XFlush(display);
}

void send_keycode_mod_mod(mod1,mod2, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode1 = XKeysymToKeycode(display, mod1);
  int modcode2 = XKeysymToKeycode(display, mod2);

  XTestFakeKeyEvent(display,modcode1,1,0);
  XTestFakeKeyEvent(display,modcode2,1,0);
  XTestFakeKeyEvent(display,keycode,1,0);
  XTestFakeKeyEvent(display,keycode,0,0);
  XTestFakeKeyEvent(display,modcode1,0,0);
  XTestFakeKeyEvent(display,modcode2,0,0);
  XFlush(display);
}

void move_pointer(int dest_x,int dest_y, int step){
  Display* display = XOpenDisplay(0);
  XWarpPointer(display, None, None, 0, 0, 0, 0, dest_x * pointer_step, dest_y * pointer_step);
  XFlush(display);
  XCloseDisplay(display);
}

void mouse_up(){
  move_pointer(0,-1,1);
}

void mouse_down(){
  move_pointer(0,1,1);
}

void mouse_left(){
  move_pointer(-1,0,1);
}

void mouse_right(){
  move_pointer(1,0,1);
}

void set_step(int step){
  pointer_step = step;
}

void call_func(struct keymap keyref){
  switch(keyref.keycode1){
    case 0 :
      mouse_up();
      break;
    case 1 :
      mouse_down();
      break;
    case 2 :
      mouse_left();
      break;
    case 3 :
      mouse_right();
      break;
    case 4 :
      set_step(5);
      break;
    case 5 :
      set_step(10);
      break;
    case 6 :
      set_step(15);
      break;
    case 7 :
      set_step(20);
      break;
    case 8 :
      set_step(25);
      break;
    case 9 :
      set_step(30);
      break;
    case 10 :
      set_step(35);
      break;
    case 11 :
      set_step(40);
      break;
    case 12 :
      set_step(45);
      break;
    case 13 :
      set_step(50);
      break;
    case 14 :
      set_step(55);
      break;
    case 15 :
      set_step(60);
      break;
    case 16 :
      set_step(65);
      break;
    case 17 :
      set_step(70);
      break;
    case 18 :
      set_step(75);
      break;
    default:
      printf("Function not found.");
  }
}

void send_key(int *binary_buttons, TArray * ref_array,int onpress){
  int chosen_mode = 0; // temporary!

  if(pointer_mode == 0){
    for(int i=0;i<(*ref_array).size;i++){
      if(memcmp(binary_buttons,(*ref_array).repository[i].binary_buttons, sizeof((*ref_array).repository[i].binary_buttons)) == 0
          && (*ref_array).repository[i].mode == chosen_mode
          && (*ref_array).repository[i].onpress == onpress){
        if((*ref_array).repository[i].is_func){
          call_func((*ref_array).repository[i]);
        }else{
          if((*ref_array).repository[i].keycode2 !=0){
            if((*ref_array).repository[i].keycode3 !=0){
              send_keycode_mod_mod((*ref_array).repository[i].keycode1,
                  (*ref_array).repository[i].keycode2,
                  (*ref_array).repository[i].keycode3);
            }else{
              send_keycode_modified((*ref_array).repository[i].keycode1, (*ref_array).repository[i].keycode2);
            }
          }else{
            send_keycode((*ref_array).repository[i].keycode1);
          }
        }
      }
    }
  }
}

void check_for_press_events(int *binary_buttons, TArray * ref_array){
  int single[16];
  if(pressed_key(binary_buttons)){
    for(int i=0; i<16; i++){
      if(binary_buttons[i] == 1){
        for(int k=0; k<16;k++){
          if(k == i){
            single[k] = 1;
          }else{
            single[k] = 0;
          }
        }
        send_key(single, ref_array, 1);
      }
    }
    pointer_step =1;
  }
}

void check_for_release_events(int *bin_buttons, int bin_history[100][16], int *bin_merged, int *counter_p, TArray * ref_array){
  for(int i=0; i<16;i++){
    bin_history[*counter_p][i] = bin_buttons[i];
  }

  if(pressed_key(bin_buttons)){
  }else{
    for (int i=0; i<16; i++){
      bin_merged[i]=0;
    }

    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_merged[i] = (bin_history[j][i] || bin_merged[i]);
      }
    }

    //reset history
    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_history[j][i]=0;
      }
    }

    send_key(bin_merged, ref_array,0);
  }

  if(*counter_p>97){
    *counter_p = 0;
    //reset history
    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_history[j][i]=0;
      }
    }
  }else{
    (*counter_p)++;
  }
}

void fetch_presses_from_js(int *bin_buttons, SDL_Joystick *joystick){
  //initialize
  for (int i=0; i < 16; i++){
    bin_buttons[i] = 0;
  }

  for ( int i=0; i < 12; i++ )
  {
    unsigned int n = SDL_JoystickGetButton ( joystick, i );
    if ( n != 0 )
      bin_buttons[i] = 1;
  }

  signed short a1 = SDL_JoystickGetAxis ( joystick, 0 );
  signed short a2 = SDL_JoystickGetAxis ( joystick, 1 );
  if ( a1 != 0 ){
    if ( a1 < 0 ){
      bin_buttons[12] = 1;
    } else {
      bin_buttons[13] = 1;
    }
  }
  if ( a2 != 0 ){
    if ( a2 < 0 ){
      bin_buttons[14] = 1;
    } else {
      bin_buttons[15] = 1;
    }
  }
}

TArray * get_ref_array(int * jsbuttons, TArray * ref){
  int chosen_mode = 0;
  for(int j=0; j< (*ref).size; j++){
    for(int i=0;i<16;i++){
      if(jsbuttons[i] == 1 && (*ref).repository[j].binary_buttons[i] == 1){
        if((*ref).repository[j].mode == chosen_mode
            && (*(*ref).repository[j].t_modified).repository != 0){
          jsbuttons[i] = 0;
          return (*ref).repository[j].t_modified;
        }
      }
    }
  }
  return ref;
}

int main(int argc, char *argv[]){
  parse_config(argc, argv);

  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
  {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Joystick *joystick;

  SDL_JoystickEventState(SDL_ENABLE);
  joystick = SDL_JoystickOpen(0);

  printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
  printf("The names of the joysticks are:\n");

  for(int i=0; i < SDL_NumJoysticks(); i++ )
  {
    printf("    %s\n", SDL_JoystickName(i));
  }

  printf("botaoes: %i\n", SDL_JoystickNumButtons(joystick));

  int buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int history[100][16];

  //reset history
  for(int j=0;j<10;j++){
    for(int i=0;i<16;i++){
      history[j][i]=0;
    }
  }
  int counter=0;
  int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


  while(1){
    SDL_Delay(40);
    SDL_JoystickUpdate();

    fetch_presses_from_js(buttons, joystick);

    TArray ref_array = { keymaps, number_of_lines };
    ref_array = * get_ref_array(buttons, &ref_array);
    check_for_press_events(buttons, &ref_array);
    check_for_release_events(buttons,history,merged, &counter,&ref_array);
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

