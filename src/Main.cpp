
#include <iostream>
#include <napi.h>

class PluginHostWrapper : public Napi::ObjectWrap<PluginHostWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "PluginHostWrapper", {
				InstanceMethod ("helloInstance", &PluginHostWrapper::HelloInstance, napi_enumerable),
				StaticMethod ("helloStatic", &PluginHostWrapper::HelloStatic, napi_enumerable)
			});
			Napi::FunctionReference *constructor = new Napi::FunctionReference();
			*constructor = Napi::Persistent (func);

			env.SetInstanceData<Napi::FunctionReference>(constructor);
			exports.Set ("PluginHost", func);

			return exports;
		}

		PluginHostWrapper (const Napi::CallbackInfo& info) : Napi::ObjectWrap<PluginHostWrapper>(info) {
			Napi::Env env = info.Env();

			if (info.Length() > 0) {
				Napi::TypeError::New (env, "Expected no arguments").ThrowAsJavaScriptException();
				return;
			}

			std::cout << "Hello from Constructor!" << std::endl;
		}

		static Napi::Value HelloStatic (const Napi::CallbackInfo& info) {
			return Napi::String::New (info.Env(), "Hello from Static Method!");
		}

		Napi::Value HelloInstance (const Napi::CallbackInfo& info) {
			return Napi::String::New (info.Env(), "Hello from Instance Method!");
		}
};

class Naph : public Napi::Addon<Naph> {
	public:
		Naph (Napi::Env env, Napi::Object exports) {
			DefineAddon (exports, {
				InstanceMethod ("hello", &Naph::Hello, napi_enumerable)
			});

			PluginHostWrapper::Init (env, exports);
		}

	private:
		Napi::Value Hello (const Napi::CallbackInfo& info) {
			return Napi::String::New (info.Env(), "Hello World!");
		}
};

NODE_API_ADDON (Naph);
