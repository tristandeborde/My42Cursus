#ifndef TOKENTYPE_HPP
# define TOKENTYPE_HPP

enum class TokenType {
    exit = 1,
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
    badsyntax,
    missingpar,
    isolatedvar
};

#endif
