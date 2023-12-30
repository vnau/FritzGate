export interface SensorStatus {
    humidity: number;
    id: string;
    name: string;
    model: string;
    serial: string;
    rssi: number;
    temperature: number;
    timestamp: number;
    seriesTimestamp: number;
    battery: number;
}

export interface DeviceStatus extends SensorStatus {
    targetTemperature: number;
    referenceSensor: string;
}
