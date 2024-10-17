#include <iostream>

template <typename T>
class shared_ptr_toy
{
    int* counter = new int(0);
    T* object = nullptr;
public:
    T& operator*(T* _object)
    {
        object = _object;
        std::cout << "operator T*" << std::endl;
        return *object;
    }
    int& operator*(int* _counter)
    {
        counter = _counter;
        std::cout << "operator int*" << std::endl;
        return *counter;
    }
    int& operator = (const shared_ptr_toy& other)
    {
        std::cout << "Operator =" << std::endl;
        if (*counter == 1)
        {
            delete this->object;
            delete this->counter;
        }
        *counter -= 1;
        this->object = other.object;
        this->counter = other.counter;
        *counter += 1;
        return *counter;
    }

    T* make_shared_toy(T* _object)
    {

        std::cout << "make shared_toy" << std::endl;
        *this = shared_ptr_toy(_object);
        return this->object;

    }
    shared_ptr_toy()
    {
        shared_ptr_toy <std::string> toy= nullptr;
    }
    shared_ptr_toy(T *object)
    {
        if (this->object != nullptr)
        {
            this->object = nullptr;
            counter = 0;
        }
        std::cout << "construct: " << this << std::endl;
        this->object = object;
        *counter = 1;
    }
    shared_ptr_toy(const shared_ptr_toy &other)
    {
        std::cout << "construct copy: " << this << std::endl;
        this->object = other.object;
        this->counter = other.counter;
        *counter += 1;

    }

    void reset()
    {
        std::cout << "Toy " << *object << " was dropped\n";
        *counter -= 1;
        this->counter = new int;
        this->object = new T;
        *counter = 0;
        object = nullptr;
    }

    T* get() const
    {
        std::cout << "get:\n";
        return this->object;
    }
    int use_count() const
    {
        return *counter;
    }
    std::string getToyName()
    {
        if (object != nullptr)
            return *object;
        else
            return "Nothing";
    }

    ~shared_ptr_toy()
    {
        *counter-=1;
        if (*counter == 0)
        {
            std::cout << "destructor: " << this << std::endl;
            delete object;
            delete counter;
        }
    }
};


int main()
{
    shared_ptr_toy <std::string >toy_01;
    toy_01.make_shared_toy(new std::string("ball"));
    shared_ptr_toy <std::string>toy_02(toy_01);
    shared_ptr_toy<std::string> toy_03 = new std::string("duck");

    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;

    std::cout << "=================================================" << std::endl;
    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_02.reset();
    toy_03.reset();
    return 0;

}
