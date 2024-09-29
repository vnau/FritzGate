#pragma once
#include <string>
#include <Stream.h>

class Sensor
{
public:
    unsigned long timestamp;
    unsigned long seriesTimestamp = 1701790712;
    std::string name;
    std::string id;
    std::string model;
    std::string serial;
    std::string data;

    uint32_t temperature;
    double temperatureAvg;
    uint32_t humidity = 0;
    int8_t rssi = 0;
    int8_t battery = 0;
    void Serialize(Stream &client, long timestamp, int indentLevel = 0);
    virtual void SerializeShort(Stream &client, int indentLevel = 0);

protected:
    void printIndent(Stream &client, int level);
    virtual void SerializeBody(Stream &client, long timestamp, int indentLevel);
};