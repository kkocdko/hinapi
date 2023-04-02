#define NODE_ADDON_API_DISABLE_DEPRECATED
#include <napi.h>

#include <chrono>
#include <iostream>
#include <thread>

Napi::Value CalcAdd(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);
  return num;
}

void RunCallback(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  cb.Call(env.Global(), {Napi::String::New(env, "hello world")});
}

Napi::Value CreateObject(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  obj.Set(Napi::String::New(env, "name"), info[0].ToString());
  obj.Set(Napi::String::New(env, "age"), info[0].As<Napi::Number>());
  return obj;
}

class HiWorker : public Napi::AsyncWorker {
  Napi::Promise::Deferred deferred;

public:
  HiWorker(Napi::Env env, Napi::Promise::Deferred deferred)
      : AsyncWorker(env), deferred(deferred) {}
  void Execute() override {
    // simulate cpu heavy task
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  void OnOK() override {
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), 1.2));
  }
};

Napi::Value HiPromise(const Napi::CallbackInfo &info) {
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  Napi::Promise ret = deferred.Promise();
  HiWorker *wk = new HiWorker(info.Env(), deferred);
  wk->Queue();
  return ret;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "calcAdd"),
              Napi::Function::New(env, CalcAdd));
  exports.Set(Napi::String::New(env, "runCallback"),
              Napi::Function::New(env, RunCallback));
  exports.Set(Napi::String::New(env, "createObject"),
              Napi::Function::New(env, CreateObject));
  exports.Set(Napi::String::New(env, "hiPromise"),
              Napi::Function::New(env, HiPromise));
  return exports;
}

NODE_API_MODULE(addon, Init)
