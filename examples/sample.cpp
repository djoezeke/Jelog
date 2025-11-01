#include <JeLog/Jelog.h>

int main(int argc, char const *argv[])
{
    JeLog::DefaultLogger::Get().Log(std::string("Hello"));
    return 0;
};