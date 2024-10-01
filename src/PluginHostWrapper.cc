#include <iostream>
#include <napi.h>
#include <math.h>
#include "juce_core/juce_core.h"
#include "juce_audio_processors/juce_audio_processors.h"

class PluginHostWrapper : public Napi::ObjectWrap<PluginHostWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "PluginHostWrapper", {
				InstanceMethod ("helloInstance", &PluginHostWrapper::HelloInstance, napi_enumerable),
				InstanceMethod ("createVST3Instance", &PluginHostWrapper::CreateVST3Instance, napi_enumerable),
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

		void CreateVST3Instance (const Napi::CallbackInfo& info) {
			Napi::Env env = info.Env();

			if (info.Length() != 1) {
				Napi::TypeError::New (env, "Expected 1 argument").ThrowAsJavaScriptException();
				return;
			}

			if (!info[0].IsNumber()) {
				Napi::TypeError::New (env, "Expected 1st argument to be a string").ThrowAsJavaScriptException();
				return;
			}

			int index = static_cast<int>(info[0].As<Napi::Number>());

			juce::OwnedArray<juce::PluginDescription> descriptions;

			juce::VST3PluginFormat format;
			juce::StringArray foundPlugins = format.searchPathsForPlugins (juce::FileSearchPath("C:/Program Files/Common Files/VST3"), false, true);
			format.findAllTypesForFile (descriptions, foundPlugins[index]);

			juce::PluginDescription* description = descriptions[0];
			std::unique_ptr<juce::AudioPluginInstance> instance = format.createInstanceFromDescription (*description, 48000, 1024);

			std::cout << description->name << std::endl;
		}
};
