#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
# include "joystext.h"
#include "../parser.tab.c"
#include "../lex.yy.c"
#include "parse_config.c"
#include "kernel.c"
#include "options.c"

int main(int argc, char *argv[]){
  parse_options(argc, argv);

  if(print_parsed_lower_level_config == 0){
    if(read_lower_level_config_file == 0){
      parse_high_level_config(argv[1]);
    } else {
      parse_lower_level_config(argc, argv[2]);
    }
  }else{
    parse_high_level_config(argv[2]);
  }

  if(print_parsed_lower_level_config == 0){
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

    loop_and_wait();

    SDL_Quit();
    puts("Bye.");
  }

  return 0;
}

