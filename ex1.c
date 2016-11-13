#include <stdio.h>
#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

int pressed_key(int *binary_buttons){
  int print_flag = 0;
  for (int i=0; i < 16; i++) {
    int b = binary_buttons[i] -0;
    if(b){
      print_flag = 1;
    }
  }
  return print_flag;
}

void print_binary(int *binary_buttons){
  for (int i=0; i < 16; i++) {
    printf("%i", binary_buttons[i]);
  }
  printf("\n");
}

void send_keycode(keysym){
  Display* display = XOpenDisplay(0);
  int val = XKeysymToKeycode(display, keysym);
  XTestFakeKeyEvent(display,val,1,0);
  XTestFakeKeyEvent(display,val,0,0);
  XFlush(display);
  XCloseDisplay(display);
}

void send_keycode_modified(modifier, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode = XKeysymToKeycode(display, modifier);
  XTestFakeKeyEvent(display,modcode,1,0);
  XTestFakeKeyEvent(display,keycode,1,0);
  XTestFakeKeyEvent(display,keycode,0,0);
  XTestFakeKeyEvent(display,modcode,0,0);
  XFlush(display);
}

void send_key(int *binary_buttons){
  int a[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int e[16] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int i[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int o[16] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};
  int u[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int b[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
  int c[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
  int d[16] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};
  int f[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int g[16] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int h[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int j[16] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0};
  int k[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
  int l[16] = {0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
  int m[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0};
  int n[16] = {0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0};
  int p[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
  int q[16] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
  int r[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1};
  int s[16] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1};
  int t[16] = {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};
  int v[16] = {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0};
  int w[16] = {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0};
  int x[16] = {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0};
  int y[16] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int z[16] = {0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0};
  int space[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
  int enter[16] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0};
  int backspace[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
  int shift[16] = {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
  int semi_colon[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
  int colon[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
  int slash[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0};
  int escape[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
  int comma[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int dot[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int minus[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int plus[16] = {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int left_parenthesis[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int right_parenthesis[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int left_square_bracket[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int right_square_bracket[16] = {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int left_curly_bracket[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int right_curly_bracket[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int exclamation[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int at[16] = {0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int sharp[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int dollar[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int percent[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int single_quote[16] = {0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int pipe[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0};
  int asterisk[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0};
  int underscore[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1};
  int double_quote[16] = {0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0};
  int ampersand[16] = {1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int equal[16] = {0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0};
  int less[16] = {1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int greater[16] = {0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0};
  int page_up[16] = {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0};
  int end[16] = {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0};
  int page_down[16] = {0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0};
  int home[16] = {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0};
  int arrow_up[16] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0};
  int arrow_right[16] = {0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0};
  int arrow_down[16] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1};
  int arrow_left[16] = {0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0};
  int one[16] = {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0};
  int two[16] = {0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0};
  int three[16] = {0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0};
  int four[16] = {0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0};
  int five[16] = {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0};
  int six[16] = {0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0};
  int seven[16] = {0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0};
  int eight[16] = {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0};
  int nine[16] = {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1};
  int zero[16] = {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1};

  if(memcmp(binary_buttons,a, sizeof(a)) == 0)
    send_keycode(XK_a);
  if(memcmp(binary_buttons,e, sizeof(e)) == 0)
    send_keycode(XK_e);
  if(memcmp(binary_buttons,i, sizeof(i)) == 0)
    send_keycode(XK_i);
  if(memcmp(binary_buttons,o, sizeof(o)) == 0)
    send_keycode(XK_o);
  if(memcmp(binary_buttons,u, sizeof(u)) == 0)
    send_keycode(XK_u);
  if(memcmp(binary_buttons,d, sizeof(e)) == 0)
    send_keycode(XK_d);
  if(memcmp(binary_buttons,c, sizeof(c)) == 0)
    send_keycode(XK_c);
  if(memcmp(binary_buttons,j, sizeof(j)) == 0)
    send_keycode(XK_j);
  if(memcmp(binary_buttons,b, sizeof(h)) == 0)
    send_keycode(XK_b);
  if(memcmp(binary_buttons,g, sizeof(g)) == 0)
    send_keycode(XK_g);
  if(memcmp(binary_buttons,f, sizeof(f)) == 0)
    send_keycode(XK_f);
  if(memcmp(binary_buttons,h, sizeof(h)) == 0)
    send_keycode(XK_h);
  if(memcmp(binary_buttons,k, sizeof(k)) == 0)
    send_keycode(XK_k);
  if(memcmp(binary_buttons,l, sizeof(l)) == 0)
    send_keycode(XK_l);
  if(memcmp(binary_buttons,m, sizeof(m)) == 0)
    send_keycode(XK_m);
  if(memcmp(binary_buttons,n, sizeof(n)) == 0)
    send_keycode(XK_n);
  if(memcmp(binary_buttons,p, sizeof(p)) == 0)
    send_keycode(XK_p);
  if(memcmp(binary_buttons,q, sizeof(q)) == 0)
    send_keycode(XK_q);
  if(memcmp(binary_buttons,r, sizeof(r)) == 0)
    send_keycode(XK_r);
  if(memcmp(binary_buttons,s, sizeof(s)) == 0)
    send_keycode(XK_s);
  if(memcmp(binary_buttons,t, sizeof(t)) == 0)
    send_keycode(XK_t);
  if(memcmp(binary_buttons,v, sizeof(v)) == 0)
    send_keycode(XK_v);
  if(memcmp(binary_buttons,w, sizeof(w)) == 0)
    send_keycode(XK_w);
  if(memcmp(binary_buttons,x, sizeof(x)) == 0)
    send_keycode(XK_x);
  if(memcmp(binary_buttons,y, sizeof(y)) == 0)
    send_keycode(XK_y);
  if(memcmp(binary_buttons,z, sizeof(z)) == 0)
    send_keycode(XK_z);
  if(memcmp(binary_buttons,space, sizeof(space)) == 0)
    send_keycode(XK_space);
  if(memcmp(binary_buttons,enter, sizeof(enter)) == 0)
    send_keycode(XK_Return);
  if(memcmp(binary_buttons,backspace, sizeof(backspace)) == 0)
    send_keycode(XK_BackSpace);
  if(memcmp(binary_buttons,semi_colon, sizeof(semi_colon)) == 0)
    send_keycode(XK_semicolon);

  if(memcmp(binary_buttons,shift, sizeof(shift)) == 0)
    send_keycode(XK_Shift_L);
  if(memcmp(binary_buttons,colon, sizeof(colon)) == 0)
    send_keycode_modified(XK_Shift_L, XK_colon);
  if(memcmp(binary_buttons,slash, sizeof(slash)) == 0)
    send_keycode(XK_slash);
  if(memcmp(binary_buttons,escape, sizeof(escape)) == 0)
    send_keycode(XK_Escape);
  if(memcmp(binary_buttons,comma, sizeof(comma)) == 0)
    send_keycode(XK_comma);
  if(memcmp(binary_buttons,dot, sizeof(dot)) == 0)
    send_keycode(XK_period);
  if(memcmp(binary_buttons,minus, sizeof(minus)) == 0)
    send_keycode(XK_minus);
  if(memcmp(binary_buttons,plus, sizeof(plus)) == 0)
    send_keycode_modified(XK_Shift_L,XK_plus);
  if(memcmp(binary_buttons,left_parenthesis, sizeof(left_parenthesis)) == 0)
    send_keycode(XK_parenleft);
  if(memcmp(binary_buttons,right_parenthesis, sizeof(right_parenthesis)) == 0)
    send_keycode(XK_parenright);
  if(memcmp(binary_buttons,left_square_bracket, sizeof(left_square_bracket)) == 0)
    send_keycode(XK_bracketleft);
  if(memcmp(binary_buttons,right_square_bracket, sizeof(right_square_bracket)) == 0)
    send_keycode(XK_bracketright);
  if(memcmp(binary_buttons,left_curly_bracket, sizeof(left_curly_bracket)) == 0)
    send_keycode_modified(XK_Shift_L, XK_braceleft);
  if(memcmp(binary_buttons,right_curly_bracket, sizeof(right_curly_bracket)) == 0)
    send_keycode_modified(XK_Shift_L, XK_braceright);
  if(memcmp(binary_buttons,exclamation, sizeof(exclamation)) == 0)
    send_keycode_modified(XK_Shift_L,XK_exclam);
  if(memcmp(binary_buttons,at, sizeof(at)) == 0)
    send_keycode_modified(XK_Shift_L,XK_at);
  if(memcmp(binary_buttons,sharp, sizeof(sharp)) == 0)
    send_keycode_modified(XK_Shift_L,XK_numbersign);
  if(memcmp(binary_buttons,dollar, sizeof(dollar)) == 0)
    send_keycode_modified(XK_Shift_L,XK_dollar);
  if(memcmp(binary_buttons,percent, sizeof(percent)) == 0)
    send_keycode_modified(XK_Shift_L,XK_percent);
  if(memcmp(binary_buttons,single_quote, sizeof(single_quote)) == 0)
    send_keycode(XK_quotedbl);
  if(memcmp(binary_buttons,pipe, sizeof(pipe)) == 0)
    send_keycode_modified(XK_Shift_L,XK_bar);
  if(memcmp(binary_buttons,asterisk, sizeof(asterisk)) == 0)
    send_keycode_modified(XK_Shift_L,XK_asterisk);
  if(memcmp(binary_buttons,underscore, sizeof(underscore)) == 0)
    send_keycode_modified(XK_Shift_L,XK_underscore);
  if(memcmp(binary_buttons,double_quote, sizeof(double_quote)) == 0)
    send_keycode_modified(XK_Shift_L,XK_quotedbl);
  if(memcmp(binary_buttons,ampersand, sizeof(ampersand)) == 0)
    send_keycode_modified(XK_Shift_L,XK_ampersand);
  if(memcmp(binary_buttons,page_up, sizeof(page_up)) == 0)
    send_keycode(XK_Page_Up);
  if(memcmp(binary_buttons,page_down, sizeof(page_down)) == 0)
    send_keycode(XK_Page_Down);
  if(memcmp(binary_buttons,home, sizeof(home)) == 0)
    send_keycode(XK_Begin);
  if(memcmp(binary_buttons,end, sizeof(end)) == 0)
    send_keycode(XK_End);
  if(memcmp(binary_buttons,arrow_up, sizeof(arrow_up)) == 0)
    send_keycode(XK_Up);
  if(memcmp(binary_buttons,arrow_down, sizeof(arrow_down)) == 0)
    send_keycode(XK_Down);
  if(memcmp(binary_buttons,arrow_right, sizeof(arrow_right)) == 0)
    send_keycode(XK_Right);
  if(memcmp(binary_buttons,arrow_left, sizeof(arrow_left)) == 0)
    send_keycode(XK_Left);
  if(memcmp(binary_buttons,one, sizeof(one)) == 0)
    send_keycode(XK_1);
  if(memcmp(binary_buttons,two, sizeof(two)) == 0)
    send_keycode(XK_2);
  if(memcmp(binary_buttons,three, sizeof(three)) == 0)
    send_keycode(XK_3);
  if(memcmp(binary_buttons,four, sizeof(four)) == 0)
    send_keycode(XK_4);
  if(memcmp(binary_buttons,five, sizeof(five)) == 0)
    send_keycode(XK_5);
  if(memcmp(binary_buttons,six, sizeof(six)) == 0)
    send_keycode(XK_6);
  if(memcmp(binary_buttons,seven, sizeof(seven)) == 0)
    send_keycode(XK_7);
  if(memcmp(binary_buttons,eight, sizeof(eight)) == 0)
    send_keycode(XK_8);
  if(memcmp(binary_buttons,nine, sizeof(nine)) == 0)
    send_keycode(XK_9);
  if(memcmp(binary_buttons,zero, sizeof(zero)) == 0)
    send_keycode(XK_0);
  if(memcmp(binary_buttons,equal, sizeof(equal)) == 0)
    send_keycode(XK_equal);
  if(memcmp(binary_buttons,less, sizeof(less)) == 0)
    send_keycode_modified(XK_Shift_L, XK_less);
  if(memcmp(binary_buttons,greater, sizeof(greater)) == 0)
    send_keycode_modified(XK_Shift_L, XK_greater);
}

int main(int argc, char *argv[]){
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
  {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Joystick *joystick;

  SDL_JoystickEventState(SDL_ENABLE);
  joystick = SDL_JoystickOpen(0);

  printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
  printf("The names of the joysticks are:\n");

  int i;
  for( i=0; i < SDL_NumJoysticks(); i++ )
  {
    printf("    %s\n", SDL_JoystickName(i));
  }

  printf("botaoes: %i\n", SDL_JoystickNumButtons(joystick));

  int buttons[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int history[100][16];
  //reset history
  for(int j=0;j<10;j++){
    for(int i=0;i<16;i++){
      history[j][i]=0;
    }
  }
  int counter=0;
  int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  while(1){
    SDL_JoystickUpdate();

    int pointer_mode=1;

    //initialize
    for (int i=0; i < 16; i++){
      buttons[i] = 0;
    }

    for ( int i=0; i < 12; i++ )
    {
      unsigned int n = SDL_JoystickGetButton ( joystick, i );
      if ( n != 0 )
        buttons[i] = 1;
    }

    signed short a1 = SDL_JoystickGetAxis ( joystick, 0 );
    signed short a2 = SDL_JoystickGetAxis ( joystick, 1 );
    if ( a1 != 0 ){
      if ( a1 < 0 ){
        buttons[12] = 1;
      } else {
        buttons[13] = 1;
      }
    }
    if ( a2 != 0 ){
      if ( a2 < 0 ){
        buttons[14] = 1;
      } else {
        buttons[15] = 1;
      }
    }

    if(pointer_mode != 1){
      SDL_Delay(40);
      //copy
      for(int i=0; i<16;i++){
        history[counter][i] = buttons[i];
      }

      if(pressed_key(buttons)){
      }else{
        //reset merged
        for (int i=0; i<16; i++){
          merged[i]=0;
        }

        //merge
        for(int j=0;j<100;j++){
          for(int i=0;i<16;i++){
            merged[i] = (history[j][i] || merged[i]);
          }
        }

        //reset history
        for(int j=0;j<100;j++){
          for(int i=0;i<16;i++){
            history[j][i]=0;
          }
        }
        send_key(merged);
      }

      if(counter>97){
        counter = 0;
        //reset history
        for(int j=0;j<100;j++){
          for(int i=0;i<16;i++){
            history[j][i]=0;
          }
        }
      }else{
        counter++;
      }
    } else{
      SDL_Delay(50);
      if(pressed_key(buttons)){
        int dest_x=0;
        int dest_y=0;
        int step=10;

        if(buttons[14])
          dest_y=-1;
        if(buttons[15])
          dest_y=1;
        if(buttons[12])
          dest_x=-1;
        if(buttons[13])
          dest_x=1;

        Display* display = XOpenDisplay(0);
        XWarpPointer(display, None, None, 0, 0, 0, 0, dest_x * step,dest_y * step);
        XFlush(display);
        XCloseDisplay(display);
      }
    }
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

