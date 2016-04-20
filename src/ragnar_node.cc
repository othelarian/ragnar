// ragnar_node.cc

// INCLUDES #####################################

#include "ragnar.h"

using node::AtExit;
using v8::FunctionCallbackInfo;
using v8::Object;
using namespace std;

// GLOBAL VARIABLES #############################

Ragnar *Ragnar::_uniq = NULL;

static Ragnar *ragnarWM;

// NODE FUNCTIONS ###############################

void
Events(const FunctionCallbackInfo<Value> &args) {
  //
  cout << "set events manager ..." << endl;
  //
  ragnarWM->_evt_cb = Local<Function>::Cast(args[0]);
  //
}

void
Init(const FunctionCallbackInfo<Value> &args) {
  //Isolate* isolate = args.GetIsolate();
  int result;
  result = ragnarWM->init();
  if (result == 0) {
    //
    //
  }
  args.GetReturnValue().Set(result);
}

void
Start(const FunctionCallbackInfo<Value> &args) {
  //
  ragnarWM->run();
  //
}

// EXIT CALLBACK ################################

static void
at_exit_cb(void*) { ragnarWM->quit(); }

// INIT RAGNAR !! ###############################

void
init(Local<Object> exports) {
  ragnarWM = Ragnar::getInstance();
  //
  NODE_SET_METHOD(exports,"events",Events);
  //
  NODE_SET_METHOD(exports,"init",Init);
  //
  NODE_SET_METHOD(exports,"start",Start);
  //
  AtExit(at_exit_cb);
}

NODE_MODULE(ragnar,init)
