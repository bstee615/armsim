#ifndef CURRENTTIME_H
#define CURRENTTIME_H

// Source: https://stackoverflow.com/a/14032877
#include <chrono>

// make the decltype slightly easier to the eye
using ms_t = std::chrono::milliseconds;

// return the same type as seconds.count() below does.
// note: C++14 makes this a lot easier.
decltype(ms_t().count()) get_ms_since_epoch()
{
    // get the current time
    const auto now     = std::chrono::system_clock::now();

    // transform the time into a duration since the epoch
    const auto epoch   = now.time_since_epoch();

    // cast the duration into seconds
    const auto milliseconds = std::chrono::duration_cast<ms_t>(epoch);

    // return the number of seconds
    return milliseconds.count();
}

#endif // CURRENTTIME_H
