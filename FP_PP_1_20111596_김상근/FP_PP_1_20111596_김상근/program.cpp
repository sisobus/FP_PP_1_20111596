#include "program.h"

Program::Program(const Program &p) {
    updateId(p.id);
    updateTitle(p.title);
    updateStartTime(p.startTime);
    updateInstructorName(p.instructorName);
    updateDuration(&p.duration);
}
Program &Program::operator = (const Program &p) {
    updateId(p.id);
    updateTitle(p.title);
    updateStartTime(p.startTime);
    updateInstructorName(p.instructorName);
    updateDuration(&p.duration);

    return *this;
}
bool Program::operator == (const Program &p) {
    return !memcpy(id,p.id,MAX_ID);
}
bool Program::operator != (const Program &p) {
    return memcpy(id,p.id,MAX_ID);
}
istream & operator >> (istream &is, Program &p) {
    string s;
    is.exceptions(istream::failbit | istream::badbit);

    try {
        getline(is,s);
    } catch (istream::failure e) {
        return is;
    }

    istringstream iss(s);
    string token;

    getline(iss, token, '|');
    p.updateId(token.data());
    getline(iss, token, '|');
    p.updateTitle(token);
    getline(iss, token, '|');
    p.updateStartTime(token.data());
    getline(iss, token, '|');
    p.updateInstructorName(token);
    getline(iss, token, '|');
    p.updateDuration(token.data());

    return is;
}
ostream & operator << (ostream &os, Program &p) {
    string mId (p.id, MAX_ID);
    string mStartTime (p.startTime, MAX_START_TIME);
    string mDuration (&p.duration, MAX_DURATION);

    os << "ID : " << p.id << endl;
    os << "TITLE : " << p.title << endl;
    os << "START TIME : " << p.startTime << endl;
    os << "INSTRUCTOR NAME : " << p.instructorName << endl;
    os << "DURATION : " << p.duration << endl;

    return os; 
}
bool Program::Pack(IOBuffer &Buffer) const {
    int numBytes;

    Buffer.Clear();

    string mId (id, MAX_ID);
    string mStartTime (startTime, MAX_START_TIME);
    string mDuration (&duration, MAX_DURATION);

    numBytes = Buffer.Pack(mId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(title.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mStartTime.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(instructorName.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mDuration.c_str());
    if ( numBytes == -1 ) return false;

    return true;
}
bool Program::Unpack(IOBuffer &Buffer) {
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(id, MAX_ID);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    title = buf;
    numBytes = Buffer.Unpack (startTime, MAX_START_TIME);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    instructorName = buf;
    numBytes = Buffer.Unpack (&duration,MAX_DURATION);
    if ( numBytes == -1 ) return false;

    return true;
}
