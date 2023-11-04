#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <exception>

#define NO_CCTOR(x) private: x()