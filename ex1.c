#include <stdio.h>
#include "SDL.h"
#include <stdio.h>

int main(int argc, char *argv[]){
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
  puts("initializing SDL");

  printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");

    int i;
    for( i=0; i < SDL_NumJoysticks(); i++ )
    {
        printf("    %s\n", SDL_JoystickName(i));
    }
  SDL_Quit();
  puts("quit sdl");

  return 0;
}

