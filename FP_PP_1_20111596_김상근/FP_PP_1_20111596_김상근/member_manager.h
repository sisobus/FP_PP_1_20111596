#ifndef __MEMBER_MANAGER_H__
#define __MEMBER_MANAGER_H__

#include "All.h"
#include "program.h"
#include "member.h"
#include "register.h"
#include "register_manager.h"

class MemberDeleteUpdate {
    public:
        bool memberSearch(string key);
        void memberInsert();
        void memberUpdate();
        void memberDelete(string key);
		void writeDataFile();
};

#endif
