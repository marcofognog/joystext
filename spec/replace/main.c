#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "parse_config.c"
#include "kernel.c"

int main(int argc, char *argv[]){
  parse_config(argc, argv);

  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
  {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  loop_and_wait();

  SDL_Quit();

  return 0;
}

