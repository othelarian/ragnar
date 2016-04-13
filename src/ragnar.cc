//ragnar.cc

// INCLUDES #####################################

// NODE INCLUDES ############
#include <node.h>
// GCC INCLUDES #############
#include <iostream>
#include <cassert>
// X INCLUDES ###############
// APP INCLUDES #############

// USINGS #######################################

// NODE USINGS ##############
using node::AtExit;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
// GCC USINGS ###############
using namespace std;

// FUNCTIONS ####################################

// EXIT CALLBACK ############
static void at_exit_cb(void*) {
  cout << "Ragnar will be back ..." << endl;
}




//class


void Method(const FunctionCallbackInfo<Value>& args) {
  //
  cout << "test 123" << endl;
  //
  Isolate* isolate = args.GetIsolate();
  //
  args.GetReturnValue().Set(String::NewFromUtf8(isolate,"world"));
  //
}



// INIT RAGNAR !! ###############################

void init(Local<Object> exports) {
  //
  NODE_SET_METHOD(exports,"hello",Method);
  //
  //
  AtExit(at_exit_cb);
}

NODE_MODULE(ragnar,init)
