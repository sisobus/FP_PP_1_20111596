#include "ProgramRegisterSystem.h"

void RegisterTest() {
    ifstream ifs("listOfRegister.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    DelimFieldBuffer buf('|', STDMAXBUF);
    RecordFile<Register> regFile(buf);
    regFile.Create("fileOfRegister.dat", ios::out | ios::trunc);
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        ifs >> reg;
        
        int res = regFile.Write(reg);
        if ( ~res ) cout << "Write success at " << res << endl;
        else cout << "Write error" << endl;
    }
    regFile.Close();

    vector<Register> ret;
    regFile.Open("fileOfRegister.dat", ios::in);
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        regFile.Read(reg);

        string::size_type offset = 0;
        offset = string(reg.registerId).find("*",offset);
        if ( offset == string::npos ) {
            cout << reg;
            ret.push_back(reg);
        }
        if ( (int)ret.size() == 10 ) break;
    }
    regFile.Close();
}
