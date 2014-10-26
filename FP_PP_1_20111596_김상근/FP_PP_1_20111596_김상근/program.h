#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "All.h"
#include "program_manager.h"

#define STDMAXBUF 256
#define MAX_ID 8
#define MAX_START_TIME 10
#define MAX_DURATION 1

class Program{
    public:
        char id[MAX_ID+5];
        string title;
        char startTime[MAX_START_TIME+5];
        string instructorName;
        char duration;

    public:
        Program(){memset(id,0,sizeof(id));memset(startTime,0,sizeof(startTime));}
        Program(const char * newId){updateId(newId);}
        Program(const Program& m);
        Program &operator = (const Program &m);
        bool operator == (const Program &m);
        bool operator != (const Program &m);
        void updateId(const char * _id){memcpy(id,_id,MAX_ID);}
        void updateTitle(const string _title){title = _title;}
        void updateStartTime(const char *_startTime){memcpy(startTime,_startTime,MAX_START_TIME);}
        void updateInstructorName(const string _instructorName){instructorName = _instructorName;}
        void updateDuration(const char * _duration){memcpy(&duration,_duration,MAX_DURATION);}

        friend istream & operator >> (istream &is,Program &m);
        friend ostream & operator << (ostream &is,Program &m);

        bool Pack(IOBuffer& Buffer) const;
        bool Unpack(IOBuffer &Buffer);
};
istream & operator >> (istream &is,Program &m);
ostream & operator << (ostream &is,Program &m);

#endif
