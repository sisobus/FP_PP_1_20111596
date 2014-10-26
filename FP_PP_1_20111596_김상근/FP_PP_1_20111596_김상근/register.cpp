#include "register.h"

Register::Register(const Register &r) {
    updateRegisterId(r.registerId);
    updateProgramId(r.programId);
    updateMemberId(r.memberId);
    updateNumberOfReRegisterd(r.numberOfReRegistered);
}
Register &Register::operator = (const Register &r ){
    updateRegisterId(r.registerId);
    updateProgramId(r.programId);
    updateMemberId(r.memberId);
    updateNumberOfReRegisterd(r.numberOfReRegistered);

    return *this;
}
bool Register::operator == (const Register &r) {
    return !memcmp(registerId, r.registerId, MAX_REGISTER_ID);
}
bool Register::operator != (const Register &r) {
    return memcmp(registerId, r.registerId, MAX_REGISTER_ID);
}
istream & operator >> (istream &is, Register &r) {
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
    r.updateRegisterId(token.data());
    getline(iss, token, '|');
    r.updateProgramId(token.data());
    getline(iss, token, '|');
    r.updateMemberId(token);
    getline(iss, token, '|');
    r.updateNumberOfReRegisterd(token.data());

    return is;
}
ostream & operator << (ostream &os, Register &r) {
    string mRegisterId(r.registerId, MAX_REGISTER_ID);
    string mProgramId(r.programId, MAX_PROGRAM_ID);
    string mNumberOfReRegistered(r.numberOfReRegistered, MAX_NUMBER_OF_RE_REGISTER);

    os << "REGISTER ID : " << mRegisterId << endl;
    os << "PROGRAM ID : " << mProgramId << endl;
    os << "MEMBER ID : " << r.memberId << endl;
    os << "NUMBER OF RE REGISTERED : " << mNumberOfReRegistered << endl;

    return os; 
}
bool Register::Pack(IOBuffer &Buffer) const {
    int numBytes;

    Buffer.Clear();

    string mRegisterId(registerId, MAX_REGISTER_ID);
    string mProgramId(programId, MAX_PROGRAM_ID);
    string mNumberOfReRegistered(numberOfReRegistered, MAX_NUMBER_OF_RE_REGISTER);

    numBytes = Buffer.Pack(mRegisterId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mProgramId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(memberId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mNumberOfReRegistered.c_str());
    if ( numBytes == -1 ) return false;

    return true;
}
bool Register::Unpack(IOBuffer &Buffer) {
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(registerId, MAX_REGISTER_ID);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack(programId, MAX_PROGRAM_ID);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    memberId = buf;
    numBytes = Buffer.Unpack (numberOfReRegistered,MAX_NUMBER_OF_RE_REGISTER);
    if ( numBytes == -1 ) return false;

    return true;
}
