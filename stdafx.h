#pragma once

#if defined AMD64 || defined _DEBUG
#error Платформа не поддерживается
#endif // #if defined AND64 || defined _DEBUG


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <string_view>

#include <Windows.h>

// #include <Python.h>
