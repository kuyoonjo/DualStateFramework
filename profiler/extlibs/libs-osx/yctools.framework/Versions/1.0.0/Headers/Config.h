//
//  config.h
//  YCTOOLS
//
//  Created by Yu Chen on 10/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef yctools_Config_h
#define yctools_Config_h

#if defined(_WIN32)

// Windows compilers need specific (and different) keywords for export and import
#define YCTOOLS_API_EXPORT __declspec(dllexport)
#define YCTOOLS_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else // Linux, FreeBSD, Mac OS X

#if __GNUC__ >= 4

// GCC 4 has special keywords for showing/hidding symbols,
// the same keyword is used for both importing and exporting
#define YCTOOLS_API_EXPORT __attribute__ ((__visibility__ ("default")))
#define YCTOOLS_API_IMPORT __attribute__ ((__visibility__ ("default")))

#else

// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#define YCTOOLS_API_EXPORT
#define YCTOOLS_API_IMPORT

#endif

#endif


#endif
