#ifndef __REGISTER_MANAGER_H__
#define __REGISTER_MANAGER_H__

#include "All.h"
#include "program.h"
#include "register.h"

class RegisterDeleteUpdate {
    public:
        bool registerSearch(string key);
        void registerInsert();
        void registerUpdate();
        void registerDelete(string key,bool isMemberDelete);
		void writeDataFile();
};

#endif
