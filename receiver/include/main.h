#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <iostream>
#include <thread>

#include "../receiver22a.h"

std::vector<int> observe(const std::vector<double> &x1, const std::vector<double> &x2, const std::vector<double> &x3)
{
    auto advance_cursor = []() {
        static int pos=0;
        char cursor[4]={'/','-','\\','|'};
        printf("%c\b", cursor[pos]);
        fflush(stdout);
        pos = (pos+1) % 4;
    };

    std::cerr << "Receiver: signal received" << std::endl;
    if (x1.size() != x2.size() || x1.size() != x3.size())
    {
        std::cerr << "Receiver: bad signal. input size mismatch" << std::endl;
        return std::vector<int>();
    }

    double dt_ = 0.001;
    double transition_ = 4.;

    receiver22a instance_;
    instance_.initialize();
    instance_.getRTM()->Timing.stepSize0 = dt_;

    std::vector<int> result;
    const size_t time_lag = static_cast<int>(std::floor(transition_ / dt_));
    size_t lag_counter = 0;
    size_t i = 0;

    std::cerr << "Receiver: proccessing signal...";
    while (i < x1.size() &&
           rtmGetErrorStatus(instance_.getRTM()) == NULL &&
           !rtmGetStopRequested(instance_.getRTM()))
    {
        advance_cursor();
        instance_.receiver22a_U.x[0] = x1.at(i);
        instance_.receiver22a_U.x[1] = x2.at(i);
        instance_.receiver22a_U.x[2] = x3.at(i);
        i++;
        lag_counter++;
        if (lag_counter >= time_lag)
        {
            lag_counter = 0;
            result.push_back(std::round(instance_.receiver22a_Y.payload_estimation));
        }
        instance_.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::floor(dt_ * 1e3))));
    }
    std::cerr << std::endl << "Receiver: done. result size: " << result.size() << std::endl
              << std::endl;
    instance_.terminate();
    return result;
}
