#ifndef _INTERPRET_H_
#define _INTERPRET_H_

#include "parse.h"

#include <string>
#include <array>
#include <algorithm>
#include <functional>


bool initialize(parse::SerializeParam<wchar_t**>&);

bool set_arguments(std::array<std::wstring, 10>&, size_t);

bool set_function(std::wstring&);

bool set_module(std::wstring&);

void run();

bool uninitilize();


#endif // _INTERPRET_H_
