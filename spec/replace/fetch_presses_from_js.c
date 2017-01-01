SDL_Joystick *joystick;

void fetch_presses_from_js(int *bin_buttons, SDL_Joystick *joystick){
  static counter = 0;
  //initialize
  for (int i=1; i < 16; i++){
    bin_buttons[i] = 0;
  }

  if(counter == 10) {
    bin_buttons[0] = 0;
    counter = 0;
  }else{
    bin_buttons[0] = 1;
    counter++;
  }
}

