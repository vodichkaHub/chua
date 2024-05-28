#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <iostream>
#include <thread>

#include "../receiver22a.h"

class Receiver
{
private:
    receiver22a instance_;
    double dt_ = 0.01;
public:
    Receiver()
    {
        instance_.initialize();
        instance_.getRTM()->Timing.stepSize0 = dt_;
    };

    ~Receiver()
    {
        instance_.terminate();
    };

    inline std::vector<uint8_t> observe(const std::vector<double> &x1, const std::vector<double> &x2, const std::vector<double> &x3)
    {
        std::cerr << "signal received" <<  std::endl;
        if (x1.size()!= x2.size() || x1.size()!= x3.size()) {
            std::cerr << "bad signal. input size mismatch"  <<  std::endl;
            return std::vector<uint8_t>();
        }

        std::vector<uint8_t> result;
        const size_t time_lag = static_cast<int>(std::floor(2. / dt_));
        size_t lag_counter=0;
        size_t i=0;

        std::cerr << "proccessing signal..." << std::endl;
        while (i < x1.size() &&
               rtmGetErrorStatus(instance_.getRTM()) == NULL &&
              !rtmGetStopRequested(instance_.getRTM()))
        {
            instance_.receiver22a_U.x[0] = x1.at(i);
            instance_.receiver22a_U.x[1] = x2.at(i);
            instance_.receiver22a_U.x[2] = x3.at(i);
            i++; lag_counter++;
            if (lag_counter >= time_lag)
            {
                lag_counter=0;
                result.push_back(static_cast<int>(std::round(instance_.receiver22a_Y.payload_estimation)));
            }
            instance_.step();
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::floor(dt_ * 1e3))));
        }
        std::cerr << "done. result size: "  << result.size() << std::endl << std::endl;
        return result;
    };
};
