#include <stdio.h>
#include <iostream>

#include "receiver/include/main.h"
#include "transmitter/include/main.h"
#include "yaml-cpp/yaml.h"

int main(int argc, char const *argv[])
{
    std::vector<int> data = {0, 1, 0, 0, 1, 1};
    auto signal = transmit(data);

    auto estimation = observe(signal[0], signal[1], signal[2]);

    return 0;
}
