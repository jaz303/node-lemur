#include <v8.h>
#include <node.h>
#include <iostream>


#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  return scope.Close(String::New("world"));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "hello", Method);
}

NODE_MODULE(binding, init);


// #define UNWRAP(thing) node::ObjectWrap::Unwrap<Lemur>(thing)
// #define UNWRAP_AS(name, thing) Lemur *name = UNWRAP(thing)
// 
// using namespace v8;

// class Lemur : node::ObjectWrap
// {
// private:
//     std::string title;
//     
// public:
//     Lemur() {}
//     ~Lemur() {}
//     
//     static void Init(Handle<Object> target) {
//         v8::HandleScope scope;
//         
//         v8::Local<FunctionTemplate> local_function_template = v8::FunctionTemplate::New(New);
//         Lemur::tpl = v8::Persistent<FunctionTemplate>::New(local_function_template);
//         Lemur::tpl->InstanceTemplate()->SetInternalFieldCount(1);
//         Lemur::tpl->SetClassName(v8::String::NewSymbol("Lemur"));
//         
//         Lemur::tpl->SetAccessor(String::New("title"), GetTitle, SetTitle);
//         
//         NODE_SET_PROTOTYPE_METHOD(Lemur::tpl, "foo", Foo);
//         
//         target->Set(String::NewSymbol("Lemur"), Lemur::tpl->GetFunction());
//     }
//     
//     static Handle<Value> New(const Arguments& args) {
//         HandleScope scope;
//         
//         Lemur *instance = new Lemur();
//         lemur->title = "Lemur!";
//         
//         instance->Wrap(args.This());
//         
//         return args.This();
//     }
//     
//     static Handle<Value> Foo(const Arguments& args) {
//         HandleScope scope;
//         
//         UNWRAP_AS(lemur, args.This());
//         v8::String::Utf8Value v8str(args[0]);
//         std::cout << v8str << ":" << lemur->title << std::endl;
//         
//         return v8::Boolean::New(true);
//     }
//     
//     static Handle<Value> GetTitle(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
//         UNWRAP_AS(lemur, info.Holder());
//         return v8::String::New(lemur->title.c_str());
//     }
//     
//     static Handle<Value> SetTitle(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo &info) {
//         UNWRAP_AS(lemur, info.Holder());
//         v8::String::Utf8Value v8str(value);
//         lemur->title = *v8str;
//     }
// };
// 
// v8::Persistent<FunctionTemplate> Lemur::tpl;
// extern "C" {
//     static void init(Handle<Object> target) {
//         Lemur::init(target);
//     }
//     NODE_MODULE(lemur, init);
// }