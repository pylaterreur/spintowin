#ifndef QUEUE_HPP_
# define QUEUE_HPP_

template <typename T>
struct Queue
{
  typedef std::shared_ptr<T> value_type;

  Queue() : i_(0), r_(0)
  {}

  ~Queue()
  {
    for (auto &p : buffer_)
      {
	p = value_type();
      }
  }

  void push_back(value_type data)
  {
    // increment_insert();
    buffer_[i_ & (Size - 1)] = data;
  }

protected:
  inline unsigned increment_insert()
  {
    i_ = (i_ + 1) & (Size - 1);
  }

  // we dont care about exceptions, on fait pas de top() + pop()
  value_type pop()
  {
    value_type ret;

    ret = buffer_[r_];
    //    buffer_[i_] = value_type();
    r_ = (r_ + 1) & (Size - 1);
    return (ret);
  }

protected:
  static const unsigned Size = 1 << 3;
  value_type	buffer_[Size];
  unsigned	i_, r_;
};

#endif
