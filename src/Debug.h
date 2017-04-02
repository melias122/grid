#ifndef GRID_DEBUG_H
#define GRID_DEBUG_H

#ifdef DEBUG
#include <iostream>
#define DBG_LOG(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": " << msg << std::endl;
#else
#define DBG_LOG(msg)
#endif

#endif
