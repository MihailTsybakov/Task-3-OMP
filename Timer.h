#ifndef TIMER
#define TIMER

#include <ctime>

class timer
{
private:
	clock_t stime;
public:
	timer()
	{
		stime = clock();
	}
	double section_time()
	{
		return static_cast<double>(clock() - stime) / 1000;
	}
};

#endif //TIMER