#include "ProgramRegisterSystem.h"

void MemberTest() {
    ifstream ifs("listOfMember.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    DelimFieldBuffer buf('|', STDMAXBUF);
    RecordFile<Member> memberFile(buf);
    memberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
    for ( int i = 0 ; i < n ; i++ ) {
        Member member;
        ifs >> member;
        
        int res = memberFile.Write(member);
        if ( ~res ) cout << "Write success at " << res << endl;
        else cout << "Write error" << endl;
    }
    memberFile.Close();

    vector<Member> ret;
    memberFile.Open("fileOfMember.dat", ios::in);
    for ( int i = 0 ; i < n ; i++ ) {
        Member member;
        memberFile.Read(member);

        string::size_type offset = 0;
        offset = member.id.find("*",offset);
        if ( offset == string::npos ) {
            cout << member;
            ret.push_back(member);
        }
        if ( (int)ret.size() == 10 ) break;
    }
    memberFile.Close();
}
