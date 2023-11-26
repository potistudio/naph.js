{
	"targets": [{
		"target_name": "naph",
		"sources": [
			"src/Main.cpp"
		],
		'include_dirs': [
			"<!@(node -p \"require('node-addon-api').include\")"
		],
		'libraries': [],
		'dependencies': [
			"<!(node -p \"require('node-addon-api').gyp\")"
		],
		'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
		"cflags!": [ "-fno-exceptions" ],
		"cflags_cc!": [ "-fno-exceptions" ]
	}]
}