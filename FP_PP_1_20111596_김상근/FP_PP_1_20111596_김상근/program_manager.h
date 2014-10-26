#ifndef __PROGRAM_MANAGER_H__
#define __PROGRAM_MANAGER_H__

#include "All.h"
#include "register.h"
#include "program.h"

class ProgramDeleteUpdate {
    public:
        bool programSearch(string key);
        void programInsert();
        void programUpdate();
        void programDelete(string key);
		void writeDataFile();
};

#endif