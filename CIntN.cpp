#include "CIntN.h"
#include "exceptions.cpp"

CIntN::CIntN()
{
    sign = true;
    dimension = 0;
    digits = nullptr;
}
CIntN::~CIntN()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

CIntN::CIntN(int dimension, bool sign, string digits_string, string output_file)
{

    this->sign = sign;
    this->dimension = dimension;
    this->output_file = output_file;
    if (static_cast<size_t>(dimension) != digits_string.size())
    {
        cout << "Error: dimension mismatch." << endl;
        cout << "Debug: >" << digits_string << "<" << endl;
        cout << dimension << " x " << digits_string.size() << endl;
        exit(-1);
    }
    digits = new int[dimension];
    for (size_t i = 0; i < digits_string.size(); ++i)
    {
        char symbol = static_cast<char>(digits_string[i]);
        if (symbol < 48 || symbol > 57)
        {
            cout << "Error: non-numeric character found." << endl;
            cout << "Digits string is: " << digits_string << endl;
            exit(-1);
        }
        digits[i] = symbol - 48;
    }
}

CIntN::CIntN(int dimension, bool sign, vector<int> digits_vect, string output_file)
{
    this->sign = sign;
    this->dimension = dimension;
    this->output_file = output_file;
    digits = new int[dimension];
    for (size_t i = 0; i < dimension; ++i)
    {
        digits[i] = digits_vect[i];
    }
}

CIntN::CIntN(const CIntN& to_copy)
{
    sign = to_copy.sign;
    dimension = to_copy.dimension;
    digits = new int[dimension];
    for (int i = 0; i < dimension; ++i)
    {
        digits[i] = to_copy.digits[i];
    }
}

CIntN& CIntN::operator=(const CIntN& equals_to)
{
    if (dimension != 0)
    {
        delete[] digits;
    }
    dimension = equals_to.dimension;
    digits = new int[dimension];
    sign = equals_to.sign;
    for (int i = 0; i < dimension; ++i)
    {
        digits[i] = equals_to.digits[i];
    }
    return *this;
}

string CIntN::out_file() const noexcept
{
    return output_file;
}

void CIntN::print() const noexcept
{
    if (dimension == 0)
    {
        return;
    }
    if (sign != true)
    {
        cout << "-";
    }
    for (int i = 0; i < dimension; ++i)
    {
        cout << digits[i];
    }
    cout << endl;
}

int CIntN::getabs() const noexcept
{
    int num = 0;
    for (int i = dimension - 1; i >= 0; --i)
    {
        num += digits[i]*pow(10, dimension-1-i);
    }
    return num;
}

CIntN::operator int() const noexcept
{
    int num = 0;
    for (int i = dimension - 1; i >= 0; --i)
    {
        num += digits[i]*pow(10, dimension-1-i);
    }
    sign == true? num *= 1 : num *= -1;
    return num;
}

vector<int> CIntN::pure_plus(const CIntN& num_1, const CIntN& num_2) const // Parallel mod. 1
{
    vector<int> res_digits;
    res_digits.resize(num_1.dimension);

    /* ================ Time =================== */
    auto start = std::chrono::system_clock::now();

#pragma omp parallel for
    for (int i = 0; i < num_1.dimension; ++i)
    {
        res_digits[i] = num_1.digits[i] + num_2.digits[i];
    }
    for (int i = num_1.dimension - 1; i >= 0; --i)
    {
        if (res_digits[i] >= 10)
        {
            if (i == 0)
            {
                cout << "Error: too big numbers..." << endl;
                exit(-1);
            }
            res_digits[i] -= 10;
            res_digits[i - 1] += 1;
        }
    }

    auto end = std::chrono::system_clock::now();
    /* ================ Time =================== */

    int elapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    cout << "Pure plus elapsed: " << elapsed << "ms" << endl;

    return res_digits;
}

vector<int> CIntN::pure_minus(const CIntN& num_1, const CIntN& num_2) const // Parallel modification
{
    vector<int> res_digits;
    res_digits.resize(num_1.dimension);
    bool sign = true;

    /* ================ Time =================== */
    auto start = std::chrono::system_clock::now();

    if (num_1.getabs() >= num_2.getabs())
    {
#pragma omp parallel for
        for (int i = 0; i < num_1.dimension; ++i)
        {
            res_digits[i] = num_1.digits[i] - num_2.digits[i];
        }
    }
    else
    {
        sign = false;
#pragma omp parallel for
        for (int i = 0; i < num_1.dimension; ++i)
        {
            res_digits[i] = num_2.digits[i] - num_1.digits[i];
        }
    }
    for (int i = 0; i < num_1.dimension; ++i)
    {
        if (res_digits[i] < 0)
        {
            int j = i - 1;
            while (res_digits[j] == 0) j--;
            res_digits[j] -= 1, j++;
            while (j < i) res_digits[j] = 9, j++;
            res_digits[i] += 10;
        }
    }

    auto end = std::chrono::system_clock::now();
    /* ================ Time =================== */

    int elapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    cout << "Pure plus elapsed: " << elapsed << "ms" << endl;

    if (!sign) res_digits.push_back(-1);

    return res_digits;
}

