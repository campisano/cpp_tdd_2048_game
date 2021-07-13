#ifndef RANDOM_GENERATOR__HPP__
#define RANDOM_GENERATOR__HPP__

#include <random>

class RandomGenerator
{
public:
    static RandomGenerator & instance()
    {
        static RandomGenerator instance;
        return instance;
    }

    RandomGenerator(RandomGenerator const &) = delete;
    void operator=(RandomGenerator const &)  = delete;

    std::mt19937 & get();

private:
    RandomGenerator();
    std::mt19937 m_engine;
};

#endif
