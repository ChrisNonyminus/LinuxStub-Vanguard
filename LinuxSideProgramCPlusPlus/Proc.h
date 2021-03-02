#pragma once

#include <string>
#include <proc_maps_parser/pmparser.h>
class ProcessManager
{
public:
    static int getPID();
    static void setPID();
    static std::string getProcName();
    static void setProcName(std::string value);
    static uint8_t read8(uint32_t addr, unsigned char val, int map);
    static void write8(uint32_t addr, unsigned char val, int map);
    static void CallMapParser();
    static std::string ReadMaps();
    static int GetProcMapSize(int map);
    static int GetProcMapStartAddr(int map);
    static std::string GetProcMapName(int map);
    static int GetMaxMaps();
    static int process_mem_usage_data();
    static int process_mem_usage_exe();
    static int process_mem_usage();
};