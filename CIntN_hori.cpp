#include "CIntN_hori.h"
#include "exceptions.cpp"

int CIntN0::output(string FileName) //override
{
    if (update_needed)
    {
        this->update_digits();
        update_needed = false;
    }
    ofstream output_file(FileName);
    if (!output_file.is_open())
    {
        cout << "Error: cannot open " << FileName << endl;
        exit(-1);
    }
    if (sign != true)
    {
        output_file << '-';
    }
    for (int i = 0; i < dimension; ++i)
    {
        output_file << (digits[i]);
    }
    output_file.close();
    return 0;
}

CIntN0::~CIntN0()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

CIntN0 operator+(const CIntN& first, const CIntN& second)
{
    if (first.update_needed) first.update_digits(), first.update_needed = false;
    if (second.update_needed) second.update_digits(), second.update_needed = false;
    try
    {
        if (first.dimension != second.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator+.");
        }
        // "+" + "+"
        if (first.sign == true && second.sign == true)
        {
            vector<int> res_digits = first.pure_plus(first, second);
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "+" + "-" addition
        if (first.sign == true && second.sign == false)
        {
            vector<int> res_digits = first.pure_minus(first, second);
            if (res_digits[first.dimension] == 0)
            {
                CIntN0 res(first.dimension, false, res_digits, first.output_file);
                res.update_needed = true;
                return res;
            }
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "-" + "+"
        if (first.sign == false && second.sign == true)
        {
            vector<int> res_digits = first.pure_minus(second, first);
            if (res_digits[first.dimension] == 0)
            {
                CIntN0 res(first.dimension, false, res_digits, first.output_file);
                res.update_needed = true;
                return res;
            }
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "-" + "-"
        if (first.sign == false && second.sign == false)
        {
            vector<int> res_digits = first.pure_plus(first, second);
            res_digits.push_back(0);
            CIntN0 res(first.dimension, false, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN0 operator-(const CIntN& first, const CIntN& second)
{
    if (first.update_needed) first.update_digits(), first.update_needed = false;
    if (second.update_needed) second.update_digits(), second.update_needed = false;
    try
    {
        if (first.dimension != second.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator -.");
        }
        // "+" - "+" subtraction
        if (first.sign == true && second.sign == true)
        {
            vector<int> res_digits = first.pure_minus(first, second);
            if (res_digits[first.dimension] == 0)
            {
               CIntN0 res(first.dimension, false, res_digits, first.output_file);
               res.update_needed = true;
               return res;
            }
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "+" - "-"
        if (first.sign == true && second.sign == false)
        {
            vector<int> res_digits = first.pure_plus(first, second);
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "-" - "+"
        if (first.sign == false && second.sign == true)
        {
            vector<int> res_digits = first.pure_plus(first, second);
            res_digits.push_back(0);
            CIntN0 res(first.dimension, false, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
        // "-" - "-"
        if (first.sign == false && second.sign == false)
        {
            vector<int> res_digits = first.pure_minus(second, first);
            if (res_digits[first.dimension] == 0)
            {
                CIntN0 res(first.dimension, false, res_digits, first.output_file);
                res.update_needed = true;
                return res;
            }
            CIntN0 res(first.dimension, true, res_digits, first.output_file);
            res.update_needed = true;
            return res;
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}
