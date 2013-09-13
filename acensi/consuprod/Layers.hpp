#ifndef LAYERS_HPP_
# define LAYERS_HPP_

namespace Layers
{
template <typename Super>
struct Producer : Super
{
private:
  struct iterator : std::iterator<std::output_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    //    typedef typename Super::Business::value_type value_type;

    iterator operator++(int)
    {
      iterator prev = *this;
      ++*this;
      return (prev);
    }

    iterator operator++()
    {
      return (*this);
    }

    typename Super::Business::value_type &operator*()
    {
      std::cout << "MA BITE" << std::endl;
      // 
    }
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    bool insert(typename Super::Business::value_type data)
    {
      
    }

    iterator produce_begin()
    {}
  };

};

template <typename Super>
struct Consumer : Super
{
private:
  struct iterator : std::iterator<std::input_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    typedef typename Super::Business::value_type value_type;

    iterator operator++(int)
    {
      iterator prev = *this;
      ++*this;
      return (prev);
    }

    iterator operator++()
    {
      return (*this);
    }

    typename Super::Business::value_type &operator*();

    // {
    //   return ();
    // }
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {

    }

    typename Super::Business::value_type pop()
    {
      
    }

    iterator consume_begin()
    {}

    iterator end()
    {}
  };

};
}

#endif
