#include <dsf/Synchronisable.h>

class Int
{
private:
    int value;
public:
    void setValue(int value)
    {
        this->value = value;
    }
    int getValue() const
    {
        return this->value;
    }
};

class SynchronizedInt : public dsf::Synchronisable<Int>, public Int
{
public:
    void synchronise() override
    {
        this->setValue(next->getValue());
    }
    void setValue(int value)
    {
        next->setValue(value);
    }
};
