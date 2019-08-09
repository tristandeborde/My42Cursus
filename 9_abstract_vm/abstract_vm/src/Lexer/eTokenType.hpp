#ifndef ETOKENTYPE_HPP
# define ETOKENTYPE_HPP

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
    eof, // recently swapped with badsyntax
    badsyntax,
    COUNT
};

enum class eExceptionType {
    missingNumberException = 0,
    forbiddenTokenException,
    noExitException,
    misplacedExitException,
    COUNT
};

#endif
