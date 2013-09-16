#ifndef LAYERS_CONSUMER_HPP_
# define LAYERS_CONSUMER_HPP_

namespace Layers
{
template <typename Super>
struct Consumer : Super
{
private:
  template <typename T>
  struct dereference_iterator
  {
    T operator*()
    {
      //      return (std::string("hihi"));
    }
  };

  template <template <typename...> class Container, typename T, typename ...Others>
  struct dereference_iterator<Container<T, Others...> >
  {
    T operator*()
    {
      //      static_cast<>
      return (std::string("hihi"));
    }
  };

  struct iterator : std::iterator<std::input_iterator_tag, typename Super::Business::value_type>, iterator_base, dereference_iterator<typename Super::Business::value_type>
  {
    typedef typename Super::Business::value_type value_type;
    typedef typename Super::Whole::Business QueueType;

    iterator() : q_(0), ref_counter_(new unsigned (1)), r_(0)
    {}

    iterator(const iterator &copy) : q_(copy.q_), ref_counter_(copy.ref_counter_), r_(copy.r_)
    {
      ++*ref_counter_;
    }

    iterator(QueueType &q) : q_(&q), ref_counter_(new unsigned (1))
    {
      // r_ = q.r_++ (atomic)
    }

    ~iterator()
    {
      --*ref_counter_;
      if (*ref_counter_ == 0)
	{
	  // q.reader_end_[r_] = 1;
	  // if (r_ == q.r_)
	  //   {
	  //     q.reader_end_[q.r_] = 0;
	  //     ++q.r_;
	  //   }

	  /* 
	  ** signal q_ that the minimum consumer index cant be r_ anymore,
	  ** (atomic plz)
	  ** in that case, q_ will have to notify if r_ and minimum consumer index were the same
	  */
	  delete ref_counter_;
	}
    }

    // we aint caring about exception safety and Herb Sutter stuff
    // http://stackoverflow.com/questions/7177884/can-i-use-placement-newthis-in-operator
    iterator &operator=(iterator &&copy)
    {
      if (this != &copy)
	{
	  QueueType& q = *q_;
	  this->~iterator();
	  new(this) iterator(q);
	}
      return (*this);
    }

    iterator operator++(int) = delete;

    iterator operator++()
    {
      QueueType& q = *q_;
      this->~iterator();
      new (this) iterator(q);
      return (*this);
    }

    QueueType *q_;
    unsigned r_;
    // make it atomic?
    unsigned *ref_counter_;
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    iterator consume_begin()
    {
      return (iterator(*static_cast<typename Super::Whole::Business*>(this)));
    }

    iterator end()
    {
      return (iterator());
    }

    friend iterator;
  };

};
}

#endif
