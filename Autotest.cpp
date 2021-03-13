#include "Autotest.h"

bool autotest()
{
    bool pass_flag = true;

    CIntN0 Number_1(4, true, "1438", "-");
    CIntN0 Number_2(4, true, "2873", "-");
    CIntN0 Number_3(4, false, "1332", "-"); // -1332
    CIntN0 Number_4(4, false, "4312", "-"); // -4312

    // 1) "+" + "+", 4311
    CIntN0 Result = Number_1 + Number_2;
    if (int(Result) != 4311) throw test_error(1, Result.getabs());


    // 2) "+" - "+"
    Result = Number_1 - Number_2; // -1435
    if (int(Result) != -1435) throw test_error(2, Result.getabs());


    Result = Number_2 - Number_1; // 1435
    if (int(Result) != 1435) throw test_error(3, Result.getabs());



    // 3) "+" + "-"
    Result = Number_1 + Number_3; // 0106
    if (int(Result) != 106) throw test_error(4, Result.getabs());



    Result = Number_1 + Number_4; // -2874
    if (int(Result) != -2874) throw test_error(5, Result.getabs());



    // 4) "-" + "+"
    Result = Number_4 + Number_2; //-1439
    if (int(Result) != -1439) throw test_error(6, Result.getabs());


    /// ******** - ********
    // 5) "-" - "-"
    Result = Number_3 - Number_4; // 2980
    if (int(Result) != 2980) throw test_error(7, Result.getabs());

    Result = Number_4 - Number_3; // -2980
    if (int(Result) != -2980) throw test_error(8, Result.getabs());

    // 6) "+" - "-"
    Result = Number_1 - Number_4; // 5750
    if (int(Result) != 5750) throw test_error(9, Result.getabs());

    // 7) "-" - "+"
    Result = Number_4 - Number_1; // -5750
    if (int(Result) != -5750) throw test_error(10, Result.getabs());

    //8 ) "-" + "-"
    Result = Number_3 + Number_4; // -5644
    if (int(Result) != -5644) throw test_error(11, Result.getabs());


    return pass_flag;
}
