#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <array>
#include <iostream>
#include <thread>

#include "../transmitter22a.h"

std::array<std::vector<double>, 3> transmit(const std::vector<int> &msg)
{
    std::cerr << "message received" << std::endl;
    if (msg.empty())
    {
        std::cerr << "bad input. message is empty" << std::endl;
        return {};
    }

    double dt_ = 0.01;

    transmitter22a instance_;
    instance_.initialize();
    instance_.getRTM()->Timing.stepSize0 = dt_;

    std::array<std::vector<double>, 3> result;
    const size_t time_lag = static_cast<int>(std::floor(2. / dt_));
    size_t lag_counter = 0;
    size_t i = 0;

    std::cerr << "transmit signal... it will take " << msg.size() * 2 << " seconds" << std::endl;
    while (i < msg.size() &&
           rtmGetErrorStatus(instance_.getRTM()) == NULL &&
           !rtmGetStopRequested(instance_.getRTM()))
    {
        instance_.transmitter22a_U.payload = msg[i];
        result[0].push_back(instance_.transmitter22a_Y.x[0]);
        result[1].push_back(instance_.transmitter22a_Y.x[1]);
        result[2].push_back(instance_.transmitter22a_Y.x[2]);
        lag_counter++;
        if (lag_counter >= time_lag)
        {
            lag_counter = 0;
            i++;
        }
        instance_.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::floor(dt_ * 1e3))));
    }

    std::cerr << "done. result size: " << result.size() << std::endl
              << std::endl;
    instance_.terminate();
    return result;
}