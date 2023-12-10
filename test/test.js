
const naph = require ("..");

console.log (naph.hello()); // "Hello World!"
console.log (naph.PluginHost.helloStatic()); // "Hello from Static Method!"
const host = new naph.PluginHost(); // "Hello from Constructor!"
console.log (host.helloInstance()); // "Hello from Instance Method!"

!async function main() {
	host.showAlert (() => {
		console.log("Main");
	});
}();
