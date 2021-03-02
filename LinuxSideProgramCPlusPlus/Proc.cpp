#include <Proc.h>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sys/uio.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <string.h>
#include <proc_maps_parser/pmparser.h>
int pid;
std::string processname;
procmaps_iterator* maps;
int ProcessManager::getPID()
{
    return pid;
}

void ProcessManager::setPID()
{
    //thx https://stackoverflow.com/questions/15686450/get-process-id-by-name
    char buf[512];
    std::string cmd;
    cmd = "pidof -s " + processname;
    FILE* cmd_pipe = popen(cmd.c_str(), "r");
    fgets(buf, 512, cmd_pipe);
    pid = strtoul(buf, NULL, 10);
    printf("PID of \"%s\" is %d\n", processname.c_str(), pid);
}

std::string ProcessManager::getProcName()
{
    return processname;
}

void ProcessManager::setProcName(std::string value)
{
    processname = value;
}

uint8_t ProcessManager::read8(uint32_t addr, unsigned char val, int map)
{
    struct iovec local, remote;
    if (addr > GetProcMapSize(map))
    {
        return 0;
    }
    addr += GetProcMapStartAddr(map);
    local.iov_base = &addr;
    local.iov_len = 8;
    remote.iov_base = &val;
    remote.iov_len = 8;
    return process_vm_readv(pid, &local, 1, &remote, 1, 0);
}

void ProcessManager::write8(uint32_t addr, unsigned char val, int map)
{
    struct iovec local, remote;
    if (addr > GetProcMapSize(map))
    {
        return;
    }
    addr += GetProcMapStartAddr(map);
    local.iov_base = &addr;
    local.iov_len = 8;
    remote.iov_base = &val;
    remote.iov_len = 8;
    process_vm_writev(pid, &local, 1, &remote, 1, 0);
}

void ProcessManager::CallMapParser()
{
    pmparser_free(maps);
    maps = pmparser_parse(pid);
}

int ProcessManager::GetProcMapSize(int map)
{
    if (maps == nullptr)
    {
        CallMapParser();
    }
    procmaps_struct* maps_tmp = NULL;
    int i = 0; 
    while (i <= map)
    {
        maps_tmp = pmparser_next(maps);
        if (i = map)
        {
            return maps_tmp->length;
        }
        i++;
    }
    pmparser_free(maps);
}

int ProcessManager::GetProcMapStartAddr(int map)
{
    if (maps == nullptr)
    {
        CallMapParser();
    }
    procmaps_struct* maps_tmp = NULL;
    int i = 0;
    while (i <= map)
    {
        maps_tmp = pmparser_next(maps);
        if (i = map)
        {
            return static_cast<int>(reinterpret_cast<intptr_t>(maps_tmp->addr_start));
        }
        i++;
    }
    pmparser_free(maps);
}

std::string ProcessManager::GetProcMapName(int map)
{
    if (maps == nullptr)
    {
        CallMapParser();
    }
    procmaps_struct* maps_tmp = NULL;
    int i = 0;
    while (i <= map)
    {
        maps_tmp = pmparser_next(maps);
        if (i = map)
        {
            return maps_tmp->pathname;
        }
        i++;
    }
    pmparser_free(maps);
}

int ProcessManager::GetMaxMaps()
{
    if (maps == nullptr)
    {
        CallMapParser();
    }
    return maps->max;
}