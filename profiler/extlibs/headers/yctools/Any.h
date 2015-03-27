//
//  Any.h
//  YCTools
//
//  Created by Yu Chen on 11/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef YCTools_Any_h
#define YCTools_Any_h

#include <memory>
#include <typeindex>
#include <string>

#include "Export.h"
#include "AnyException.h"

namespace yc
{
    class YCTOOLS_API Any
    {
    public:
        Any(void);
        Any(Any& that);
        Any(Any && that);
        template<typename T> Any(T && value);
        
        bool isNull() const;
        template<class T> bool is() const;
        template<class T> typename std::decay<T>::type& to();
        
        template<class T> operator T() const;
        Any& operator=(const Any& any);
        
    private:
        class Base;
        template<typename T> class Derived;
        std::unique_ptr<Base> Clone() const;
        std::unique_ptr<Base> pointer;
        std::type_index typeIndex;
    };
}


/////////////////////////////////////////////////////
//  Class yc::Any

namespace yc
{
    
    template<typename T> Any::Any(T && value) :
        pointer(new Derived <typename std::decay<T>::type> (std::forward<T>(value))),
        typeIndex(std::type_index(typeid(typename std::decay<T>::type)))
    {}
    
    template<class T> bool Any::is() const
    {
        return typeIndex == std::type_index(typeid(T));
    }
    
    template<class T> typename std::decay<T>::type& Any::to()
    {
        if (!this->is<T>())
        {
            throw Exception::AnyException(typeid(T).name(), typeIndex.name());
        }
        
        typedef typename std::decay<T>::type U;
        auto derived = static_cast<Derived<U>*> (pointer.get());
        return derived->value;
    }
    template<class T> Any::operator T() const
    {
        return this->to<typename std::decay<T>::type>();
    }

}

//////////////////////////////////////////
// Inner Classes

namespace yc {
    
	class YCTOOLS_API Any::Base
    {
        public:
        virtual ~Base();
        virtual std::unique_ptr<Base> Clone() const = 0;
    };
    template<typename T>
    class Any::Derived : public Any::Base
    {
    public:
        template<typename U>
        Derived(U && value) : value(std::forward<U>(value)) { }
        
        std::unique_ptr<Base> Clone() const
        {
            return std::unique_ptr<Base>(new Derived<T>(this->value));
        }
        
        T value;
    };
}



#endif
