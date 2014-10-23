//
//  Debug.h
//  dsf
//
//  Created by Yu Chen on 10/21/14.
//
//

#ifndef dsf_Debug_h
#define dsf_Debug_h

#include <iostream>

namespace dsf {
#ifdef DEBUG
#define Debug(x) std::cout << x << std::endl
#else
#define Debug(x)
#endif
}

#endif
