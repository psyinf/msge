#pragma once
#include <chrono>

namespace msge
{

struct FrameStamp
{
    std::uint32_t             frameNumber;
    std::chrono::milliseconds frameTime;
};

}

