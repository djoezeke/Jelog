#include "../JeLog/DefaultLogger.h"

int main(int argc, char const *argv[])
{
    JeLog::DefaultLogger::Get().Log("Hello");
    return 0;
};