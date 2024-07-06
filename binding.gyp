{
	"targets": [
		{
			"target_name": "naph",
			"sources": [
				"src/Addon.cpp",
				"src/PluginHost.cpp",
				"src/PluginHostWrapper.cpp",
				"lib/thirdparty/JUCE/modules/juce_audio_basics/juce_audio_basics.cpp",
				"lib/thirdparty/JUCE/modules/juce_audio_processors/juce_audio_processors.cpp",
				"lib/thirdparty/JUCE/modules/juce_core/juce_core.cpp",
				"lib/thirdparty/JUCE/modules/juce_data_structures/juce_data_structures.cpp",
				"lib/thirdparty/JUCE/modules/juce_events/juce_events.cpp",
				"lib/thirdparty/JUCE/modules/juce_graphics/juce_graphics.cpp",
				"lib/thirdparty/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp",
				"lib/thirdparty/JUCE/modules/juce_gui_extra/juce_gui_extra.cpp",
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")",
				"lib/thirdparty/JUCE/modules",
				"lib/thirdparty/JUCE/modules/juce_audio_processors/format_types/VST3_SDK",
			],
			"libraries": [
				"../lib/thirdparty/JUCEStatic.lib",
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")",
			],
			"defines": [
				"NAPI_DISABLE_CPP_EXCEPTIONS",
				"DONT_SET_USING_JUCE_NAMESPACE",
				"JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED",
				"JUCE_PLUGINHOST_VST3",
				"JUCE_WINDOWS",
				"JUCE_STANDALONE_APPLICATION",
			],
			"cflags!": [
				"-fno-exceptions",
				"-fno-rtti",
			],
			"cflags_cc!": [
				"-fno-exceptions",
				"-fno-rtti",
			],
			"cflags": [
				"-fexceptions",
				"-frtti",
			],
			"cflags_cc": [
				"-fexceptions",
				"-frtti",
			],
			"msvs_settings": {
				"VCCLCompilerTool": {
					"AdditionalOptions": [
						"/GR", # Enable RTTI
						"/EHsc" # Enable C++ Exceptions
					] # Force for MSVC
				}
			}
		},
	],
}
