#include "member_manager.h"

bool MemberDeleteUpdate::memberSearch(string key) {
    DelimFieldBuffer buf('|',STDMAXBUF);
    RecordFile<Member> memberFile(buf);
    memberFile.Open("fileOfMember.dat", ios::in);

    ifstream ifs("listOfMember.txt");
    int n;
    ifs >> n;

    for ( int i = 0 ; i < n ; i++ ) {
        Member member;
        memberFile.Read(member);
        string::size_type offset = 0;
        offset = member.id.find("*",offset);
        
        string mBirthday(member.birthday,MAX_BIRTHDAY);
        string mMemberClass(&member.memberClass,1);

        bool mask = key == member.id |
                    key == member.password |
                    key == member.name |
                    key == member.email |
                    key == member.address |
                    key == mBirthday |
                    key == mMemberClass;
        if ( offset == string::npos && mask ) {
            cout << member;
            return true;
        }
    }
    cout << "There is no " << key << endl;
    return false;
}

void MemberDeleteUpdate::memberInsert() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	//getline(cin,s);
	cin >> s;
    v.push_back(s);
    if ( memberSearch(s) ) {
        cout << "error : There is same ID";
        return ;
    } else {
        cout << "Input new password : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new first name : ";
        //getline(cin,string(s));
		string _name = "";
		cin >> _name;

		cout << "Input new last name : ";
		cin >> s;
		_name = _name + " " + string(s);
        v.push_back(_name);
        
        cout << "Input new email : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new address : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new birthday : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new class : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfMember.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            //fscanf(fp,"%[^\r]\r",s);
			fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfMember.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void MemberDeleteUpdate::memberUpdate() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	cin >> s;
    v.push_back(s);
    if ( !memberSearch(s) ) {
        cout << "error : There is not ID" << endl;
        return ;
    } else {
        memberDelete(s);

        cout << "Input new password : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new first name : ";
        //getline(cin,string(s));
		string _name = "";
		cin >> _name;

		cout << "Input new last name : ";
		cin >> s;
		_name = _name + " " + string(s);
        v.push_back(_name);
        
        cout << "Input new email : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new address : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new birthday : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new class : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfMember.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfMember.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void MemberDeleteUpdate::memberDelete(string key) {
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

        string mBirthday (member.birthday,MAX_BIRTHDAY);
        if ( member.id != key ) {
            ret.push_back(member);
        } else {
            member.id = "*" + member.id;
            ret.push_back(member);
            
            RegisterDeleteUpdate now;
            now.registerDelete(key,true);
        }
    }
    memberFile.Close();

    FILE *fp = fopen("listOfMember.txt","w");
    fprintf(fp,"%d\n",(int)ret.size());
    for ( int i = 0 ; i < (int)ret.size() ; i++ ) {
		string mBirthday (ret[i].birthday, MAX_BIRTHDAY);
        string now = ret[i].id + "|" + ret[i].password + "|" +
                     ret[i].name + "|" + ret[i].email + "|" + 
                     ret[i].address + "|" + mBirthday + "|" +
                     ret[i].memberClass;
        fprintf(fp,"%s\n",now.c_str());
    }
    fclose(fp);
}

void MemberDeleteUpdate::writeDataFile() {
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
}