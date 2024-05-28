#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <array>
#include <iostream>
#include <thread>

#include "../transmitter22a.h"

class Transmitter
{
private:
    transmitter22a instance_;
    double dt_ = 0.01;
public:
    Transmitter()
    {
        instance_.initialize();
        instance_.getRTM()->Timing.stepSize0 = dt_;
    };

    ~Transmitter()
    {
        instance_.terminate();
    };

    inline std::array<std::vector<double>, 3> transmit(const std::vector<std::uint8_t> &msg) {
        std::cerr << "message received"  <<  std::endl;
        if (msg.empty()) {
            std::cerr << "bad input. message is empty"  <<  std::endl;
            return {};
        }

        std::array<std::vector<double>, 3> result;
        const size_t time_lag = static_cast<int>(std::floor(2. / dt_));
        size_t lag_counter=0;
        size_t i=0;

        std::cerr << "transmit signal... it will take " << msg.size() * 2 << " seconds" <<  std::endl;
        while (i < msg.size() &&
               rtmGetErrorStatus(instance_.getRTM()) == NULL &&
              !rtmGetStopRequested(instance_.getRTM()))
        {
            instance_.transmitter22a_U.payload = msg[i];
            result[0].push_back(instance_.transmitter22a_Y.x[0]);
            result[1].push_back(instance_.transmitter22a_Y.x[1]);
            result[2].push_back(instance_.transmitter22a_Y.x[2]);
            lag_counter++;
            if (lag_counter >= time_lag) {
                lag_counter = 0;
                i++;
            }
            instance_.step();
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::floor(dt_ * 1e3))));
        }
        std::cerr << "done. result size: "  << result.size() << std::endl << std::endl;
        return result;
    };
};

// extern "C" {
//     Transmitter* Transmitter_new(){ return new Transmitter(); }
//     void Transmitter_transmit(Transmitter* foo, const unsigned char *msg) {
//         const unsigned char *data = msg;
//         std::vector<std::uint8_t> vector(data, data + strlen((char*)msg));
//         foo->transmit(vector);
//     }
//     void Transmitter_destroy(Transmitter* foo) { foo->~Transmitter(); }
// }