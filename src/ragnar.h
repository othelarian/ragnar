// ragnar.h

#ifndef RAGNAR_H
#define RAGNAR_H

// INCLUDES #####################################

#include <uv.h>
#include <xcb/xcb.h>
#include <xcb/randr.h>

// DEFINES ######################################

#define p_delete(mem_p)                \
  do {                                 \
    void **__ptr = (void **)(mem_p);   \
    free(*__ptr);                      \
    *(void **)__ptr = NULL;            \
  } while (0)

// RAGNAR SINGLETON #############################

class Ragnar {
  private:
  Ragnar();
  ~Ragnar();
  int                   init_event(void);
  bool                  init_screen(void);
  void                  loop(void);
  void                  update_screen(void);

  public:
  static Ragnar        *getInstance(void);
  int                   init(void);
  void                  quit(void);
  int                   run(void);

  private:
  xcb_screen_t         *_dft_screen;
  int                   _dft_screen_nbr;
  uint32_t              _dft_screen_height; // MAYBE WASTED
  uint32_t              _dft_screen_width; // MAYBE WASTED
  xcb_window_t          _dft_win_root; // MAYBE WASTED
  uv_poll_t            *_evt_handle;
  static Ragnar        *_uniq;
  int                   _value;
  xcb_connection_t     *_x_cnx;
  //
  //monitors
  //windows
  //
  //
};

#endif
