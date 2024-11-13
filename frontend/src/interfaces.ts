export interface SensorStatus {
    humidity: number;
    id: string;
    name: string;
    model: string;
    data: string;
    serial: string;
    rssi: number;
    temperature: number;
    timestamp: number;
    seriesTimestamp: number;
    battery: number;
}

export interface StatusData {
    sensors: SensorStatus[];
    thermostats: DeviceStatus[];
}

export interface DeviceStatus extends SensorStatus {
    targetTemperature: number;
    referenceSensor: string;
}
