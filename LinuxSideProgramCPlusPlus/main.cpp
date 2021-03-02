#include <cstdio>
#include <string>
#include <iostream>
#include <Proc.h>
#include <iostream>
#include <map>
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
#include <algorithm>
#include <iterator>
#include <readline/readline.h>
#include <readline/history.h>
#include <Connector.h>

int commandline(std::string func, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
    //Initialize commands (thx https://stackoverflow.com/questions/22929554/using-command-line-input-to-call-a-function)
    if (func == "read8")
    {
        uint32_t decAddr = atoi(arg1.c_str());
        uint8_t decVal = atoi(arg2.c_str());
        int map = atoi(arg3.c_str());
        printf("Calling %s(%d, %d, %d)...\n", func.c_str(), decAddr, decVal, map);
        printf("%X\n",ProcessManager::read8(decAddr, decVal, map));
    }
    if (func == "write8")
    {
        uint32_t decAddr = atoi(arg1.c_str());
        uint8_t decVal = atoi(arg2.c_str());
        int map = atoi(arg3.c_str());
        printf("Calling %s(%d, %d, %d)...\n", func.c_str(), decAddr, decVal, map);
        ProcessManager::write8(decAddr, decVal, map);
    }
    if (func == "recieve")
    {
        UDPConnector::Recieve();
    }
    if (func == "exit")
    {
        exit(0);
    }
}

int main()
{
    
    //printf("Test\n");
    std::string procname;
    std::string currCmd;
    printf("Enter the name (just the filename, not the full path) of the currently running process you want to corrupt.\n>> ");
    std::cin >> procname;

    ProcessManager::setProcName(procname);
    ProcessManager::setPID();
    UDPConnector::Connect();
    std::string func = "";
    std::string arg1 = "";
    std::string arg2 = "";
    std::string arg3 = "";
    std::string arg4 = "";
    while(1)
    {
        printf("Type a command.\n>> ");
        //activate console
        std::string cmd;
        std::cin >> cmd;
        func = "";
        arg1 = "";
        arg2 = "";
        arg3 = "";
        arg4 = "";
        //thanks https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        /*std::istringstream iss(cmd);
        std::string word;
        int args = 0;
        while (iss >> word)
        {
            if (args == 0)
            {
                func = word;
            }
            if (args == 1)
            {
                arg1 = word;
            }
            if (args == 2)
            {
                arg2 = word;
            }
            if (args == 3)
            {
                arg3 = word;
            }
            if (args == 4)
            {
                arg4 = word;
            }
            args++;
            
        }*/
        commandline(func, arg1, arg2, arg3, arg4);
    }
    //return 0;
}