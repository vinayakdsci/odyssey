#include "errors.h"

#include <iostream>

const char* LexerError::what() const noexcept { return what_.c_str(); }
const char* ParserError::what() const noexcept { return what_.c_str(); }

void Diagnostic::print_diagnostic() {
    const char* msg = message.c_str();
    printf("\x1B[u\x1B[A\033[1;91m\nerror: \033[0m\033[1m%s\033[0m\n", msg);
}
