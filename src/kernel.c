#include <stdio.h>
#include <unistd.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include "fetch_presses_from_js.c"
#include "sends.c"
#include <signal.h>

int pointer_mode=0;
int pointer_step = 1;
int should_run=1;

void signal_handler(int sig){
  should_run=0;
}

void move_pointer(int dest_x,int dest_y){
  Display* display = XOpenDisplay(0);
  XWarpPointer(display, None, None, 0, 0, 0, 0, dest_x * pointer_step, dest_y * pointer_step);
  XFlush(display);
  XCloseDisplay(display);
}

void scroll(int scroll_direction, int step){
  Display* display = XOpenDisplay(0);
  int num;
  if(step == 1){
    num = 1;
  }else{
    num = step/5;
  }
  for(int i=0;i<(num); i++){
    XTestFakeButtonEvent(display, scroll_direction, 1, 0);
    XTestFakeButtonEvent(display, scroll_direction, 0, 0);
  }
  XFlush(display);
  XCloseDisplay(display);
}

void click(int num){
  Display* display = XOpenDisplay(0);
  XTestFakeButtonEvent(display, num, 1, 0);
  XTestFakeButtonEvent(display, num, 0, 0);
  XFlush(display);
  XCloseDisplay(display);
  usleep(200000);
}

void click_right(){
  click(3);
}

void click_left(){
  click(1);
}

void mouse_up(){
  move_pointer(0,-1);
}

void mouse_down(){
  move_pointer(0,1);
}

void mouse_left(){
  move_pointer(-1,0);
}

void mouse_right(){
  move_pointer(1,0);
}

void set_step(int step){
  pointer_step = step;
}

void scroll_up(){
  scroll(4, pointer_step);
}

void scroll_down(){
  scroll(5, pointer_step);
}

void scroll_right(){
  scroll(6, pointer_step);
}

void scroll_left(){
  scroll(7, pointer_step);
}

void switch_to_mode0(){
  pointer_mode=0;
  printf("switched to: %i\n", pointer_mode);
}

void switch_to_mode1(){
  pointer_mode=1;
  printf("switched to: %i\n", pointer_mode);
}

void call_func(struct keymap keyref){
  switch(keyref.keycode1){
    case 0 :
      mouse_up();
      break;
    case 1 :
      mouse_down();
      break;
    case 2 :
      mouse_left();
      break;
    case 3 :
      mouse_right();
      break;
    case 4 :
      set_step(5);
      break;
    case 5 :
      set_step(10);
      break;
    case 6 :
      set_step(15);
      break;
    case 7 :
      set_step(20);
      break;
    case 8 :
      set_step(25);
      break;
    case 9 :
      set_step(30);
      break;
    case 10 :
      set_step(35);
      break;
    case 11 :
      set_step(40);
      break;
    case 12 :
      set_step(45);
      break;
    case 13 :
      set_step(50);
      break;
    case 14 :
      set_step(55);
      break;
    case 15 :
      set_step(60);
      break;
    case 16 :
      set_step(65);
      break;
    case 17 :
      set_step(70);
      break;
    case 18 :
      set_step(75);
      break;
    case 19 :
      switch_to_mode0();
      break;
    case 20 :
      switch_to_mode1();
      break;
    case 21 :
      scroll_up();
      break;
    case 22 :
      scroll_down();
      break;
    case 23 :
      scroll_right();
      break;
    case 24 :
      scroll_left();
      break;
    case 25 :
      click_right();
      break;
    case 26 :
      click_left();
      break;
    default:
      printf("Function not found.");
  }
}

