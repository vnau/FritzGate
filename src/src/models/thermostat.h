#pragma once
#include <Stream.h>
#include <string>
#include <vector>
#include "sensor.h"

class PresetAction
{
private:
    uint16_t time;
    uint8_t state;

public:
    PresetAction(int hours, int minutes, int8_t dayOfWeek, bool enabled)
        : time(((int16_t)hours) << 8 | minutes),
          state(((1 << dayOfWeek) & 0x7F) | (enabled ? 0x80 : 0x00))
    {
    }

    uint8_t hours() const;
    uint8_t minutes() const;
    bool enabled() const;
    int order() const;
    uint8_t daysOfWeekMask() const;
    void addDayOfWeek(int8_t dayOfWeek);
    uint8_t firstDay() const;
};

class Thermostat : public Sensor
{
public:
    int windowOpenTimer;
    int windowOpenTrigger;
    std::string temperatureSensor;
    std::string externalTemperatureSensorId;
    bool adaptiveHeating = false;
    uint32_t targetTemperature = 0;
    uint32_t targetTemperatureLow = 0;
    uint32_t targetTemperatureHigh = 0;
    int32_t offset = 0;
    unsigned long offsetTimestamp;
    std::vector<PresetAction> weeklyTimetable;
    std::string referenceSensor;

protected:
    virtual void SerializeBody(Stream &client, long timestamp, int indentLevel);
};