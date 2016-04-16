// ragnar.cc

// INCLUDES #####################################

#include <iostream>

#include "ragnar.h"

using namespace std;

// RAGNAR CLASS METHODS (PRIVATE) ###############

Ragnar::Ragnar() : _value(8) {}
Ragnar::~Ragnar() {}

bool
Ragnar::screen_randr(void) {
  //awesome screen_scan_randr_monitors
  //
  // awesome code, don't work
  //xcb_randr_get_monitors_cookie_t monitors_c = xcb_randr_get_monitors(_x_cnx,_dft_screen->root,1);
  //xcb_randr_get_monitors_reply_t *monitors_r = xcb_randr_get_monitors_reply(_x_cnx,monitors_c,NULL);
  //xcb_randr_monitor_info_iterator_t monitor_iter;
  //
  //awesome screen_update_primary
  //
  //
  // i3 randr
  //
  xcb_randr_get_output_primary_cookie_t pcookie;
  xcb_randr_get_screen_resources_current_cookie_t rcookie;
  //
  pcookie = xcb_randr_get_output_primary(_x_cnx,_dft_screen->root);
  rcookie = xcb_randr_get_screen_resources_current(_x_cnx,_dft_screen->root);
  //
  xcb_randr_get_output_primary_reply_t *primary;
  //
  if ((primary = xcb_randr_get_output_primary_reply(_x_cnx,pcookie,NULL)) == NULL) return false;
  //
  //
  //
  return true;
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
  iter = xcb_setup_roots_iterator(xcb_get_setup(_x_cnx));
  //
  int scrn_cnt = iter.rem;
  //
  int tmp_screen_nbr = _dft_screen_nbr;
  //
  for (;iter.rem;--tmp_screen_nbr,xcb_screen_next(&iter)) {
    if (tmp_screen_nbr == 0) {
      _dft_screen = iter.data;
      //
      _dft_screen_height = _dft_screen->height_in_pixels;
      _dft_screen_width = _dft_screen->width_in_pixels;
      _dft_win_root = _dft_screen->root;
      //
      //screen->root_depth
      //screen->default__colormap;
      //
    }
  }
  //
  if (xcb_get_extension_data(_x_cnx,&xcb_randr_id)->present) {
    //
    cout << "randr not present" << endl;
    //
    return 2;
  }
  if (!screen_randr()) return 3;
  //
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
