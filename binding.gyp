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
