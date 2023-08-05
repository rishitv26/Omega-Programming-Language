#include "common.h"

Pointer::Pointer():c_ptr(nullptr) {}

Pointer::~Pointer() { delete[] c_ptr; }

void* Pointer::raw_ptr() { return c_ptr; }
