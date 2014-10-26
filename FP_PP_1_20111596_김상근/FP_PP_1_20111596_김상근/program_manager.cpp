#include "program_manager.h"

bool ProgramDeleteUpdate::programSearch(string key) {
    DelimFieldBuffer buf('|',STDMAXBUF);
    RecordFile<Program> programFile(buf);
    programFile.Open("fileOfProgram.dat", ios::in);

    ifstream ifs("listOfProgram.txt");
    int n;
    ifs >> n;

    for ( int i = 0 ; i < n ; i++ ) {
        Program program;
        programFile.Read(program);
        string::size_type offset = 0;
        offset = string(program.id).find("*",offset);
        
		string mId = string(program.id);
		string mStartTime = string(program.startTime);
		string mDuration = "" + program.duration;
        /*string mId (program.id,MAX_PROGRAM_ID);
        string mStartTime (program.startTime,MAX_START_TIME);
        string mDuration (&program.duration,MAX_DURATION);*/

        bool mask = key == mId |
                    key == program.title |
                    key == mStartTime |
                    key == program.instructorName |
                    key == mDuration;
        if ( offset == string::npos && mask ) {
            cout << program;
            return true;
        }
    }
    cout << "There is no " << key << endl;
    return false;
}

void ProgramDeleteUpdate::programInsert() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	cin >> s;
    v.push_back(s);
    if ( programSearch(s) ) {
        cout << "error : There is same ID";
        return ;
    } else {
        cout << "Input new title : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new start time : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);
        
        cout << "Input new instructor name : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new duration : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfProgram.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfProgram.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void ProgramDeleteUpdate::programUpdate() {
    vector<string> v;
    char s[1<<8];

    cout << "Input new id : "; 
    //scanf("%s",s);
	cin >> s;
    v.push_back(s);
    if ( !programSearch(s) ) {
        cout << "error : There is not ID" << endl;
        return ;
    } else {
        programDelete(s);

        cout << "Input new title : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new start time : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);
        
        cout << "Input new instructor name : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        cout << "Input new duration : ";
        //scanf("%s",s);
		cin >> s;
        v.push_back(s);

        string res = "";
        for ( int i = 0 ; i < (int)v.size() ; i++ ) {
            res += v[i];
            res += (i==(int)v.size()-1)?"":"|";
        }
        int n;
        FILE *fp = fopen("listOfProgram.txt","r");
        fscanf(fp,"%d\n",&n);
        vector<string> prev;
        for ( int i = 0 ; i < n ; i++ ) {
            fgets(s,MAX_READ_LINE_LENGTH,fp);

			while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
			s[strlen(s)-1] = 0;
            prev.push_back(s);
        }
        fclose(fp);
        fp = fopen("listOfProgram.txt","w");
        n++;
        fprintf(fp,"%d\n",n);
        for ( int i = 0 ; i < (int)prev.size() ; i++ ) 
            fprintf(fp,"%s\n",prev[i].c_str());
        fprintf(fp,"%s\n",res.c_str());
        fclose(fp);
    }
	writeDataFile();
}
void ProgramDeleteUpdate::programDelete(string key) {
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

        if ( program.id != key ) {
            ret.push_back(program);
        } else {
            sprintf(program.id,"*%s",program.id);
            ret.push_back(program);
        }
    }
    programFile.Close();

    FILE *fp = fopen("listOfProgram.txt","w");
    fprintf(fp,"%d\n",(int)ret.size());
    for ( int i = 0 ; i < (int)ret.size() ; i++ ) {
        string now = string(ret[i].id) + "|" + ret[i].title + "|" +
                     string(ret[i].startTime) + "|" + ret[i].instructorName + "|" +
                     ret[i].duration;
        fprintf(fp,"%s\n",now.c_str());
    }
    fclose(fp);
}

void ProgramDeleteUpdate::writeDataFile() {
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
}