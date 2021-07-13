#include "random_generator.hpp"

#include <chrono>

RandomGenerator::RandomGenerator()
{
    std::random_device device;

    std::random_device::result_type seed;

    if(device.entropy() != 0)
    {
        seed = device();
    }
    else
    {
        seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    m_engine.seed(seed);
}

std::mt19937 & RandomGenerator::get()
{
    return m_engine;
}
