#include "ProgramRegisterSystem.h"

vector<Member> showMember() {
    ifstream ifs("listOfMember.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Member> ret;
    for ( int i = 0 ; i < n ; i++ ) {
        Member member;
        ifs >> member;

        string::size_type offset = 0;
        offset = member.id.find("*",offset);
        if ( offset == string::npos ) {
            cout << member;
            ret.push_back(member);
        }
        if ( (int)ret.size() == 10 ) return ret;
    }
    return ret;
}
