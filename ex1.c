#include <stdio.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

void print_binary(int *binary_buttons){
  int print_flag = 0;
  for (int i=0; i < 16; i++) {
    int b = binary_buttons[i] -0;
    if(b){
      print_flag = 1;
    }
  }
  if(print_flag){
    for (int i=0; i < 16; i++) {
      printf("%i", binary_buttons[i]);
    }
    printf("\n");
    print_flag = 0;
  }
}

void send_keycode(keysym){
  Display* display = XOpenDisplay(0);
  int val = XKeysymToKeycode(display, keysym);
  XTestFakeKeyEvent(display,val,1,0);
  XTestFakeKeyEvent(display,val,0,0);
  XFlush(display);
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

void send_key(int *binary_buttons){
  int a[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int b[16] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int c[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int d[16] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};
  int e[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
  int f[16] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0};
  int g[16] = {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
  int h[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
  int i[16] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};
  int j[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
  int k[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int l[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

  if(memcmp(binary_buttons,a, sizeof(a)) == 0)
    send_keycode(XK_a);
  if(memcmp(binary_buttons,b, sizeof(b)) == 0)
    send_keycode(XK_b);
  if(memcmp(binary_buttons,c, sizeof(c)) == 0)
    send_keycode(XK_c);
  if(memcmp(binary_buttons,d, sizeof(d)) == 0)
    send_keycode(XK_d);
  if(memcmp(binary_buttons,e, sizeof(e)) == 0)
    send_keycode(XK_e);
  if(memcmp(binary_buttons,f, sizeof(f)) == 0)
    send_keycode(XK_f);
  if(memcmp(binary_buttons,g, sizeof(g)) == 0)
    send_keycode(XK_g);
  if(memcmp(binary_buttons,h, sizeof(h)) == 0)
    send_keycode(XK_h);
  if(memcmp(binary_buttons,i, sizeof(h)) == 0)
    send_keycode(XK_i);
  if(memcmp(binary_buttons,j, sizeof(h)) == 0)
    send_keycode(XK_j);
  if(memcmp(binary_buttons,k, sizeof(h)) == 0)
    send_keycode(XK_k);
  if(memcmp(binary_buttons,l, sizeof(h)) == 0)
    send_keycode_modified(XK_Shift_L, XK_z);
}


int main(int argc, char *argv[]){
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

  int i;
  for( i=0; i < SDL_NumJoysticks(); i++ )
  {
    printf("    %s\n", SDL_JoystickName(i));
  }

  printf("botaoes: %i\n", SDL_JoystickNumButtons(joystick));

  SDL_Event event;


  int buttons[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  while(1){
    SDL_Delay(20);
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

    send_key(buttons);
    print_binary(buttons);
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

