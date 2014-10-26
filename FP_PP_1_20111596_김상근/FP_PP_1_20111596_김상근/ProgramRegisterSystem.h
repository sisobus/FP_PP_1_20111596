#include "All.h"
#include "member.h"
#include "program.h"
#include "register.h"
#include "member_manager.h"
#include "program_manager.h"
#include "register_manager.h"

vector<Member> showMember();
vector<Program> showProgram();
vector<Register> showRegister();
void MemberTest();
void ProgramTest();
void RegisterTest();
int processProgramRegisterSystem(int command);
void printMenu();
void processErrorMessage(int error);
