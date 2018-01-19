#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "fetch_presses_from_js.c"
#include "sends.c"
#include <signal.h>

int should_run=1;

SDL_Joystick *joystick;
void signal_handler(int sig){
  should_run=0;
}
SDL_Event event;

void loop_and_print(){
  (void) signal(SIGINT, signal_handler);

  int buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  while(should_run){
    SDL_Delay(140);
    SDL_JoystickUpdate();

    fetch_microsoft_xbox360(buttons, joystick);

    int number_of_buttons = 16;
    for ( int i=0; i < number_of_buttons; i++ )
    {
      unsigned int n = SDL_JoystickGetButton ( joystick, i );
      printf("%i--> %i\n", i,n);
    }

    for ( int i=0; i<8; i++)
      printf("%i--> %i\n", i, SDL_JoystickGetAxis ( joystick, i ));

    signed short hat1 = SDL_JoystickGetHat ( joystick, 0 );
    signed short hat2 = SDL_JoystickGetHat ( joystick, 1 );

    printf("hat1:%i\n", hat1);
    printf("hat2:%i\n", hat2);

    print_binary(buttons);
    printf("\n");
  }
}

