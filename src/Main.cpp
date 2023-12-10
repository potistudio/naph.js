
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED true
#define DONT_SET_USING_JUCE_NAMESPACE true

#include <iostream> // For Debuging

#include <napi.h>
#include <chrono>
#include <thread>

#include "juce_core/juce_core.h"
#include "juce_gui_basics/juce_gui_basics.h"

/* Callback Async Worker */
class PromiseWorker : public Napi::AsyncWorker {
	public:
		PromiseWorker (Napi::Env env, Napi::Function callback) : Napi::AsyncWorker (callback), sum(0) {}

	protected:
		void Execute() override {
			sum = 1 + 1;
		}

		void OnOK() override {
			Napi::Env env = Env();

			Callback().MakeCallback (
				Receiver().Value(),
				{
					Napi::Number::New (env, sum)
				}
			);
		}

	private:
		int sum;
};

class AlertWindowWorker : public Napi::AsyncWorker {
	public:
		AlertWindowWorker (Napi::Env env, Napi::Function callback) : Napi::AsyncWorker (env), tsfn(Napi::ThreadSafeFunction::New(env, callback, "AlertWindowWorker", 0, 1)) {}
		virtual ~AlertWindowWorker() override { tsfn.Release(); }

	protected:
		void Execute() override {
			//TODO: to Threadsafe Function
			// BlockingCall -> Juce Async Callback -> Call js
			tsfn.BlockingCall ([](Napi::Env env, Napi::Function js_callback){
				js_callback.Call ({ Napi::String::New(env, "AAA") });
			});
			// juce::AlertWindow::showMessageBoxAsync (juce::MessageBoxIconType::InfoIcon, "Hello World!", "Congratulations!!!This Window is Called from Node.js", "OK", nullptr, juce::ModalCallbackFunction::create([](int result) {
			// }));
		}

	private:
		Napi::ThreadSafeFunction tsfn;
};

/* Wrapper */
class PluginHostWrapper : public Napi::ObjectWrap<PluginHostWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "PluginHostWrapper", {
				InstanceMethod ("helloInstance", &PluginHostWrapper::HelloInstance, napi_enumerable),
				InstanceMethod ("showAlert", &PluginHostWrapper::ShowAlert, napi_enumerable),
				InstanceMethod ("asyncCallback", &PluginHostWrapper::AsyncCallback, napi_enumerable),
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

			juce::String text = juce::String();
			std::cout << "Hello from Constructor!" << std::endl;
		}

		static Napi::Value HelloStatic (const Napi::CallbackInfo& info) {
			return Napi::String::New (info.Env(), "Hello from Static Method!");
		}

		Napi::Value HelloInstance (const Napi::CallbackInfo& info) {
			return Napi::String::New (info.Env(), "Hello from Instance Method!");
		}

		void ShowAlert (const Napi::CallbackInfo& info) {
			Napi::Env env = info.Env();
			Napi::Function callback = info[0].As<Napi::Function>();

			AlertWindowWorker* worker = new AlertWindowWorker (env, callback);
			worker -> Queue();
			return;
		}

		void AsyncCallback (const Napi::CallbackInfo& info) {
			Napi::Env env = info.Env();

			Napi::Function callback = info[0].As<Napi::Function>();

			PromiseWorker* worker = new PromiseWorker (env, callback);
			worker -> Queue();
			return;
		}
};

/* Exporter */
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
