#ifndef MOVE_ONLY__HPP__
#define MOVE_ONLY__HPP__

// from c++ International Standard example N4296 p210
class MoveOnly
{
protected:
    // no virtual destructor used to avoid unecessary overhead
    // therefore it needs to be protected to avoid the delete of such base class pointers and cause memory leaks
    // from http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual

    // after that, this class can be usable only as base class, so all methods can be protected
    explicit MoveOnly()        = default;
    MoveOnly(const MoveOnly &) = delete;
    MoveOnly(MoveOnly &&)      = default;
    ~MoveOnly()                = default;

    MoveOnly & operator=(const MoveOnly &) = delete;
    MoveOnly & operator=(MoveOnly &&)      = default;
};

#endif