int send_key(int *binary_buttons, TArray * ref_array,int onpress){
  for(int i=0;i<(*ref_array).size;i++){
    if(memcmp(binary_buttons,(*ref_array).repository[i].binary_buttons, sizeof((*ref_array).repository[i].binary_buttons)) == 0
        && (*ref_array).repository[i].mode == pointer_mode
        && (*ref_array).repository[i].onpress == onpress){
      if((*ref_array).repository[i].is_func){
        call_func((*ref_array).repository[i]);
        return 1;
      }else{
        if((*ref_array).repository[i].keycode2 !=0){
          if((*ref_array).repository[i].keycode3 !=0){
            send_keycode_mod_mod((*ref_array).repository[i].keycode1,
                (*ref_array).repository[i].keycode2,
                (*ref_array).repository[i].keycode3);
            return 1;
          }else{
            send_keycode_modified((*ref_array).repository[i].keycode1, (*ref_array).repository[i].keycode2);
            return 1;
          }
        }else{
          if((*ref_array).repository[i].keycode1 != 0){
            send_keycode((*ref_array).repository[i].keycode1);
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

int check_for_press_events(int *binary_buttons, TArray * ref_array){
  int single[16];
  int did_press_key = 0;
  if(pressed_key(binary_buttons)){
    for(int i=0; i<16; i++){
      if(binary_buttons[i] == 1){
        for(int k=0; k<16;k++){
          if(k == i){
            single[k] = 1;
          }else{
            single[k] = 0;
          }
        }
       did_press_key = send_key(single, ref_array, 1);
      }
    }
    pointer_step =1;
  }
  return did_press_key;
}

int check_for_release_events(int *bin_buttons, int bin_history[100][16], int *bin_merged, int *counter_p, TArray * ref_array){
  int did_release_key = 0;
  for(int i=0; i<16;i++){
    bin_history[*counter_p][i] = bin_buttons[i];
  }

  if(pressed_key(bin_buttons)){
    did_release_key = 0;
  }else{
    for (int i=0; i<16; i++){
      bin_merged[i]=0;
    }

    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_merged[i] = (bin_history[j][i] || bin_merged[i]);
      }
    }

    //reset history
    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_history[j][i]=0;
      }
    }

    did_release_key = send_key(bin_merged, ref_array,0);
  }

  if(*counter_p>97){
    *counter_p = 0;
    //reset history
    for(int j=0;j<100;j++){
      for(int i=0;i<16;i++){
        bin_history[j][i]=0;
      }
    }
  }else{
    (*counter_p)++;
  }
  return did_release_key;
}

Keymap modemaps[2] = {
  {{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},1,1,0,19,0,0,0},
  {{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},1,0,0,20,0,0,0}
};
int modemaps_size = 2;

TArray * get_ref_array(int * jsbuttons, TArray * ref){
  for(int j=0; j< (*ref).size; j++){
    for(int i=0;i<16;i++){
      if(jsbuttons[i] == 1 && (*ref).repository[j].binary_buttons[i] == 1){
        if((*ref).repository[j].mode == pointer_mode
            && (*(*ref).repository[j].t_modified).repository != 0){
          jsbuttons[i] = 0;
          return (*ref).repository[j].t_modified;
        }
      }
    }
  }
  return ref;
}

void loop_and_wait(){
  (void) signal(SIGINT, signal_handler);

  int buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int mod_buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int mod_history[100][16];
  int history[100][16];
  int mode_history[100][16];

  //reset history
  for(int j=0;j<100;j++){
    for(int i=0;i<16;i++){
      history[j][i]=0;
    }
  }
  //reset history
  for(int j=0;j<100;j++){
    for(int i=0;i<16;i++){
      mod_history[j][i]=0;
    }
  }
  int counter=0;
  int mod_counter=0;
  int mode_counter=0;
  int mod_merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int mode_merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  while(should_run){
    SDL_Delay(40);
    SDL_JoystickUpdate();

    fetch_presses_from_js(mod_buttons, joystick);
    memcpy(buttons, mod_buttons, sizeof(mod_buttons));

    TArray ref_array = { keymaps, number_of_lines };
    TArray mod_array = * get_ref_array(buttons, &ref_array);

    TArray mode_array = { modemaps, modemaps_size };

    check_for_press_events(mod_buttons, &mod_array);
    check_for_release_events(mod_buttons,mod_history,mod_merged, &mod_counter,&mod_array);
    check_for_release_events(mod_buttons,mode_history,mode_merged, &mode_counter,&mode_array);
  }
}

