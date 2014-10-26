#include "ProgramRegisterSystem.h"

vector<Register> showRegister() {
    ifstream ifs("listOfRegister.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Register> ret;
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        ifs >> reg;

        string::size_type offset = 0;
        offset = string(reg.registerId).find("*",offset);
        if ( offset == string::npos ) {
            cout << reg;
            ret.push_back(reg);
        }
        if ( (int)ret.size() == 10 ) return ret;
    }
    return ret;
}
