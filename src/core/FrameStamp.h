#pragma once
#include <chrono>
#include <stdint.h>

class FrameStamp
{
public:
    std::chrono::milliseconds frameDuration;
    std::uint64_t             frameNumber;
};




