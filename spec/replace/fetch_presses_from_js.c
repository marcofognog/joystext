SDL_Joystick *joystick;

void fetch_presses_from_js(int *bin_buttons, SDL_Joystick *joystick){
  char temp_buttons[18];
  gets(temp_buttons);


  for(int i=0; i<16;i++){
    bin_buttons[i] = atoi(&temp_buttons[i]);
  }

  return 0;
}

