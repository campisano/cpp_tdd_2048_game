#ifndef NUMBER_TESTABLE__HPP__
#define NUMBER_TESTABLE__HPP__

#include "../../2048/domain/number.hpp"

class NumberTestable : public Number
{
public:
    bool & m_deleted;
    explicit NumberTestable(Value _v, bool & _deleted) : Number(_v),
        m_deleted(_deleted)
    {
        m_deleted = false;
    }

    virtual ~NumberTestable()
    {
        m_deleted = true;
    }
};

#endif
