#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>
#include <memory>

class Number
{
public:
    using Value = uint32_t; //TODO use of unsigned values can mask logic errors

    using Movable = std::unique_ptr<Number>;
    static Movable make(Value _value);

protected:
    explicit Number(Value _value);

public:
    Number(const Number &) = delete;
    Number(Number &&)      = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&)      = default;

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
