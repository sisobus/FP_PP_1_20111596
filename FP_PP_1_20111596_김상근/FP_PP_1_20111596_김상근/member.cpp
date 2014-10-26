#include "member.h"
Member::Member(const Member &m) {
    updateId(m.id);
    updatePassword(m.password);
    updateName(m.name);
    updateEmail(m.email);
    updateAddress(m.address);
    updateBirthday(m.birthday);
    updateMemberClass(&m.memberClass);
}
Member &Member::operator = (const Member &m) {
    updateId(m.id);
    updatePassword(m.password);
    updateName(m.name);
    updateEmail(m.email);
    updateAddress(m.address);
    updateBirthday(m.birthday);
    updateMemberClass(&m.memberClass);

    return *this;
}
bool Member::operator == (const Member &m) {
    return id == m.id;
}
bool Member::operator != (const Member &m) {
    return id != m.id;
}
istream & operator >> (istream &is, Member &m) {
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
    m.updateId(token);
    getline(iss, token, '|');
    m.updatePassword(token);
    getline(iss, token, '|');
    m.updateName(token);
    getline(iss, token, '|');
    m.updateEmail(token);
    getline(iss, token, '|');
    m.updateAddress(token);
    getline(iss, token, '|');
    m.updateBirthday(token.data());
    getline(iss, token, '|');
    m.updateMemberClass(token.data());

    return is;
}

ostream & operator << (ostream &os, Member &m) {
    string mBirthday (m.birthday, MAX_BIRTHDAY);
    string mMemberClass (&m.memberClass, 1);

    os << "ID : " << m.id << endl;
    os << "PASSWORD : " << m.password << endl;
    os << "NAME : " << m.name << endl;
    os << "E-MAIL : " << m.email << endl;
    os << "ADDRESS : " << m.address << endl;
    os << "BIRTHDAY : " << mBirthday << endl;
    os << "CLASS : " << mMemberClass << endl;
    
    return os; 
}
bool Member::Pack(IOBuffer &Buffer) const {
    int numBytes;

    Buffer.Clear();

    string mBirthday (birthday, MAX_BIRTHDAY);
    string mMemberClass (&memberClass, 1);

    numBytes = Buffer.Pack(id.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(password.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(name.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(email.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(address.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mBirthday.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mMemberClass.c_str());
    if ( numBytes == -1 ) return false;
    return true;
}
bool Member::Unpack(IOBuffer &Buffer) {
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    id = buf;
    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    password = buf;
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    name = buf; 
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    email = buf;
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    address = buf; 
    numBytes = Buffer.Unpack(birthday, MAX_BIRTHDAY);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack(&memberClass, 1);
    if ( numBytes == -1 ) return false;

    return true;
}
