//
//  Any.cpp
//  YCTools
//
//  Created by Yu Chen on 11/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#include "../../include/yctools/Any.h"

namespace yc
{
    Any::Any() :
    typeIndex(std::type_index(typeid(void) ))
    {}
    
    Any::Any(Any& that) :
    pointer(that.Clone()),
    typeIndex(that.typeIndex)
    {}
    
    Any::Any(Any && that) :
    pointer(std::move(that.pointer)),
    typeIndex(that.typeIndex)
    {}
    
    bool Any::isNull() const
    {
        return !bool(pointer);
    }
    
    Any& Any::operator=(const Any& any)
    {
        if (this->pointer == any.pointer)
            return *this;
        
        this->pointer = any.Clone();
        this->typeIndex = any.typeIndex;
        return *this;
    }
    
    Any::Base::~Base() {}
    
    std::unique_ptr<Any::Base> Any::Clone() const
    {
        if (pointer != nullptr)
            return pointer->Clone();
        
        return nullptr;
    }
}
