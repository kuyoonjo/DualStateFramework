//
//  AnyException.cpp
//  YCTools
//
//  Created by Yu Chen on 11/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#include "../../include/yctools/AnyException.h"

namespace yc
{
    namespace Exception
    {
        
        AnyException::AnyException(std::string from,
                                   std::string to) :
            from(from),
            to(to)
        {}
        
        const char* AnyException::what() const throw()
        {
            return "\"Any\" exception happened!";
        }
        std::string AnyException::details() const throw()
        {
            return "Can not cast " + from + " to " + to;
        }
    }
}