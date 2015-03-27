//
//  AnyException.h
//  YCTools
//
//  Created by Yu Chen on 11/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef YCTools_AnyException_h
#define YCTools_AnyException_h

#include <exception>
#include <string>

#include "Export.h"
namespace yc
{
    namespace Exception
    {
        class YCTOOLS_API AnyException : public std::exception
        {
        public:
            AnyException(std::string from,
                         std::string to);
            virtual const char* what() const throw() override;
            std::string details() const throw();
        private:
            std::string from;
            std::string to;
        };
    }
    
}
#endif
