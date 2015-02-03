//
//  Export.h
//  YCTOOLS
//
//  Created by Yu Chen on 10/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef yctools_Export_h
#define yctools_Export_h

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Config.h"


////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(YCTOOLS_EXPORTS)

#define YCTOOLS_API YCTOOLS_API_EXPORT

#else

#define YCTOOLS_API YCTOOLS_API_IMPORT

#endif

#endif
