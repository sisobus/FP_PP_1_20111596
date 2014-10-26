#include "register_manager.h"

bool RegisterDeleteUpdate::registerSearch(string key) {
    DelimFieldBuffer buf('|',STDMAXBUF);
    RecordFile<Register> registerFile(buf);
    registerFile.Open("fileOfRegister.dat", ios::in);

    ifstream ifs("listOfRegister.txt");
    int n;
    ifs >> n;

    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        registerFile.Read(reg);
        string::size_type offset = 0;
        offset = string(reg.registerId).find("*",offset);
        
		string mRegisterId = string(reg.registerId);
		string mProgramId = string(reg.programId);
		string mNumberOfReRegistered = string(reg.numberOfReRegistered);

        /*string mRegisterId (reg.registerId,MAX_REGISTER_ID);
        string mProgramId (reg.programId,MAX_PROGRAM_ID);
        string mNumberOfReRegistered (reg.numberOfReRegistered,MAX_NUMBER_OF_RE_REGISTER);*/

        bool mask = key == mRegisterId |
                    key == mProgramId |
                    key == reg.memberId |
                    key == mNumberOfReRegistered;
        if ( offset == string::npos && mask ) {
            cout << reg;
            return true;
        }
    }
    cout << "There is no " << key << endl;
    return false;
}

void RegisterDeleteUpdate::registerInsert() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	cin >> s;
    v.push_back(s);
    if ( registerSearch(s) ) {
        cout << "error : There is same ID";
        return ;
    } else {
        cout << "Input new program ID : ";
    //    scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new member ID ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);
        
        cout << "Input new Number Of Re-registered : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfRegister.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfRegister.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void RegisterDeleteUpdate::registerUpdate() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	cin >> s;
    v.push_back(s);
    if ( !registerSearch(s) ) {
        cout << "error : There is not ID" << endl;
        return ;
    } else {
        registerDelete(s,false);

        cout << "Input new program ID : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new member ID : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);
        
        cout << "Input new Number Of Re-Registered : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfRegister.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfRegister.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void RegisterDeleteUpdate::registerDelete(string key,bool isMemberDelete) {
    ifstream ifs("listOfRegister.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    DelimFieldBuffer buf('|', STDMAXBUF);
    RecordFile<Register> registerFile(buf);
    registerFile.Create("fileOfRegister.dat", ios::out | ios::trunc);
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        ifs >> reg;
        
        int res = registerFile.Write(reg);
        if ( ~res ) cout << "Write success at " << res << endl;
        else cout << "Write error" << endl;
    }
    registerFile.Close();

    vector<Register> ret;
    registerFile.Open("fileOfRegister.dat", ios::in);
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        registerFile.Read(reg);

        if ( isMemberDelete ) {
            if ( reg.memberId == key ) {
                ret.push_back(reg);
            } else {
                reg.memberId = "*" + reg.memberId;
                ret.push_back(reg);
            }
        } else {
            if ( reg.registerId != key ) {
                ret.push_back(reg);
            } else {
				string now = "*" + string(reg.registerId);
				sprintf(reg.registerId,"%s",now.c_str());
                //sprintf(reg.registerId,"*%s",reg.registerId);
                ret.push_back(reg);
            }
        }
    }
    registerFile.Close();

    FILE *fp = fopen("listOfRegister.txt","w");
    fprintf(fp,"%d\n",(int)ret.size());
    for ( int i = 0 ; i < (int)ret.size() ; i++ ) {
		string mRegisterId (ret[i].registerId,MAX_REGISTER_ID);
        string mProgramId (ret[i].programId,MAX_PROGRAM_ID);
        string mNumberOfReRegistered (ret[i].numberOfReRegistered,MAX_NUMBER_OF_RE_REGISTER);

        string now = mRegisterId + "|" + mProgramId + "|" +
                     ret[i].memberId + "|" + mNumberOfReRegistered;
        fprintf(fp,"%s\n",now.c_str());
    }
    fclose(fp);
}

void RegisterDeleteUpdate::writeDataFile() {
	ifstream ifs("listOfRegister.txt");
    int n;

    ifs >> n;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    DelimFieldBuffer buf('|', STDMAXBUF);
    RecordFile<Register> registerFile(buf);
    registerFile.Create("fileOfRegister.dat", ios::out | ios::trunc);
    for ( int i = 0 ; i < n ; i++ ) {
        Register reg;
        ifs >> reg;
        
        int res = registerFile.Write(reg);
        if ( ~res ) cout << "Write success at " << res << endl;
        else cout << "Write error" << endl;
    }
    registerFile.Close();
}