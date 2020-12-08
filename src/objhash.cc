#include <nan.h>
#include <node.h>
#include <v8.h>

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    info.GetReturnValue().Set(Nan::Undefined());
  } else if (info[0]->IsObject()) {
    v8::Local<v8::Object> object;
    if (info[0]->ToObject(info.GetIsolate()->GetCurrentContext()).ToLocal(&object)) {
      int hash = object->GetIdentityHash();
      info.GetReturnValue().Set(Nan::New(hash));
    } else {
      info.GetReturnValue().Set(Nan::Undefined());
    }
  } else {
    info.GetReturnValue().Set(info[0]);
  }
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New<v8::String>("objhash").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Method)).ToLocalChecked());
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
