#include "CIntN.h"
#include "Create.h"
#include "Autotest.h"
#include "Timer.h"
#include <fstream>

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
    cout << "Outputting done." << endl;
    srand(time(0));

    /* ================ Time Measurement ================ */
    int num_dimension = 250'000'000;

    cout << "Generating numbers with length " << num_dimension << "..." << endl;
    vector<int> digits_1, digits_2;
    digits_1.resize(num_dimension);
    digits_2.resize(num_dimension);
    digits_1[0] = 1;
    digits_2[0] = 2;
    for (int i = 1; i < num_dimension; ++i)
    {
        digits_1[i] = rand() % 10;
        digits_2[i] = rand() % 10;
    }
    CIntN0 Num_1(num_dimension, true, digits_1, "-");
    CIntN0 Num_2(num_dimension, true, digits_2, "-");

    cout << "Checkpoint: numbers generated." << endl;

    Num_1 + Num_2;
    
    // 250kk Release: 20.8 s no omp
    // 250kk Release: 13.5 s omp
    return 0;
}
