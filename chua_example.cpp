#include <stdio.h>
#include <iostream>

#include "receiver/include/main.h"
#include "transmitter/include/main.h"
#include "yaml-cpp/yaml.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "No input file path!" << std::endl;
        return 1;
    }

    YAML::Node input = YAML::LoadFile(argv[1]);
    std::vector<int> data;
    if (input["signal"])
        data = input["signal"].as<std::vector<int>>();

    std::cout << data[1] << std::endl;
    // auto signal = transmit(data);

    // auto estimation = observe(signal[0], signal[1], signal[2]);

    return 0;
}
