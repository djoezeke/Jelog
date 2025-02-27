
#include "Je-Log/je-log.h"

int main(int argc, char const *argv[])
{
    JeLog::DefaultLogger::Get().Log("Hello");
    return 0;
};