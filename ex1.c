#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "parse_config.c"

int pointer_mode=0;

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

void send_key(int *binary_buttons, struct keymap *key_ref,int onpress){
  int chosen_mode = 0; // temporary!

  if(pointer_mode == 0){
    for(int i=0;i<number_of_lines;i++){
      if(memcmp(binary_buttons,key_ref[i].binary_buttons, sizeof(key_ref[i].binary_buttons)) == 0
          && key_ref[i].mode == chosen_mode
          && key_ref[i].onpress == onpress){
        if(key_ref[i].keycode2 !=0){
          if(key_ref[i].keycode3 !=0){
            send_keycode_mod_mod(key_ref[i].keycode1, key_ref[i].keycode2, key_ref[i].keycode3);
          }else{
            send_keycode_modified(key_ref[i].keycode1, key_ref[i].keycode2);
          }
        }else{
          send_keycode(key_ref[i].keycode1);
        }
      }
    }
  }
}

void check_for_press_events(int *binary_buttons, struct keymap *key_reference){
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
        send_key(single, key_reference, 1);
      }
    }
  }
}

void check_for_release_events(int *bin_buttons, int bin_history[100][16], int *bin_merged, int *counter_p, struct keymap *key_referece){
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

    send_key(bin_merged, key_referece,0);
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

    check_for_press_events(buttons, keymaps);
    check_for_release_events(buttons,history,merged, &counter,keymaps);
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

