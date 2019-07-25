#ifndef eTokenType_HPP
# define eTokenType_HPP

# include <cstddef>

enum class eTokenType {
    exit = 0,
    dump,
    push,
    pop,
    assert,
    add,
    sub,
    mul,
    div,
    mod,
    print,
    int8,
    int16,
    int32,
    flt,
    dbl,
    endl,
    badsyntax,
    eof,
    COUNT
};

// Custom struct, necessary in order to use eTokenType as a map key in Parser.cpp
struct eTokenTypeHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif
