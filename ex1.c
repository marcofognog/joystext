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
  int space[16] = {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0};
  int enter[16] = {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
  int backspace[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};

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
    SDL_Delay(40);
    SDL_JoystickUpdate();


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
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

