#include "CIntN.h"
#include "Create.h"
#include "Autotest.h"
#include "Timer.h"
#include <chrono>

int main(int argc, char* argv[])
{
    try
    {
        autotest();
        cout << "Autotest passed." << endl;
    }
    catch (const test_error& exc)
    {
        cout << "Failed test " << exc.test_number << ": wrong result is " << exc.test_result << endl;
        cout << "Autotest Failed!" << endl;
        exit(-1);
    }
    catch (...)
    {
        cout << "Unknown exception caught during autotest. Exiting." << endl;
        exit(-1);
    }

    string input_filename = "Input.txt";
    ifstream input_file(input_filename);

    if (!input_file.is_open())
    {
        cout << "Error: cannot open " << input_filename << endl;
        exit(-1);
    }

    vector<CIntN*> CINT_vector;
    map<string, CINT_Factory*> factories;
    factories["Hori"] = new Hori_Factory;
    factories["Vert"] = new Vert_Factory;

    string tmp_string;

    while (getline(input_file, tmp_string))
    {
        CINT_vector.push_back(Create_CINTN(tmp_string, factories));
    }
    input_file.close();
    /* ================ Outputiing ================ */

    for (vector<CIntN*>::iterator it = CINT_vector.begin(); it != CINT_vector.end(); ++it)
    {
        (*it)->output((*it)->out_file());
        delete (*it);
    }
    CIntN0 a(3, true, "543", "-");
    CIntN1 b(3, false, "111", "-");
    CIntN0 c = a-b;
    //cout << "Frankenstein assembled from CIntN0 and CIntN1: ";
    c.print();

    /* ================ Measuring elapsed time ================ */
    /* ============= 18274655 + 28124356 x100000 ==============*/
       
    int num_dimensions = 10e5;

    stringstream digits_1, digits_2, tmp;
    for (int i = 0; i < num_dimensions; ++i) // Gens random numbers
    {
        digits_1 << rand() % 10;
        digits_2 << rand() % 10;
        tmp << 0;
    }

    CIntN0 num_1(num_dimensions, true, digits_1.str(), "-");
    CIntN0 num_2(num_dimensions, true, digits_2.str(), "-");

    CIntN0 TMP(num_dimensions, true, tmp.str(), "-");

    auto start = std::chrono::system_clock::now();
    // Evaluation here
    TMP = num_1 + num_2;
    auto end = std::chrono::system_clock::now();
    int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    cout << "Milliseconds elapsed: " << elapsed_ms << endl;
    

    // Seconds Elapsed without OMP: +- 2sec
    // Seconds Elapsed with OMP: +- 5sec :) for "+" in (*)
    // Seconds Elapsed with OMP: +- 2.5 sec for "-" in (*)
    return 0;
}
