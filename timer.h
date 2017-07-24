#ifndef TIMER_HH_
#define TIMER_HH_

#include <chrono>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

struct scoped_timer {
  /* Init the timer: get the current time */
  scoped_timer(double& s) : seconds(s), t0(steady_clock::now()) {}

  /* set time diff between now and start in the double ref (seconds) */
  /* use maximal precision (nanoseconds) for counts                  */
  /* hint: seconds = double(nanoseconds count) / 1e9 */
  ~scoped_timer() 
  {
    seconds = std::chrono::duration_cast<std::chrono::microseconds>
    (steady_clock::now() - t0).count();
    std::cout << "scope took  " << seconds << " microseconds \n";
  }
  double & seconds;
  steady_clock::time_point      t0;
};

#endif
