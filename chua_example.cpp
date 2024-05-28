#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "receiver/include/main.h"
#include "transmitter/include/main.h"
#include "yaml-cpp/yaml.h"

void write_signal(std::ofstream &f, std::vector<double> signal, std::string name)
{
    f << name << ": [";
    for (const auto &s : signal)
    {
        f << s;
        if (&s != &signal.back())
            f << ",";
    }
    f << "]" << std::endl;
}

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

    auto signal = transmit(data);
    auto estimation = observe(signal[0], signal[1], signal[2]);

    std::ofstream out_encrypted;
    out_encrypted.open("encrypted_signal.yaml");
    write_signal(out_encrypted, signal[0], "x1");
    write_signal(out_encrypted, signal[1], "x2");
    write_signal(out_encrypted, signal[2], "x3");
    out_encrypted.close();
    
    std::ofstream out_estimation;
    out_estimation.open("estimation_signal.yaml");
    out_estimation << "estimation: [";
    for (const auto  &s  : estimation) {
        out_estimation << s;
        if (&s !=  &estimation.back())
            out_estimation << ",";
    }
    out_estimation << "]"  << std::endl;
    out_estimation.close();

    return 0;
}
