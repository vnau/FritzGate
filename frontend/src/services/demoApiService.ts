import { Status, type ApiService, type SensorStatus, type StatusData } from "../interfaces";

export class DemoApiService implements ApiService {
    private statusPromise: Promise<StatusData> = undefined!;
    private sensors: SensorStatus[] = [];
    private url!: string;

    constructor(baseUrl: string) {
        this.url = baseUrl + "/status.json";
    }

    async ensureStatusLoaded(): Promise<StatusData> {
        if (!this.statusPromise) {
            this.statusPromise = fetch(this.url).then(resp => resp.json());
            var data = await this.statusPromise;
            data.fritz = { host: 'fritzbox', user: 'user', status: Status.unconfigured };
            for (const sensor of data.sensors) {
                setTimeout(() => this.sensors.push(sensor), Math.random() * 8000);
            }

            return data;
        } else {
            return await this.statusPromise;
        }
    }

    async fetchStatus(): Promise<StatusData | undefined> {
        var status = await this.ensureStatusLoaded();
        const res = {
            fritz: status.fritz,
            sensors: this.sensors.map(v => ({
                ...v,
                temperature: v.temperature + Math.random() / 5,
                humidity: v.humidity + Math.random(),
                rssi: v.rssi + Math.random() * 5
            })),
            thermostats: status.fritz.status === Status.connected
                ? status.thermostats//.map(v => ({ ...v }))
                : [],
        };
        return res;
    }

    async setBinding(device: string, reference: string): Promise<Response> {
        var status = await this.ensureStatusLoaded();
        return { ok: true } as any;
    }

    async setConfig(host: string, user: string, pass: string): Promise<Response> {
        var status = await this.ensureStatusLoaded();
        status.fritz.status = Status.connecting;
        setTimeout(() => {
            status.fritz.status = Status.connected;
        }, 1000);
        return { ok: true } as any;
    }
}