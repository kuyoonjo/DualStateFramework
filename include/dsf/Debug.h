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
#if __OPTIMIZE__
#define Debug(x)
#else
#define Debug(x) std::cout << x << std::endl
#endif
}

#endif
