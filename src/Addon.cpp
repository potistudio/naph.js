#include <napi.h>
#include "PluginHostWrapper.cpp"

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
