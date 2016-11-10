#include <stdio.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>

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
    printf("a\n");
  if(memcmp(binary_buttons,b, sizeof(b)) == 0)
    printf("b\n");
  if(memcmp(binary_buttons,c, sizeof(c)) == 0)
    printf("c\n");
  if(memcmp(binary_buttons,d, sizeof(d)) == 0)
    printf("d\n");
  if(memcmp(binary_buttons,e, sizeof(e)) == 0)
    printf("e\n");
  if(memcmp(binary_buttons,f, sizeof(f)) == 0)
    printf("f\n");
  if(memcmp(binary_buttons,g, sizeof(g)) == 0)
    printf("g\n");
  if(memcmp(binary_buttons,h, sizeof(h)) == 0)
    printf("h\n");
  if(memcmp(binary_buttons,i, sizeof(h)) == 0)
    printf("i\n");
  if(memcmp(binary_buttons,j, sizeof(h)) == 0)
    printf("j\n");
  if(memcmp(binary_buttons,k, sizeof(h)) == 0)
    printf("k\n");
  if(memcmp(binary_buttons,l, sizeof(h)) == 0)
    printf("l\n");
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
  Display* display = XOpenDisplay(0);


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

