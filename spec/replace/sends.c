#include "SDL.h"
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

void send_keycode(keysym){
  Display* display = XOpenDisplay(0);
  int val = XKeysymToKeycode(display, keysym);
  printf("%i\n", val);
  XCloseDisplay(display);
}

void send_keycode_modified(modifier, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode = XKeysymToKeycode(display, modifier);
  printf("%i-%i\n",modcode, keycode);
  XCloseDisplay(display);
}

void send_keycode_mod_mod(mod1,mod2, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode1 = XKeysymToKeycode(display, mod1);
  int modcode2 = XKeysymToKeycode(display, mod2);

  printf("%i-%i\n",modcode1,modcode2, keycode);
  XCloseDisplay(display);
}

