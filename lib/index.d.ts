
export function hello(): string;

export class PluginHost {
	constructor();

	helloInstance(): string;
	showAlert (callback: () => void): void;

	static helloStatic(): string;
}