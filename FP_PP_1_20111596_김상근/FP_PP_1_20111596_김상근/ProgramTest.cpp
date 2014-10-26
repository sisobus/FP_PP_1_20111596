#include "ProgramRegisterSystem.h"

void ProgramTest() {
    ifstream ifs("listOfProgram.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    DelimFieldBuffer buf('|', STDMAXBUF);
    RecordFile<Program> programFile(buf);
    programFile.Create("fileOfProgram.dat", ios::out | ios::trunc);
    for ( int i = 0 ; i < n ; i++ ) {
        Program program;
        ifs >> program;
        
        int res = programFile.Write(program);
        if ( ~res ) cout << "Write success at " << res << endl;
        else cout << "Write error" << endl;
    }
    programFile.Close();

    vector<Program> ret;
    programFile.Open("fileOfProgram.dat", ios::in);
    for ( int i = 0 ; i < n ; i++ ) {
        Program program;
        programFile.Read(program);

        string::size_type offset = 0;
        offset = string(program.id).find("*",offset);
        if ( offset == string::npos ) {
            cout << program;
            ret.push_back(program);
        }
        if ( (int)ret.size() == 10 ) break;
    }
    programFile.Close();
}
