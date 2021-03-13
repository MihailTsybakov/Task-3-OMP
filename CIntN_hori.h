#ifndef CINTHORI
#define CINTHORI

#include "CIntN.h"

class CIntN0 : public CIntN
{
public:
    using CIntN::CIntN;
    using CIntN::operator=;
    CIntN0(const CIntN& to_copy) : CIntN(to_copy) {}
    ~CIntN0();

    int output(string FileName) override;

    friend CIntN0 operator+(const CIntN& first, const CIntN& second);
    friend CIntN0 operator-(const CIntN& first, const CIntN& second);
};

#endif // CINTHORI
