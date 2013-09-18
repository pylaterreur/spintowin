#include <iostream>
#include <mutex>
#include <boost/thread.hpp>
#include <thread>
#include <boost/atomic.hpp>
#include <atomic>
#include <list>
#include <sstream>

namespace thr
{
  using namespace std;
}

using std::atomic;

const unsigned NbPhilos = 4;
static atomic<int> thr_counter(0);

template <typename T>
static void print(T&& t)
{
  static std::mutex m;
  std::lock_guard<std::mutex> l(m);

  std::cout << t;
}

struct Philo
{
  Philo() : right_philo_(this), left_fork_not_mine_(false), left_fork_clean_(false)
  {}

  Philo(Philo * const right_philo) : right_philo_(right_philo) : left_fork_not_mine_(false), left_fork_clean_(false)
  {
    assert(right_philo != this);
    Philo *p = right_philo;
    while (p->right_philo_ != right_philo_)
      p = p->right_philo_;
    p->right_philo_ = this;
  }

  // didn't do anything about the forks
  // ~Philo()
  // {
  //   if (!right_philo_)
  //     return ;
  //   Philo *p = right_philo_;
  //   while (p->right_philo_ != this)
  //     p->right_philo_;
  //   p->right_philo_ = this->right_philo_;
  // }

  Philo(const Philo &) = delete;

  Philo(Philo &&rval) = default;

  void operator()()
  {
    while (1)
      {
	// std::ostringstream str;
	// unsigned tmp = thr_counter;
	// str << "lolilol " << tmp;
	while (thr_counter != NbPhilos)
	  boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	
	right_philo_->left_fork_;

	//    boost::thread::get_id
	// str << " Eating\n";
	print(str.str());
      }

  }

private:
  // should do something with bitwise stuff, eg 0b10 for clean, 0b01 for "not mine" ??
  atomic<bool> left_fork_clean_;
  atomic<bool> left_fork_not_mine_;
  Philo *right_philo_;

  void wait_fork()
  {
    // expecting 
    // left_fork_clean_;
  }
};

template <typename Super>
struct ThreadMe : Super
{
  template <typename... T>
  ThreadMe(T&&... args) : Super(args...), thr_(&f, this)
  {
    ++thr_counter;
  }

  ~ThreadMe()
  {
    thr_.join();
  }

private:
  static void f(Super *p)
  {
    // boost::this_thread::at_thread_exit([](){
    // 	unsigned tmp = thr_counter;
    // 	print(tmp);
    // 	--thr_counter;
    //   });
    (*p)();
  }
  std::thread thr_;
};

int main()
{
  std::list<ThreadMe<Philo> > v(1);

  for (unsigned i = 0; i < NbPhilos - 1; ++i)
    v.emplace_front(&v.front());
}
