#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>
#include <memory>
#include "../../common/move_only.hpp"

class Number : MoveOnly
{
public:
    using Value   = uint32_t; //TODO use of unsigned values can mask logic errors
    using Movable = std::unique_ptr<Number>;

    static Movable make(Value _value);

    virtual ~Number();

protected:
    explicit Number(Value _value);

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
