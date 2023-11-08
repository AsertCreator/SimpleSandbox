#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <exception>

#define NO_CCTOR(x) private: x()
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 2

typedef void (*BasicEvent)(void*, int);
typedef bool (*VetoEvent)(void*, int);