#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "parse_config.c"
#include "loop_and_print.c"

int main(int argc, char *argv[]){
  parse_config(argc, argv);

  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
  {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }


  SDL_JoystickEventState(SDL_ENABLE);
  joystick = SDL_JoystickOpen(0);

  printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
  printf("The names of the joysticks are:\n");

  for(int i=0; i < SDL_NumJoysticks(); i++ )
  {
    printf("    %s\n", SDL_JoystickName(i));
  }

  printf("Number of buttons: %i\n", SDL_JoystickNumButtons(joystick));
  printf("Number of axes: %i\n", SDL_JoystickNumAxes(joystick));
  printf("Number of balls: %i\n", SDL_JoystickNumBalls(joystick));
  printf("Number of hats: %i\n", SDL_JoystickNumHats(joystick));

  loop_and_print();

  SDL_Quit();
  puts("Bye.");

  return 0;
}

