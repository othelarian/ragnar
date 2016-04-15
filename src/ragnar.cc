// ragnar.cc

// INCLUDES #####################################

#include "ragnar.h"

// RAGNAR CLASS METHODS (PRIVATE) ###############

Ragnar::Ragnar() : _value(0) {}
Ragnar::~Ragnar() {}

bool
Ragnar::screen_randr(void) {
  //
  //
  return false;
  //
}

void
screen_x11(void) {
  //
  //
  //
}

bool
screen_xinerama(void) {
  //
  //
  return false;
  //
}

// RAGNAR CLASS METHODS (PUBLIC) ################

Ragnar*
Ragnar::getInstance(void) {
  if (_uniq == NULL) { _uniq = new Ragnar; }
  return _uniq;
}

// init - called with the start
// return 0 : OK
// return 1 : error when trying to connect to X server
int
Ragnar::init(void) {
  // variables
  xcb_screen_iterator_t iter;
  // connection to X server
  _x_cnx = xcb_connect(NULL,&_dft_screen_nbr);
  if (xcb_connection_has_error(_x_cnx)) { return 1; }
  //
  // START TEST - informations about the screens
  cout << endl << "default screen_nbr : " << _dft_screen_nbr << endl;
  //
  iter = xcb_setup_roots_iterator(xcb_get_setup(_x_cnx));
  //
  int scrn_cnt = iter.rem;
  cout << endl << "screen count : " << scrn_cnt << endl;
  //
  int tmp_screen_nbr = _dft_screen_nbr;
  //
  xcb_screen_t *screen;
  for (;iter.rem;--tmp_screen_nbr,xcb_screen_next(&iter)) {
    if (tmp_screen_nbr == 0) {
      _dft_screen = iter.data;
      _dft_screen_height = _dft_screen->height_in_pixels;
      _dft_screen_width = _dft_screen->width_in_pixels;
      _dft_win_root = _dft_screen->root;
    }
    //
    screen = iter.data;
    cout << endl << "screen " << screen->root << endl;
    cout << "width : " << screen->width_in_pixels << endl;
    cout << "height : " << screen->height_in_pixels << endl;
    cout << endl;
  }
  // END TEST
  //
  // check for xrandr & xinerama, or basic x11
  //
  if (!screen_randr() && !screen_xinerama()) screen_x11();
  //
  //
  cout << "x connexion initialized" << endl;
  //
  //
  return 0;
  //
}

// quit - called by atExit
void
Ragnar::quit(void) {
  // disconnection to X server
  xcb_disconnect(_x_cnx);
}
