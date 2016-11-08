#include <stdio.h>
#include "SDL.h"

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

puts("lista de events:");
printf("%d\n", SDL_JOYBUTTONDOWN);
printf("%d\n", SDL_JOYAXISMOTION);
printf("%d\n", SDL_JOYBUTTONUP);
printf("%d\n", SDL_JOYHATMOTION);
printf("%d\n", SDL_JOYBALLMOTION);

  SDL_Event event;
  while(1){
    SDL_Delay(10);
    while(SDL_PollEvent(&event))
    {
      //printf("%d \n", event.type);
      switch(event.type)
      {
        case 16973834:
          puts("4");
          break;
        case 16777226:
          puts("1");
          break;
        case 16842762:
          puts("2");
          break;
        case 16908298:
          puts("3");
          break;
        case SDL_JOYBALLMOTION:
          puts("ball!!!!!!");
          break;
      }
    }
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

