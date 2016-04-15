// ragnar.h

// INCLUDES #####################################

#include <xcb/xcb.h>
#include <xcb/xineram.h>
#include <xcb/randr.h>

// RAGNAR SINGLETON #############################

class Ragnar {
  private:
  Ragnar();
  ~Ragnar();
  bool                  screen_randr(void);
  void                  screen_x11(void);
  bool                  screen_xinerama(void);

  public:
  static Ragnar        *getInstance(void);
  int                   init();
  void                  quit();
  //
  //

  private:
  xcb_screen_t         *_dft_screen;
  int                   _dft_screen_nbr;
  uint32_t              _dft_screen_height; // MAYBE WASTED
  uint32_t              _dft_screen_width; // MAYBE WASTED
  xcb_window_t          _dft_win_root; // MAYBE WASTED
  static Ragnar        *_uniq;
  int                   _value;
  xcb_connection_t     *_x_cnx;
  //
  //monitors
  //windows
  //
  //
};

Ragnar *Ragnar::_uniq = NULL;
