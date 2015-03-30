//
//  Export.h
//  DualStateFramework
//
//  Created by Yu Chen on 10/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef dsf_Export_h
#define dsf_Export_h

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Config.h"


////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(dsf_EXPORTS)

#define DSF_API DSF_API_EXPORT

#else

#define DSF_API DSF_API_IMPORT

#endif

#endif
