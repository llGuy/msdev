#ifndef _LOG_H_
#define _LOG_H_


void Log(const char* msg)
{
    std::cout << "---------- LOG : " << msg << " ----------\n";
}

void Error(const char* msg)
{
    std::cerr << "--------- ERROR LOG : " << msg << "----------\n";
}


#endif /* _LOG_H_ */


