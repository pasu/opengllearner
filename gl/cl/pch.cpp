#include "pch.h"
#include <iostream>

using namespace std;

void FatalError(const char* file, int line, const char* message)
{
    cout << file << ", line " << line << ":" << endl;
    cout << message << endl;
}

void FatalError(const char* file, int line, const char* message, const char* context)
{
    FatalError(file, line, message);
}
