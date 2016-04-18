// ragnar_node.cc

// INCLUDES #####################################

// NODE INCLUDES ############
#include <node.h>
#include <uv.h>
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

// GLOBAL VARIABLES #############################

Ragnar *Ragnar::_uniq = NULL;

static Ragnar *ragnarWM;

// NODE FUNCTIONS ###############################

void
Start(const FunctionCallbackInfo<Value>& args) {
  int result;
  result = ragnarWM->init();
  //
  //test
  // see for libuv to the event loop
  uv_poll_t *handle;
  //test
  //
  // initiate loop
  if (result == 0) result = ragnarWM->run();
  //
  //
  Isolate* isolate = args.GetIsolate();
  //args.GetReturnValue().Set(String::NewFromUtf8(isolate,result));
  args.GetReturnValue().Set(result);
  //
}

// EXIT CALLBACK ################################

static void
at_exit_cb(void*) {
  //
  ragnarWM->quit();
  //
  cout << "Ragnar will be back ..." << endl;
}

// INIT RAGNAR !! ###############################

void
init(Local<Object> exports) {
  ragnarWM = Ragnar::getInstance();
  //
  NODE_SET_METHOD(exports,"start",Start);
  //
  //
  AtExit(at_exit_cb);
}

NODE_MODULE(ragnar,init)
