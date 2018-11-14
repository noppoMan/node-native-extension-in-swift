#include <iostream>
#include <cstdlib>
#include <nan.h>
#include <dlfcn.h>

using std::cerr;
using std::endl;
using std::string;

#ifdef __APPLE__
#define IS_SUPPORTED_PLATFORM true
const string SHARED_LIBRARY_EXT = "dylib";
#endif

#ifdef __linux__
#define IS_SUPPORTED_PLATFORM true
const string SHARED_LIBRARY_EXT = "so";
#endif

#if !defined IS_SUPPORTED_PLATFORM
  cerr << "Unsupported Platform";
  exit(EXIT_FAILURE);
#endif

const string SWIFT_SHARED_LIBRARY_PATH = "./NativeExtensionInSwift/.build/debug/libNativeExtensionInSwift."+SHARED_LIBRARY_EXT;

const auto SWIFT_FIBONACCI_FUNC_SYMBOL = "swift_fibonacci";
const auto SWIFT_PRINT_HELLO_FUNC_SYMBOL = "swift_print_hello";

typedef int (*FibonacciFunc)(int);
typedef void (*PrintHelloFunc)();

void *DLSymOrDie(void *lib, const string& func_name) {
  const auto func = dlsym(lib, func_name.c_str());
  const auto dlsym_error = dlerror();
  if (dlsym_error) {
    cerr << "Could not load symbol create: " << dlsym_error << endl;
    dlclose(lib);
    exit(EXIT_FAILURE);
  }
  return func;
}

void *DLOpenOrDie(const string& path) {
  const auto lib = dlopen(path.c_str(), RTLD_LAZY);
  if (!lib) {
    cerr << "Could not load library: " << dlerror() << endl;
    exit(EXIT_FAILURE);
  }
  return lib;
}

void Fibonacci(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Argument should be a number");
    return;
  }

  const auto swiftLib = DLOpenOrDie(SWIFT_SHARED_LIBRARY_PATH);
  const auto _Fibonacci = (FibonacciFunc)DLSymOrDie(swiftLib, SWIFT_FIBONACCI_FUNC_SYMBOL);

  double arg0 = info[0]->NumberValue();
  const auto n = _Fibonacci(arg0);
  info.GetReturnValue().Set(n);
}

void PrintHello(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  const auto swiftLib = DLOpenOrDie(SWIFT_SHARED_LIBRARY_PATH);
  const auto _PrintHello = (PrintHelloFunc)DLSymOrDie(swiftLib, SWIFT_PRINT_HELLO_FUNC_SYMBOL);
  _PrintHello();
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("fibonacci").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Fibonacci)->GetFunction());

  exports->Set(Nan::New("printHello").ToLocalChecked(),
              Nan::New<v8::FunctionTemplate>(PrintHello)->GetFunction());
}

NODE_MODULE(addon, Init)
