#ifndef GRID_DEBUG_H
#define GRID_DEBUG_H

#include <iostream>

#ifdef DEBUG
#define DBG_LOG(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": " << msg << std::endl;
#else
#define DBG_LOG(msg)
#define println(msg) std::cout << msg << std::endl
#endif

#endif
