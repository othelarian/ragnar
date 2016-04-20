// ragnar.h

#ifndef RAGNAR_H
#define RAGNAR_H

// INCLUDES #####################################

#include <iostream>
#include <node.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>

using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Value;
using v8::String;

// DEFINES ######################################

#define p_delete(mem_p)                \
  do {                                 \
    void **__ptr = (void **)(mem_p);   \
    free(*__ptr);                      \
    *(void **)__ptr = NULL;            \
  } while (0)

// SHARED FUNCTIONS #############################

// nothing

// RAGNAR SINGLETON #############################

class Ragnar {
  private:
  Ragnar();
  ~Ragnar();
  int                   init_event(void);
  bool                  init_screen(void);
  void                  update_screen(void);

  public:
  static Ragnar        *getInstance(void);
  int                   init(void);
  void                  quit(void);
  void                  run(void);

  public:
  Local<Function>       _evt_cb;

  private:
  xcb_screen_t         *_dft_screen;
  int                   _dft_screen_nbr;
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
