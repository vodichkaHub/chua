#include <stdio.h>
#include <iostream>

// #include "receiver/project/include/main.h"
#include "transmitter/project/include/main.h"

int main(int argc, char const *argv[])
{
    Transmitter transmitter;
    std::vector<uint8_t> data = {0, 1, 0, 0, 1, 1};
    transmitter.transmit(data);
    return 0;
}
