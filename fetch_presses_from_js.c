SDL_Joystick *joystick;

void fetch_presses_from_js(int *bin_buttons, SDL_Joystick *joystick){
  //initialize
  for (int i=0; i < 16; i++){
    bin_buttons[i] = 0;
  }

  for ( int i=0; i < 12; i++ )
  {
    unsigned int n = SDL_JoystickGetButton ( joystick, i );
    if ( n != 0 )
      bin_buttons[i] = 1;
  }

  signed short a1 = SDL_JoystickGetAxis ( joystick, 0 );
  signed short a2 = SDL_JoystickGetAxis ( joystick, 1 );
  if ( a1 != 0 ){
    if ( a1 < 0 ){
      bin_buttons[12] = 1;
    } else {
      bin_buttons[13] = 1;
    }
  }
  if ( a2 != 0 ){
    if ( a2 < 0 ){
      bin_buttons[14] = 1;
    } else {
      bin_buttons[15] = 1;
    }
  }
}

