{
	"targets": [
		{
			"target_name": "naph",
			"sources": [
				"src/Main.cpp",
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")",
				"lib/thirdparty/JUCE/modules"
			],
			"libraries": [
				"../lib/thirdparty/JUCEStatic.lib",
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")",
			],
			"defines": [
				"NAPI_DISABLE_CPP_EXCEPTIONS",
				"JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED",
				"DONT_SET_USING_JUCE_NAMESPACE",
				"JUCE_PLUGINHOST_VST",
				"JUCE_PLUGINHOST_VST3",
				"JUCE_PLUGINHOST_AU",
				"JUCE_PLUGINHOST_LADSPA",
				"JUCE_PLUGINHOST_LV2",
				"JUCE_PLUGINHOST_ARA",
				"JUCE_WINDOWS",
				"JUCE_STANDALONE_APPLICATION",
			],
			"cflags!": [
				"-fno-exceptions",
			],
			"cflags_cc!": [
				"-fno-exceptions",
			],
		},
	],
}
