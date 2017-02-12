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
int mine=0;
int modified=0;

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
  XFlush(display);
  XCloseDisplay(display);
}

void unclick(int num){
  Display* display = XOpenDisplay(0);
  XTestFakeButtonEvent(display, num, 0, 0);
  XFlush(display);
  XCloseDisplay(display);
}

void click_right(){
  click(3);
}

void unclick_right(){
  unclick(3);
}

void click_scroll(){
  click(2);
}

void unclick_scroll(){
  unclick(2);
}

void click_left(){
  click(1);
}

void unclick_left(){
  unclick(1);
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

void switch_to_mode(int mode_num){
  pointer_mode=mode_num;
  printf("switched to: %i\n", pointer_mode);
}

void toggle_left_click(){
  static int clicked = 0;
  if(clicked){
    unclick(1);
    clicked=0;
  }else{
    click(1);
    clicked=1;
  }
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
      switch_to_mode(0);
      break;
    case 20 :
      switch_to_mode(1);
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
    case 27 :
      switch_to_mode(2);
      break;
    case 28 :
      switch_to_mode(3);
      break;
    case 29 :
      switch_to_mode(4);
      break;
    case 30 :
      switch_to_mode(5);
      break;
    case 31 :
      switch_to_mode(6);
      break;
    case 32 :
      switch_to_mode(7);
      break;
    case 33 :
      switch_to_mode(8);
      break;
    case 34 :
      switch_to_mode(9);
      break;
    case 35 :
      toggle_left_click();
      break;
    case 36 :
      click_scroll();
      break;
    case 37 :
      unclick_scroll();
      break;
    case 38 :
      unclick_right();
      break;
    case 39 :
      unclick_left();
      break;
    default:
      printf("Function not found: %i\n", keyref.keycode1);
  }
}

int send_key(int *binary_buttons, TArray * ref_array,int onpress){
  int found_something=0;
  int cached_mode = pointer_mode;
  for(int i=0;i<(*ref_array).size;i++){
    if(memcmp(binary_buttons,(*ref_array).repository[i].binary_buttons, sizeof((*ref_array).repository[i].binary_buttons)) == 0
        && (*ref_array).repository[i].mode == cached_mode
        && (*ref_array).repository[i].onpress == onpress){
      if((*ref_array).repository[i].is_func){
        call_func((*ref_array).repository[i]);
        found_something=1;
      }else{
        if((*ref_array).repository[i].keycode2 !=0){
          if((*ref_array).repository[i].keycode3 !=0){
            send_keycode_mod_mod((*ref_array).repository[i].keycode1,
                (*ref_array).repository[i].keycode2,
                (*ref_array).repository[i].keycode3);
            found_something=1;
          }else{
            send_keycode_modified((*ref_array).repository[i].keycode1, (*ref_array).repository[i].keycode2);
            found_something=1;
          }
        }else{
          if((*ref_array).repository[i].keycode1 != 0){
            send_keycode((*ref_array).repository[i].keycode1);
            found_something=1;
          }
        }
      }
    }
  }
  return found_something;
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

int count_history(int history[100][16]){
  int count = 0;
  for(int i=0; i<100; i++){
    if(pressed_key(history[i])){
      count++;
    }
  }
  return count;
}

void check_for_once_filter(int * buttons, TArray * ref_array){
  static int history[100][16];
  static int counter = 0;
  int did_press_key= 0;
  int single[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  if(pressed_key(buttons)){
    if(counter == 0){
      for(int i=0; i<16; i++){
        if(buttons[i] == 1){
          for(int k=0; k<16;k++){
            if(k == i){
              single[k] = 1;
            }else{
              single[k] = 0;
            }
          }
          did_press_key = send_key(single, ref_array, 3);
        }
      }
      if(did_press_key){
        counter++;
      }
    }
  }else{
    counter=0;
  }
}

void check_for_filtered_events(int * buttons, TArray * ref_array, int * mine){
  static int history[100][16];
  static int sent_second = 0;
  static int sent_first = 0;
  static int counter = 0;
  int loop_window;

  if(pressed_key(buttons)){
    if(count_history(history) == 0 && sent_first == 0){
      send_key(buttons, ref_array,2);
      memset(history, 0, sizeof(history));
      counter=0;
      sent_first = 1;
      *mine = 1;
      return;
    }else{
      if(sent_second == 1){
        loop_window = 1;
      }else{
        loop_window = 20;
      }
      if(count_history(history) == loop_window){
        send_key(buttons, ref_array,2);
        memset(history, 0, sizeof(history));
        counter=0;
        sent_second = 1;
        *mine = 1;
        return;
      }
    }
    for(int i=0; i<16; i++)
      history[counter][i] = buttons[i];
    counter++;
  }else{
    memset(history, 0, sizeof(history));
    counter=0;
    sent_second=0;
    sent_first=0;
  }
}

TArray * get_ref_array(int * jsbuttons, TArray * ref){
  for(int j=0; j< (*ref).size; j++){
    for(int i=0;i<16;i++){
      if(jsbuttons[i] == 1 && (*ref).repository[j].binary_buttons[i] == 1){
        if((*ref).repository[j].mode == pointer_mode
            && (*(*ref).repository[j].t_modified).repository != 0){
          jsbuttons[i] = 0;
          modified = 1;
          return (*ref).repository[j].t_modified;
        }
      }
    }
  }
  modified = 0;
  return ref;
}

void loop_and_wait(){
  (void) signal(SIGINT, signal_handler);

  int buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int bck_buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int mod_history[100][16];

  //reset history
  for(int j=0;j<100;j++){
    for(int i=0;i<16;i++){
      mod_history[j][i]=0;
    }
  }
  int mod_counter=0;
  int mod_merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  while(should_run){
    SDL_Delay(40);
    SDL_JoystickUpdate();

    fetch_microsoft_xbox360(buttons, joystick);

    int all_pressed[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    if(memcmp(buttons, &all_pressed, sizeof(all_pressed)) == 0){
      should_run=0;
      break;
    }

    if(pressed_key(buttons) == 0)
      mine = 0;

    memcpy(bck_buttons, buttons, sizeof(bck_buttons));
    TArray ref_array = { keymaps, number_of_lines };
    TArray mod_array = * get_ref_array(buttons, &ref_array);

    check_for_press_events(buttons, &mod_array);

    if(modified){
      if(mine == 0){
        if(check_for_release_events(buttons,mod_history,mod_merged, &mod_counter,&mod_array)){
        }else{
          check_for_release_events(bck_buttons,mod_history,mod_merged, &mod_counter,&ref_array);
        }
      }
      check_for_filtered_events(buttons, &mod_array, &mine);
      check_for_once_filter(buttons, &mod_array);
    }else{
      if(mine == 0){
        if(check_for_release_events(buttons,mod_history,mod_merged, &mod_counter,&mod_array)){
        }else{
          check_for_release_events(bck_buttons,mod_history,mod_merged, &mod_counter,&ref_array);
        }
      }else{
        check_for_filtered_events(buttons, &mod_array, &mine);
      }
      check_for_once_filter(buttons, &ref_array);
    }
  }
}

