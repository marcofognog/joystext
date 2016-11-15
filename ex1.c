#include <stdio.h>
#include <unistd.h>
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

void send_keycode_mod_mod(mod1,mod2, keysym){
  Display* display = XOpenDisplay(0);
  int keycode = XKeysymToKeycode(display, keysym);
  int modcode1 = XKeysymToKeycode(display, mod1);
  int modcode2 = XKeysymToKeycode(display, mod2);

  XTestFakeKeyEvent(display,modcode1,1,0);
  XTestFakeKeyEvent(display,modcode2,1,0);
  XTestFakeKeyEvent(display,keycode,1,0);
  XTestFakeKeyEvent(display,keycode,0,0);
  XTestFakeKeyEvent(display,modcode1,0,0);
  XTestFakeKeyEvent(display,modcode2,0,0);
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
  int left_parenthesis[16] = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int right_parenthesis[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int right_square_bracket[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0};
  int left_square_bracket[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0};
  int left_curly_bracket[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int right_curly_bracket[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int exclamation[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0};
  int at[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0};
  int sharp[16] = {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int dollar[16] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int percent[16] = {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1};
  int single_quote[16] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1};
  int pipe[16] = {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int asterisk[16] = {0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
  int underscore[16] = {0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0};
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
  int tab[16] = {0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1};

  int super_b[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0};
  int super_right_arrow[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0};
  int super_shift_q[16] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1};
  int super_left_arrow[16] = {0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0};
  int super_d[16] = {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
  int super_ctrl_right_arrow[16] = {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
  int super_enter[16] = {0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0};
  int super_ctrl_left_arrow[16] = {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0};
  int ctrl_w[16] = {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0};
  int ctrl_t[16] = {0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0};
  int ctrl_shift_t[16] = {0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0};
  int ctrl_c[16] = {0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0};
  int ctrl_z[16] = {1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0};
  int ctrl_d[16] = {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0};
  int ctrl_tab[16] = {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1};
  int ctrl_shift_tab[16] = {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1};

  int double_quote2[16] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};
  int single_quote2[16] = {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0};

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
    send_keycode(XK_Home);
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
  if(memcmp(binary_buttons,tab, sizeof(tab)) == 0)
    send_keycode(XK_Tab);

  //custom
  if(memcmp(binary_buttons,ctrl_w, sizeof(ctrl_w)) == 0)
    send_keycode_modified(XK_Control_L, XK_w);
  if(memcmp(binary_buttons,super_right_arrow, sizeof(super_right_arrow)) == 0)
    send_keycode_modified(XK_Super_L, XK_Right);
  if(memcmp(binary_buttons,super_left_arrow, sizeof(super_left_arrow)) == 0)
    send_keycode_modified(XK_Super_L, XK_Left);
  if(memcmp(binary_buttons,super_d, sizeof(super_d)) == 0)
    send_keycode_modified(XK_Super_L, XK_d);
  if(memcmp(binary_buttons,super_enter, sizeof(super_enter)) == 0)
    send_keycode_modified(XK_Super_L, XK_Return);
  if(memcmp(binary_buttons,super_shift_q, sizeof(super_shift_q)) == 0)
    send_keycode_mod_mod(XK_Super_L, XK_Shift_L, XK_q);
  if(memcmp(binary_buttons,super_ctrl_right_arrow, sizeof(super_ctrl_right_arrow)) == 0)
    send_keycode_mod_mod(XK_Super_L, XK_Control_L, XK_Right);
  if(memcmp(binary_buttons,super_ctrl_left_arrow, sizeof(super_ctrl_left_arrow)) == 0)
    send_keycode_mod_mod(XK_Super_L, XK_Control_L, XK_Left);
  if(memcmp(binary_buttons,ctrl_t, sizeof(ctrl_t)) == 0)
    send_keycode_modified(XK_Control_L, XK_t);
  if(memcmp(binary_buttons,ctrl_shift_t, sizeof(ctrl_shift_t)) == 0)
    send_keycode_mod_mod(XK_Control_L, XK_Shift_L, XK_t);
  if(memcmp(binary_buttons,ctrl_c, sizeof(ctrl_c)) == 0)
    send_keycode_modified(XK_Control_L, XK_c);
  if(memcmp(binary_buttons,ctrl_z, sizeof(ctrl_z)) == 0)
    send_keycode_modified(XK_Control_L, XK_z);
  if(memcmp(binary_buttons,ctrl_tab, sizeof(ctrl_tab)) == 0)
    send_keycode_modified(XK_Control_L, XK_Tab);
  if(memcmp(binary_buttons,ctrl_shift_tab, sizeof(ctrl_shift_tab)) == 0)
    send_keycode_mod_mod(XK_Control_L, XK_Shift_L, XK_Tab);
  if(memcmp(binary_buttons,super_b, sizeof(super_b)) == 0)
    send_keycode_modified(XK_Super_L, XK_b);
  if(memcmp(binary_buttons,ctrl_d, sizeof(ctrl_d)) == 0)
    send_keycode_modified(XK_Control_L, XK_d);
  if(memcmp(binary_buttons,single_quote2, sizeof(single_quote2)) == 0)
    send_keycode(XK_quotedbl);
  if(memcmp(binary_buttons,double_quote2, sizeof(double_quote2)) == 0)
    send_keycode_modified(XK_Shift_L,XK_quotedbl);
}

void check_for_pointer_events(int *binary_buttons){
  if(pressed_key(binary_buttons)){
    int dest_x=0;
    int dest_y=0;
    int step=1;

    if(binary_buttons[14])
      dest_y=-1;
    if(binary_buttons[15])
      dest_y=1;
    if(binary_buttons[12])
      dest_x=-1;
    if(binary_buttons[13])
      dest_x=1;

    int speed1[16]={1,0,0,0};
    int speed2[16]={1,1,0,0};
    int speed3[16]={0,1,0,0};
    int speed4[16]={0,1,1,0};
    int speed5[16]={0,0,1,0};
    int speed6[16]={0,0,1,1};
    int speed7[16]={0,0,0,1};
    int speed8[16]={1,0,0,1};
    int segment[4]={0,0,0,0};

    for(int i=0; i<4;i++){
      segment[i] = binary_buttons[i];
    }

    if(memcmp(segment,speed1, sizeof(segment)) == 0)
      step = 10;
    if(memcmp(segment,speed2, sizeof(segment)) == 0)
      step = 20;
    if(memcmp(segment,speed3, sizeof(segment)) == 0)
      step = 30;
    if(memcmp(segment,speed4, sizeof(segment)) == 0)
      step = 40;
    if(memcmp(segment,speed5, sizeof(segment)) == 0)
      step = 55;
    if(memcmp(segment,speed6, sizeof(segment)) == 0)
      step = 65;
    if(memcmp(segment,speed7, sizeof(segment)) == 0)
      step = 75;
    if(memcmp(segment,speed8, sizeof(segment)) == 0)
      step = 85;

    Display* display = XOpenDisplay(0);
    XWarpPointer(display, None, None, 0, 0, 0, 0, dest_x * step,dest_y * step);

    if(binary_buttons[4]){
      XTestFakeButtonEvent(display, 1, 1, 0);
      XTestFakeButtonEvent(display, 1, 0, 0);
      usleep(200000);
    }
    if(binary_buttons[5]){
      XTestFakeButtonEvent(display, 3, 1, 0);
      XTestFakeButtonEvent(display, 3, 0, 0);
      usleep(200000);
    }

    XFlush(display);
    XCloseDisplay(display);
  }
}

void check_for_text_events(int *bin_buttons, int bin_history[100][16], int *bin_merged, int *counter_p){
  for(int i=0; i<16;i++){
    bin_history[*counter_p][i] = bin_buttons[i];
  }

  if(pressed_key(bin_buttons)){
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
    send_key(bin_merged);
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
  int pointer_mode_history[100];
  int text_mode_history[100];
  int mode_counter = 0;

  //reset history
  for(int j=0;j<10;j++){
    for(int i=0;i<16;i++){
      history[j][i]=0;
    }
  }
  int counter=0;
  int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  int pointer_mode=0;
  int start_button = 9;
  int select_button = 8;

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

    if(pointer_mode != 1){
      check_for_text_events(buttons,history,merged, &counter);
    }else{
      check_for_pointer_events(buttons);
    }

    pointer_mode_history[mode_counter] = buttons[start_button];
    text_mode_history[mode_counter] = buttons[select_button];
    if(pressed_key(buttons)){
    }else{
      mode_counter = 0;
      int released_start = 0;
      int released_select = 0;
      for(int j=0;j<100;j++){
        released_start = (pointer_mode_history[j] || released_start);
      }
      for(int j=0;j<100;j++){
        released_select = (text_mode_history[j] || released_select);
      }

      if(released_select){
        pointer_mode=0;
        printf("Pointer mode disabled.\n");
      }
      if(released_start){
        pointer_mode=1;
        printf("Pointer mode enabled.\n");
      }
      for(int j=0;j<100;j++){
        pointer_mode_history[j]=0;
      }
      for(int j=0;j<100;j++){
        text_mode_history[j]=0;
      }
    }

    if(mode_counter>97){
      mode_counter = 0;
      for(int j=0;j<100;j++){
        pointer_mode_history[j]=0;
      }
      for(int j=0;j<100;j++){
        text_mode_history[j]=0;
      }
    }else{
      mode_counter++;
    }
  }

  SDL_Quit();
  puts("quit sdl");

  return 0;
}

