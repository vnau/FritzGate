import type { ApiService, StatusData } from "../interfaces";

export class FritzGateApiService implements ApiService {
    private getEndpoint(endpoint: string) {
        const apiUrl = (["localhost", "127.0.0.1"].includes(window.location.hostname) ? "http://fritzgate" : "") + "/api/";
        return apiUrl + endpoint;
    }

    async fetchStatus(): Promise<StatusData | undefined> {
        var result: StatusData | undefined = undefined;
        const controller = new AbortController();
        const timeoutId = setTimeout(() => {
            controller.abort();
            //  busy = true;
        }, 2000);

        try {
            const sensorsJson = await fetch(this.getEndpoint("status"), {
                signal: controller.signal,
            });
            result = await sensorsJson.json();
        } finally {
            clearTimeout(timeoutId);
        }
        return result;
    }

    async setBinding(device: string, reference: string): Promise<Response> {
        const response = await fetch(this.getEndpoint("thermostat"), {
            method: "POST",
            body: JSON.stringify({
                id: device,
                referenceSensor: reference,
            }),
            headers: {
                "Content-Type": "application/json",
            },
        });
        return response;
    }

    async setConfig(host: string, user: string, pass: string): Promise<Response> {
        return await fetch(this.getEndpoint("fritzauth"), {
            method: "POST",
            body: JSON.stringify({ host, user, pass }),
        });
    }
}