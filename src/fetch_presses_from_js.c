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
}

int fetch_button(SDL_Joystick *joystick, int num){
  unsigned int n = SDL_JoystickGetButton ( joystick, num );
  if ( n != 1 )
    return 0;
  return 1;
}

void fetch_microsoft_xbox360(int *bin_buttons, SDL_Joystick *joystick){
  for (int i=0; i < 16; i++){
    bin_buttons[i] = 0;
  }

  bin_buttons[0] = fetch_button(joystick, 3);
  bin_buttons[1] = fetch_button(joystick, 1);
  bin_buttons[2] = fetch_button(joystick, 0);
  bin_buttons[3] = fetch_button(joystick, 2);

  bin_buttons[4] = fetch_button(joystick, 4);
  bin_buttons[5] = fetch_button(joystick, 5);


  bin_buttons[8] = fetch_button(joystick, 6);
  bin_buttons[9] = fetch_button(joystick, 7);

  int hat = SDL_JoystickGetHat(joystick,0);
  switch(hat){
    case 1:
      bin_buttons[14] = 1;
      break;
    case 2:
      bin_buttons[13] = 1;
      break;
    case 4:
      bin_buttons[15] = 1;
      break;
    case 8:
      bin_buttons[12] = 1;
      break;
    case 3:
      bin_buttons[14] = 1;
      bin_buttons[13] = 1;
      break;
    case 6:
      bin_buttons[15] = 1;
      bin_buttons[13] = 1;
      break;
    case 12:
      bin_buttons[15] = 1;
      bin_buttons[12] = 1;
      break;
    case 9:
      bin_buttons[12] = 1;
      bin_buttons[14] = 1;
      break;
  }

  signed short a3 = SDL_JoystickGetAxis ( joystick, 2 );
  signed short a4 = SDL_JoystickGetAxis ( joystick, 5 );

  if ( a3 > 0 ){
    bin_buttons[6] = 1;
  }
  if ( a4 > 0 ){
    bin_buttons[7] = 1;
  }

}
