#include <stdio.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>

void print_binary(char *binary_buttons){
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


  char buttons[15];
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

    print_binary(buttons);

  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

