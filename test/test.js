
const naph = require ("..");

console.log (naph.hello()); // "Hello World!"
console.log (naph.PluginHost.helloStatic()); // "Hello from Static Method!"
const host = new naph.PluginHost(); // "Hello from Constructor!"
console.log (host.helloInstance()); // "Hello from Instance Method!"

!function main() {
	// host.showAlert ((a) => {
	// 	console.log("Callback", a);
	// });
	host.asyncCallback ((a) => {
		console.log("Callback", a);
	})
}();
