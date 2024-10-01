export function hello(): string;

export class PluginHost {
	constructor();

	helloInstance(): string;
	showAlert (callback: () => void): void;
	createVST3Instance (index: number): void;
	asyncCallback (callback: (sum: number) => void): void;

	static helloStatic(): string;
}
