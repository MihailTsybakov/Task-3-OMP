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
    cout << "Frankenstein assembled from CIntN0 and CIntN1: ";
    c.print();

    /* ================ Measuring elapsed time ================ */
    /* ============= 18274655 + 28124356 x100000 ==============*/
       
    CIntN0 num_1(8, true, "18274655", "-");
    CIntN0 num_2(8, true, "28124356", "-");
    CIntN0 TMP;

    timer T;
    for (int i = 0; i < 100000; ++i)
    {
        TMP = num_1 + num_2;
    }

    cout << "Seconds elapsed with omp: " << T.section_time() << endl;

    // Seconds Elapsed without OMP: +- 2sec
    // Seconds Elapsed with OMP: +- 4sec :))
    return 0;
}
