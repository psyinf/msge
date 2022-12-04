#pragma once
#include <chrono>
#include <stdint.h>
namespace msge
{

class FrameStamp
{
public:
    std::chrono::milliseconds frameDuration;
    std::uint64_t             frameNumber;
};
} //namespace msge



