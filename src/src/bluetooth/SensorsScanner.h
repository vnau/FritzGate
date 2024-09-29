#pragma once

#include "../models/sensor.h"
#include <string>

/**
 * @brief Abstract base class to handle BLE device scan callbacks.
 *
 * This interface is used to process scan results for BLE devices.
 * Implement this class to define what should happen when a sensor is detected.
 */
class SensorScannerCallback
{
public:
    virtual ~SensorScannerCallback() = default;

    /**
     * @brief Called when a new BLE sensor is detected during scanning.
     *
     * @param sensor Pointer to the detected sensor's data.
     */
    virtual void onResult(Sensor *sensor) = 0;
};

/**
 * @brief Abstract base class for BLE scanning operations.
 *
 * Implementations of this class will handle initializing and starting BLE scans.
 */
class SensorsScanner
{
public:
    virtual ~SensorsScanner() = default;

    /**
     * @brief Initialize the BLE scanner with a device name.
     *
     * @param deviceName Name of the BLE device to initialize.
     */
    virtual void init(const std::string deviceName) = 0;

    /**
     * @brief Start the BLE scan with the specified callback for handling results.
     *
     * @param pAdvertisedDeviceCallbacks Callback instance to handle scan results.
     */
    virtual void start(SensorScannerCallback *pAdvertisedDeviceCallbacks) = 0;
};
