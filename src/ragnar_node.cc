// ragnar_node.cc

// INCLUDES #####################################

#include "ragnar.h"

// GLOBAL VARIABLES #############################

Ragnar *Ragnar::_uniq = NULL;

static Ragnar *ragnarWM;

// NODE FUNCTIONS ###############################
NAN_METHOD(Events) {
  //
  cout << "set events manager ..." << endl;
  //
  ragnarWM->_evt_cb = new Nan::Callback(info[0].As<Function>());
  //
  //ragnarWM->_evt_cb = Local<Function>::Cast(args[0]);
  //
  info.GetReturnValue().SetUndefined();
  //
}

NAN_METHOD(Init) {
  Nan::HandleScope scope;
  int result;
  result = ragnarWM->init();
  if (result == 0) {
    //
    //
  }
  info.GetReturnValue().Set(result);
}

NAN_METHOD(Start) {
  //
  ragnarWM->run();
  //
  info.GetReturnValue().SetUndefined();
}

// EXIT CALLBACK ################################

static void
at_exit_cb(void*) { ragnarWM->quit(); }

// INIT RAGNAR !! ###############################

//void
NAN_MODULE_INIT(init) {
  ragnarWM = Ragnar::getInstance();
  //
  //
  Nan::Set(target,Nan::New("events").ToLocalChecked(),Nan::New<FunctionTemplate>(Events)->GetFunction());
  //
  Nan::Set(target,Nan::New("init").ToLocalChecked(),Nan::New<FunctionTemplate>(Init)->GetFunction());
  //
  Nan::Set(target,Nan::New("start").ToLocalChecked(),Nan::New<FunctionTemplate>(Start)->GetFunction());
  //
  //
  AtExit(at_exit_cb);
}

NODE_MODULE(ragnar,init)
