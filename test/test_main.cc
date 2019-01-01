#include "logmos/logger.h"
#include "logmos/color.h"

int main() {
    INFO("hello this is %s test", "info");
    DEBUG("hello this is %s test", "debug");
    WARN("hello this is %s test", "warn");
    ERROR("hello this is %s test", "error");

    INFO() << "this is info test, nice to meet you";
    DEBUG() << "this is info test, nice to meet you";
    WARN() << "this is info test, nice to meet you";
    ERROR() << "this is info test, nice to meet you";
    return 0;
}
