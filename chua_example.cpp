#include <stdio.h>
#include <iostream>

#include "receiver/include/main.h"
#include "transmitter/include/main.h"

int main(int argc, char const *argv[])
{
    Transmitter transmitter;
    std::vector<int> data = {0, 1, 0, 0, 1, 1};
    auto signal = transmitter.transmit(data);

    Receiver receiver;
    auto estimation = receiver.observe(signal[0], signal[1], signal[2]);
    for (int b : estimation)
        std::cout << b <<  " ";

    return 0;
}
