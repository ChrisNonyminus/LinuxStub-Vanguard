#pragma once

#include <string>
class ProcessManager
{
public:
    static int getPID();
    static void setPID();
    static std::string getProcName();
    static void setProcName(std::string value);
    static uint8_t read8(uint32_t addr, unsigned char val, std::string map);
    static void write8(uint32_t addr, unsigned char val, std::string map);
};