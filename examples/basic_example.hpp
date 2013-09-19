
#include <iostream>
#include "Empty.hpp"
#include "Utility.hpp"

template <typename Super>
struct IA1 : Super
{
  struct Business : Super::Business
  {
    template <typename... Args>
    Business(Args&&... args) : Super::Business(args...)
    {}

    void functionA() const
    {
      std::cout << "this object has the method functionA() because it is aspectized by IA1"<< std::endl;
    }

    void function() const
    {
      std::cout << "IA1::function()" << std::endl;
    }
  };
};

template <typename Super>
struct IA2 : Super
{
  struct Business : Super::Business
  {
    template <typename... Args>
    Business(Args&&... args) : Super::Business(args...)
    {}

    void function() const
    {
      std::cout << "IA2::function()" << std::endl;
    }
  };
};

template <typename Super>
struct IB52 : Super
{
  struct Business : Super::Business
  {
    template <typename... Args>
    Business(Args&&... args) : Super::Business(args...)
    {}

    void functionB() const
    {
      std::cout << "this object has the method functionB() because it is aspectized by B52"<< std::endl;
      static_cast<typename Super::Whole::Business const*>(this)->functionA();
    }

    void functionB1() const
    {
      //      static_cast<typename GetUpperAspect<IB52> >
    }

    void function() const
    {
      std::cout << "IB52::function()" << std::endl;
    }
  };

private:
  //  typedef A<IA1> Dumby;
};
