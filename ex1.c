#include <stdio.h>
#include "SDL.h"
#include <stdio.h>

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

  SDL_Event event;
  while(1){
  while(SDL_PollEvent(&event))
  {
    puts("eaaa");
    switch(event.type)
    {
      case SDL_JOYBUTTONDOWN:
        puts("apertou!!!!!!");
        break;
    }
  }
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

