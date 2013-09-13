#ifndef LAYERS_HPP_
# define LAYERS_HPP_

# include <utility>

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
      return (*new typename Super::Business::value_type(new std::string("LOl")));
      // 
    }
  };

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

template <typename Super>
struct Consumer : Super
{
private:
  struct iterator : std::iterator<std::input_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    typedef typename Super::Business::value_type value_type;
    typedef typename Super::Whole::Business QueueType;

    iterator() : q_(0)// , r_(0)
    {}

    iterator(iterator &&copy) = default;

    iterator(const iterator &copy) = delete;

    iterator(QueueType &q)
    {
      // r_ = q.r_++ (atomic)
    }

    ~iterator()
    {
      /* 
      ** signal q_ that the minimum consumer index cant be r_ anymore,
      ** IF ref_counter_ < 2
      ** (atomic plz)
      ** in that case, q_ will have to notify if r_ and minimum consumer index were the same
      */
    }

    // we aint caring about exception safety and Herb Sutter stuff
    // http://stackoverflow.com/questions/7177884/can-i-use-placement-newthis-in-operator
    iterator &operator=(iterator &&copy)
    {
      if (this != &copy)
	{
	  this->~iterator();
	  new(this) (iterator());
	}
      return (*this);
    }

    iterator operator++(int) = delete;
    // {
    //   iterator prev = *this;
    //   ++*this;
    //   return (prev);
    // }

// iterator

    iterator operator++()
    {
      
      return (*this);
    }

    typename Super::Business::value_type &operator*()
    {
      
    }

    QueueType *q_;
    unsigned r_;
    
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
