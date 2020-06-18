#ifndef HASHCODE_TIME_HPP
#define HASHCODE_TIME_HPP

#include <time.h>

// Precise wall time clock
class Timer {
  public:
    Timer(clockid_t clockType=CLOCK_REALTIME) : clockType(clockType) {
	    timespec res;
	    clock_getres(clockType, &res);
	    this->resolution = res.tv_sec * 1000000000ll + res.tv_nsec;
	    this->start();
	}

    void start() {
    	clock_gettime(clockType, &(this->startTime));
	}

    double secElapsed() const {
	    timespec temp;
	    clock_gettime(clockType, &temp);

	    int difSec = temp.tv_sec - this->startTime.tv_sec;
	    int difNS = (int)temp.tv_nsec - (int)this->startTime.tv_nsec;

	    return difSec + difNS / 1e9;
	}

    double msElapsed() const {
	    return this->secElapsed() * 1000.0;
	}

  private:
    clockid_t clockType;
    long long resolution;
    timespec startTime;
};

#endif // HASHCODE_TIME_HPP
