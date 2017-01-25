SDL_Joystick *joystick;

void fetch_presses_from_js(int *bin_buttons, SDL_Joystick *joystick){
  char temp_buttons[18];
  gets(temp_buttons);

  for(int i=0; i<16;i++){
    if(temp_buttons[i] == '1'){
      bin_buttons[i] = 1;
    }else{
      bin_buttons[i] = 0;
    }
  }

  return 0;
}

void fetch_microsoft_xbox360(int *bin_buttons, SDL_Joystick *joystick){
  char temp_buttons[18];
  gets(temp_buttons);

  for(int i=0; i<16;i++){
    if(temp_buttons[i] == '1'){
      bin_buttons[i] = 1;
    }else{
      bin_buttons[i] = 0;
    }
  }

  return 0;
}
