#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>
#include <memory>

class Number
{
public:
    using Movable = std::unique_ptr<Number>;
    using Value = uint32_t;

public:
    explicit Number(Value _value);
    Number(const Number &) = delete;
    Number(Number &&)      = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&)      = default;

    static Movable make(Value _value);

public:
    Value value()                          const;
    bool  canMerge(const Number & _number) const;

    void merge(Movable & _number);
    void clearMergeState();

private:
    Value m_value;
    bool  m_merged;
};

#endif
