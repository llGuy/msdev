#include "log.h"

#include <string>
#include <iostream>

void NewLog(const std::string& msg)
{
    std::cout << "---------- " << msg << " ----------" << std::endl; 
}

void Log(const std::string& msg)
{
    std::cout << "LOG > " << msg << std::endl;
}

void Error(const std::string& msg)
{
    std::cout << "ERROR > " << msg << std::endl;
}


