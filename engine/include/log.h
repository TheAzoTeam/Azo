/**
 * @file log.h
 * @brief Purpose: Contains general scope to the log.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef LOG_H
#define LOG_H


#include <iostream>
#include <cstdlib>


// Generating macro of the NINFO.
#ifndef NINFO
#   define INFO(...) \
	std::cout << "[INFO] " << __VA_ARGS__ << std::endl;
#else
#   define INFO(...)
#endif

// Generating macro of the  WARN.
#ifndef NWARN
#   define WARN(...) \
	std::cout << "[WARN] " << __VA_ARGS__ << std::endl;
#else
#   define WARN(...)
#endif

// Generating macro of the NERROR.
#ifndef NERROR
#   define ERROR(...)							      \
	do {									  \
		std::cout	<< "[ERROR] " << __FILE__ << " line " << __LINE__	    \
				<< std::endl << __VA_ARGS__ << std::endl;		    \
		std::exit(EXIT_FAILURE);					      \
	} while(false)
#else
#   define ERROR(...)
#endif

// Generating macro of the NDEBUG.
#ifndef DEBUG
    #ifndef NDEBUG
    #   define DEBUG(...) \
	std::cerr << "[DEBUG] " << __VA_ARGS__ << std::endl;
    #else
    #   define DEBUG(...)
    #endif
#endif

// Generating macro of the NASSERT.
#ifndef NASSERT
#   define ASSERT(condition, ...) \
	do { \
		if(!(condition)){ \
			std::cerr	<< "Assertion `" # condition "` failed in " << __FILE__	\
					<< " line " << __LINE__ << ": " << __VA_ARGS__ << std::endl; \
			std::exit(EXIT_FAILURE); \
		} \
	} while(false)
#else
#   define ASSERT(condition, ...)
#endif

#endif
