#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "All.h"

#define STDMAXBUF 256
#define MAX_REGISTER_ID 12
#define MAX_PROGRAM_ID 8
#define MAX_NUMBER_OF_RE_REGISTER 2

class Register {
    public:
        char registerId[MAX_REGISTER_ID+5];
        char programId[MAX_PROGRAM_ID+5];
        string memberId;
        char numberOfReRegistered[MAX_NUMBER_OF_RE_REGISTER+5];

    public:
        Register(){
			memset(registerId,0,sizeof(registerId));
			memset(programId,0,sizeof(programId));
			memset(numberOfReRegistered,0,sizeof(numberOfReRegistered));
		}
        Register(const char * newId){updateRegisterId(newId);}
        Register(const Register& m);
        Register &operator = (const Register &m);
        bool operator == (const Register &m);
        bool operator != (const Register &m);
        void updateRegisterId(const char *_registerId) {
            memcpy(registerId,_registerId,MAX_REGISTER_ID);
        }
        void updateProgramId(const char *_programId) {
            memcpy(programId,_programId,MAX_PROGRAM_ID);
        }
        void updateMemberId(const string _memberId){memberId=_memberId;}
        void updateNumberOfReRegisterd(const char *_numberOfReRegistered) {
            memcpy(numberOfReRegistered,_numberOfReRegistered,MAX_NUMBER_OF_RE_REGISTER);
        }

        friend istream & operator >> (istream &is,Register &m);
        friend ostream & operator << (ostream &is,Register &m);

        bool Pack(IOBuffer& Buffer) const;
        bool Unpack(IOBuffer &Buffer);
};
istream & operator >> (istream &is,Register &m);
ostream & operator << (ostream &is,Register &m);

#endif
