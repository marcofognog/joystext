#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "parse_config.c"

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

void send_key(int *binary_buttons){
  // Make this limit the same as the number of keybindings in the conf file.
  for(int i=0;i<number_of_lines;i++){
    if(memcmp(binary_buttons,keymaps[i].binary_buttons, sizeof(keymaps[i].binary_buttons)) == 0){
      if(keymaps[i].keycode2 !=0){
        if(keymaps[i].keycode3 !=0){
          send_keycode_mod_mod(keymaps[i].keycode1, keymaps[i].keycode2, keymaps[i].keycode3);
        }else{
          send_keycode_modified(keymaps[i].keycode1, keymaps[i].keycode2);
        }
      }else{
        send_keycode(keymaps[i].keycode1);
      }
    }
  }
}

void check_for_pointer_events(int *binary_buttons){
  if(pressed_key(binary_buttons)){
    int dest_x=0;
    int dest_y=0;
    int step=1;

    if(binary_buttons[14])
      dest_y=-1;
    if(binary_buttons[15])
      dest_y=1;
    if(binary_buttons[12])
      dest_x=-1;
    if(binary_buttons[13])
      dest_x=1;

    int speed1[16]={1,0,0,0};
    int speed2[16]={1,1,0,0};
    int speed3[16]={0,1,0,0};
    int speed4[16]={0,1,1,0};
    int speed5[16]={0,0,1,0};
    int speed6[16]={0,0,1,1};
    int speed7[16]={0,0,0,1};
    int speed8[16]={1,0,0,1};
    int segment[4]={0,0,0,0};

    for(int i=0; i<4;i++){
      segment[i] = binary_buttons[i];
    }

    if(memcmp(segment,speed1, sizeof(segment)) == 0)
      step = 10;
    if(memcmp(segment,speed2, sizeof(segment)) == 0)
      step = 20;
    if(memcmp(segment,speed3, sizeof(segment)) == 0)
      step = 30;
    if(memcmp(segment,speed4, sizeof(segment)) == 0)
      step = 40;
    if(memcmp(segment,speed5, sizeof(segment)) == 0)
      step = 55;
    if(memcmp(segment,speed6, sizeof(segment)) == 0)
      step = 65;
    if(memcmp(segment,speed7, sizeof(segment)) == 0)
      step = 75;
    if(memcmp(segment,speed8, sizeof(segment)) == 0)
      step = 85;

    Display* display = XOpenDisplay(0);
    XWarpPointer(display, None, None, 0, 0, 0, 0, dest_x * step,dest_y * step);

    if(binary_buttons[4]){
      XTestFakeButtonEvent(display, 1, 1, 0);
      XTestFakeButtonEvent(display, 1, 0, 0);
      usleep(200000);
    }
    if(binary_buttons[5]){
      XTestFakeButtonEvent(display, 3, 1, 0);
      XTestFakeButtonEvent(display, 3, 0, 0);
      usleep(200000);
    }

    XFlush(display);
    XCloseDisplay(display);
  }
}

void check_for_text_events(int *bin_buttons, int bin_history[100][16], int *bin_merged, int *counter_p){
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
    send_key(bin_merged);
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
  int pointer_mode_history[100];
  int text_mode_history[100];
  int mode_counter = 0;

  //reset history
  for(int j=0;j<10;j++){
    for(int i=0;i<16;i++){
      history[j][i]=0;
    }
  }
  int counter=0;
  int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  int pointer_mode=0;
  int start_button = 9;
  int select_button = 8;

  while(1){
    SDL_Delay(40);
    SDL_JoystickUpdate();

    //initialize
    for (int i=0; i < 16; i++){
      buttons[i] = 0;
    }

    for ( int i=0; i < 12; i++ )
    {
      unsigned int n = SDL_JoystickGetButton ( joystick, i );
      if ( n != 0 )
        buttons[i] = 1;
    }

    signed short a1 = SDL_JoystickGetAxis ( joystick, 0 );
    signed short a2 = SDL_JoystickGetAxis ( joystick, 1 );
    if ( a1 != 0 ){
      if ( a1 < 0 ){
        buttons[12] = 1;
      } else {
        buttons[13] = 1;
      }
    }
    if ( a2 != 0 ){
      if ( a2 < 0 ){
        buttons[14] = 1;
      } else {
        buttons[15] = 1;
      }
    }

    if(pointer_mode != 1){
      check_for_text_events(buttons,history,merged, &counter);
    }else{
      check_for_pointer_events(buttons);
    }

    pointer_mode_history[mode_counter] = buttons[start_button];
    text_mode_history[mode_counter] = buttons[select_button];
    if(pressed_key(buttons)){
    }else{
      mode_counter = 0;
      int released_start = 0;
      int released_select = 0;
      for(int j=0;j<100;j++){
        released_start = (pointer_mode_history[j] || released_start);
      }
      for(int j=0;j<100;j++){
        released_select = (text_mode_history[j] || released_select);
      }

      if(released_select){
        pointer_mode=0;
        printf("Pointer mode disabled.\n");
      }
      if(released_start){
        pointer_mode=1;
        printf("Pointer mode enabled.\n");
      }
      for(int j=0;j<100;j++){
        pointer_mode_history[j]=0;
      }
      for(int j=0;j<100;j++){
        text_mode_history[j]=0;
      }
    }

    if(mode_counter>97){
      mode_counter = 0;
      for(int j=0;j<100;j++){
        pointer_mode_history[j]=0;
      }
      for(int j=0;j<100;j++){
        text_mode_history[j]=0;
      }
    }else{
      mode_counter++;
    }
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

