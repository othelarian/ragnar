// ragnar.h

// INCLUDES #####################################

#include <xcb/xcb.h>

// RAGNAR SINGLETON #############################

class Ragnar {
  private:
  Ragnar();
  ~Ragnar();
  public:
  static Ragnar *getInstance(void);
  int init();
  void quit();
  //
  //

  private:
  int _value;
  static Ragnar *_uniq;
  xcb_connection_t *_x_cnx;
  //
  //monitors
  //windows
  //
  //
};
Ragnar *Ragnar::_uniq = NULL;
