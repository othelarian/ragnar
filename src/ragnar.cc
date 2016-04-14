// ragnar.cc

// INCLUDES #####################################

// NODE INCLUDES ############
#include <node.h>
// GCC INCLUDES #############
#include <iostream>
// X INCLUDES ###############
// APP INCLUDES #############
#include "ragnar.h"

using node::AtExit;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using namespace std;

// RAGNAR CLASS METHODS #########################

Ragnar::Ragnar() : _value(0) {}
Ragnar::~Ragnar() {}

Ragnar *Ragnar::getInstance(void) {
  if (_uniq == NULL) { _uniq = new Ragnar; }
  return _uniq;
}

int Ragnar::init(void) {
  //
  //_x_cnx = xcb_connect(NULL,NULL);
  //
  xcb_screen_t *screen;
  int screen_nbr;
  xcb_screen_iterator_t iter;
  //
  _x_cnx = xcb_connect(NULL,&screen_nbr);
  if (xcb_connection_has_error(_x_cnx)) { return 1; }
  //
  cout << endl << "screen_nbr : " << screen_nbr << endl;
  //
  int scrn_cnt = xcb_setup_roots_iterator(xcb_get_setup(_x_cnx)).rem;
  cout << endl << "screen count : " << scrn_cnt << endl;
  //
  iter = xcb_setup_roots_iterator(xcb_get_setup(_x_cnx));
  for (;iter.rem;--screen_nbr,xcb_screen_next(&iter)) {
    //
    screen = iter.data;
    //
    cout << endl << "screen " << screen->root << endl;
    cout << "width : " << screen->width_in_pixels << endl;
    cout << "height : " << screen->height_in_pixels << endl;
    cout << endl;
    //
  }
  //
  //
  cout << "x connexion initialized" << endl;
  //
  //
  return 0;
  //
}

void Ragnar::quit(void) {
  //
  xcb_disconnect(_x_cnx);
}

static Ragnar *ragnarWM;


// NODE FUNCTIONS ###############################

void Start(const FunctionCallbackInfo<Value>& args) {
  //
  int result;
  //
  result = ragnarWM->init();
  //
  //
  Isolate* isolate = args.GetIsolate();
  //args.GetReturnValue().Set(String::NewFromUtf8(isolate,result));
  args.GetReturnValue().Set(result);
  //
}

// EXIT CALLBACK ################################

static void at_exit_cb(void*) {
  //
  ragnarWM->quit();
  //
  cout << "Ragnar will be back ..." << endl;
}

// INIT RAGNAR !! ###############################

void init(Local<Object> exports) {
  //
  ragnarWM = Ragnar::getInstance();
  //
  NODE_SET_METHOD(exports,"start",Start);
  //
  //
  AtExit(at_exit_cb);
}

NODE_MODULE(ragnar,init)
