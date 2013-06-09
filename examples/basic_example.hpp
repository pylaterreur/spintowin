
#include <iostream>

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
  };

private:
  //  typedef A<IA1> Dumby;
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
  };

private:
  //  typedef A<IA1> Dumby;
};
