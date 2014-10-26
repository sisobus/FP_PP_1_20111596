#ifndef __MEMBER_H__
#define __MEMBER_H__

#include "All.h"
#include "member_manager.h"

#define MAX_BIRTHDAY 10
#define STDMAXBUF 256

class Member {
public:
    string id;
    string password;
    string name;
    string email;
    string address;
    char birthday[MAX_BIRTHDAY+5];
    char memberClass;

public:
    Member(){memset(birthday,0,sizeof(birthday));}
    Member(string newId){updateId(newId);}
    Member(const Member& m);
    Member &operator = (const Member &m);
    bool operator == (const Member &m);
    bool operator != (const Member &m);
    void updateId(const string _id){id = _id;}
    void updatePassword(const string _password){password = _password;}
    void updateName(const string _name){name = _name;}
    void updateEmail(const string _email){email = _email;}
    void updateAddress(const string _address){address = _address;}
    void updateBirthday(const char *_birthday){memcpy(birthday,_birthday,MAX_BIRTHDAY);}
    void updateMemberClass(const char * _memberClass){memcpy(&memberClass,_memberClass,1);}

    friend istream & operator >> (istream &is,Member &m);
    friend ostream & operator << (ostream &is,Member &m);

    bool Pack(IOBuffer& Buffer) const;
    bool Unpack(IOBuffer &Buffer);
};
istream & operator >> (istream &is,Member &m);
ostream & operator << (ostream &is,Member &m);

#endif
