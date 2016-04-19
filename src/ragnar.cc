// ragnar.cc

// INCLUDES #####################################

#include <iostream>

#include "ragnar.h"

using namespace std;

// RAGNAR CLASS METHODS (PRIVATE) ###############

Ragnar::Ragnar() : _value(8) {}
Ragnar::~Ragnar() {}

// init_event - initialize all events listeners
int
Ragnar::init_event(void) {
  //
  _evt_handle = new uv_poll_t;
  //
  //
  return 0;
  //
}

// screen_randr - check the outputs / monitors
bool
Ragnar::init_screen(void) {
  //
  // awesome test
  //
  xcb_randr_get_screen_resources_cookie_t screen_res_c;
  xcb_randr_get_screen_resources_reply_t *screen_res_r;
  screen_res_c = xcb_randr_get_screen_resources(_x_cnx,_dft_screen->root);
  screen_res_r = xcb_randr_get_screen_resources_reply(_x_cnx,screen_res_c,NULL);
  //
  cout << "crtcs : " << screen_res_r->num_crtcs << endl;
  cout << "outputs : " << screen_res_r->num_outputs << endl;
  //
  xcb_randr_crtc_t *randr_crtcs = xcb_randr_get_screen_resources_crtcs(screen_res_r);
  for (int i=0; i < screen_res_r->num_crtcs; i++) {
    xcb_randr_get_crtc_info_cookie_t crtc_info_c;
    xcb_randr_get_crtc_info_reply_t *crtc_info_r;
    crtc_info_c = xcb_randr_get_crtc_info(_x_cnx,randr_crtcs[i],XCB_CURRENT_TIME);
    crtc_info_r = xcb_randr_get_crtc_info_reply(_x_cnx,crtc_info_c,NULL);
    //
    if (!xcb_randr_get_crtc_info_outputs_length(crtc_info_r)) continue;
    //
    // TODO : preparation of the geometry
    //
    //
    xcb_randr_output_t *randr_outputs = xcb_randr_get_crtc_info_outputs(crtc_info_r);
    //
    for (int j=0; j < xcb_randr_get_crtc_info_outputs_length(crtc_info_r); j++) {
      //
      cout << "coucou !" << endl;
      //
      xcb_randr_get_output_info_cookie_t output_info_c;
      xcb_randr_get_output_info_reply_t *output_info_r;
      //
      output_info_c = xcb_randr_get_output_info(_x_cnx,randr_outputs[j],XCB_CURRENT_TIME);
      output_info_r = xcb_randr_get_output_info_reply(_x_cnx,output_info_c,NULL);
      //
      //
      //
      p_delete(&output_info_r);
    }
    //
    // TODO : add the crtc to the list
    //
    p_delete(&crtc_info_r);
  }
  //
  return true;
  //
}

// loop - catch the X events !
void
Ragnar::loop(void) {
  //
  //
  //
  uv_poll_init(uv_default_loop(),_evt_handle,_dft_screen_nbr);
  //uv_poll_start(handle, UV_READABLE, EIO_Loop);
  //
}

// update_screen
void
Ragnar::update_screen(void) {
  //
  //
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
// return 1 : x_connect failed
// return 2 : randr not presentint
// return 3 : ??
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
  init_event();
  //
  if (!xcb_get_extension_data(_x_cnx,&xcb_randr_id)->present) return 2;
  if (!init_screen()) return 3;
  //
  cout << "x connexion initialized" << endl;
  //
  // TODO : EWMH
  // TODO : systray
  // TODO : spawn ?
  // TODO : xkb ?
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
  //
  cout << "Ragnar will be back ..." << endl;
  //
}

// loop - the event loop
// return 0 : OK
int
Ragnar::run(void) {
  //
  cout << "take the loop !" << endl;
  //
  //
  return 0;
  //
}
