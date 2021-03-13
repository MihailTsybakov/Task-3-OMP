#ifndef TEST
#define TEST

#include "CIntN.h"
#include "CIntN_hori.h"
#include "CIntN_vert.h"

#include <sstream>

bool autotest();

class test_error : public exception
{
public:
	int test_number, test_result;
	test_error(int test_number, int test_result)
	{
		this->test_number = test_number;
		this->test_result = test_result;
	}
	const char* what() const noexcept override
	{
		stringstream ss;
		ss << "Failed test " << test_number << ": wrong result is " << test_result << endl;
		return (ss.str()).c_str();
	}
};

#endif // TEST