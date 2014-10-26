#include "ProgramRegisterSystem.h"

vector<Program> showProgram() {
    ifstream ifs("listOfProgram.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Program> ret;
    for ( int i = 0 ; i < n ; i++ ) {
        Program program;
        ifs >> program;

        string::size_type offset = 0;
        offset = string(program.id).find("*",offset);
        if ( offset == string::npos ) {
            cout << program;
            ret.push_back(program);
        }
        if ( (int)ret.size() == 10 ) return ret;
    }
    return ret;
}
