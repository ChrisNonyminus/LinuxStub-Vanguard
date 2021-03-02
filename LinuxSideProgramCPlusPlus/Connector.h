#pragma once
#include <string>
class UDPConnector
{
public:
    static void Connect();
    static std::string Recieve();
    static std::string Send(std::string text);
    static void Disconnect();

    static void ExecuteCommand();
    
};