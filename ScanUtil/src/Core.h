#ifndef __SCAN_CORE_H__
#define __SCAN_CORE_H__


#include <iostream>
#include "Platform/Platform.h"


#define LOG(level, message) std::cout << "[" << #level << "] " << ##message << '\n' 

#define INFO(message) LOG(INFO, message)
#define WARN(message) LOG(WARNING, message)
#define FATAL(message) LOG(FATAL, message)


#endif
