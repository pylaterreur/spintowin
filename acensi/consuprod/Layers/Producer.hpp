#ifndef LAYERS_PRODUCER_HPP_
# define LAYERS_PRODUCER_HPP_

namespace Layers
{
template <typename Super>
struct Producer : Super
{
public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    template <typename T>
    void push_back(T&& t)
    {
      // wait if insert index == lowest consumer index
      // increment
      // Super::Business::insert(std::forward<T>(t));
    }

  };

};
}

#endif
