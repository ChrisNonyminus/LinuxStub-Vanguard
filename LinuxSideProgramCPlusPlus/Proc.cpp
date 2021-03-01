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
int pid;
std::string processname;
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

uint8_t ProcessManager::read8(uint32_t addr, unsigned char val, std::string map)
{
    struct iovec local, remote;
    local.iov_base = &addr;
    local.iov_len = 8;
    remote.iov_base = &val;
    remote.iov_len = 8;
    return process_vm_readv(pid, &local, 1, &remote, 1, 0);
}

void ProcessManager::write8(uint32_t addr, unsigned char val, std::string map)
{
    struct iovec local, remote;
    local.iov_base = &addr;
    local.iov_len = 8;
    remote.iov_base = &val;
    remote.iov_len = 8;
    process_vm_writev(pid, &local, 1, &remote, 1, 0);
}