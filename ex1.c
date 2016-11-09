#include <stdio.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>


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
printf("botaoes: %i\n", SDL_JoystickNumButtons(joystick));

  SDL_Event event;
  Display* display = XOpenDisplay(0);

  while(1){
    SDL_Delay(120);
    SDL_JoystickUpdate();

    for ( int i=0; i < SDL_JoystickNumButtons ( joystick ); ++i )
    {
      unsigned int n = SDL_JoystickGetButton ( joystick, i );
      if ( n != 0 ){
        fprintf ( stdout, "found you pressed button %i\n", i );
        XTestFakeKeyEvent(display, 14, 1, 0);
        XTestFakeKeyEvent(display, 14, 0, 0);
      }
    }

    for ( int i=0; i < SDL_JoystickNumAxes ( joystick ); ++i )
    {
      signed short a = SDL_JoystickGetAxis ( joystick, i );
      if ( a != 0 )
        fprintf ( stdout, "axis %i is %d\n", i,a );
    }
    XFlush(display);
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

