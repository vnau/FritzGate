#pragma once
#include "SensorsScanner.h"

/**
 * @brief Singleton class to retrieve the BLE scan instance.
 *
 * Use this class to obtain a BLE scan object to start scanning for sensors.
 */
class TheengsSensorsScanner
{
public:
    /**
     * @brief Retrieve the scan object for BLE scanning operations.
     *
     * This is a singleton object. The caller should not release or delete it.
     *
     * @return Pointer to the BLE scan object.
     */
    static SensorsScanner *getScan();
};