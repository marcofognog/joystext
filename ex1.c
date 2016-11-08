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
    while(SDL_PollEvent(&event))
    {
      printf("event type %d \n", event.type);

      if(event.type == 11){
        puts("apertou quadrado.");
      }
      switch(event.type)
      {
        case SDL_JOYBUTTONDOWN:
          puts("buttondow!!!!!!");
          break;
        case SDL_JOYAXISMOTION:
          puts("axis!!!!!");
          break;
        case SDL_JOYBUTTONUP:
          puts("up!!!!!!");
          break;
        case SDL_JOYHATMOTION:
          puts("hat!!!!!!");
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

