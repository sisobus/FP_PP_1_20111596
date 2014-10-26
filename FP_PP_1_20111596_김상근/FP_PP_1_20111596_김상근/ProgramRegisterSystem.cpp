#include "ProgramRegisterSystem.h"

int main() {
    while ( true ) {
        printMenu();
        int t;
        scanf("%d",&t);
        if ( t == 19 ) return printf("End program! Bye Bye~\n"),0;
        int ret = processProgramRegisterSystem(t);
        if ( ret < 0 ) processErrorMessage(ret);
    }
    return 0;
}
void printMenu() {
    printf("***************************************\n");
    printf("*       File Processing Projecet1     *\n");
    printf("*           Sangkeun Kim              *\n");
    printf("***************************************\n");
    printf("* 1. showMember                       *\n");
    printf("* 2. showProgram                      *\n");
    printf("* 3. showRegister                     *\n");
    printf("* 4. MemberTest                       *\n");
    printf("* 5. ProgramTest                      *\n");
    printf("* 6. RegisterTest                     *\n");
    printf("* 7. SearchMember                     *\n");
    printf("* 8. InsertMember                     *\n");
    printf("* 9. UpdateMember                     *\n");
    printf("* 10.DeleteMember                     *\n");
    printf("* 11.SearchProgram                    *\n");
    printf("* 12.InsertProgram                    *\n");
    printf("* 13.UpdateProgram                    *\n");
    printf("* 14.DeleteProgram                    *\n");
    printf("* 15.SearchRegister                   *\n");
    printf("* 16.InsertRegister                   *\n");
    printf("* 17.UpdateRegister                   *\n");
    printf("* 18.DeleteRegister                   *\n");
    printf("* 19.END                              *\n");
    printf("***************************************\n");
}
int processProgramRegisterSystem(int selectedMenu) {
    MemberDeleteUpdate memberDeleteUpdate;
    ProgramDeleteUpdate programDeleteUpdate;
    RegisterDeleteUpdate registerDeleteUpdate;
	string s = "";
    switch ( selectedMenu ) {

        case 1:
            showMember();
            break;
        case 2:
            showProgram();
            break;
        case 3:
            showRegister();
            break;
        case 4:
            MemberTest();
            break;
        case 5:
            ProgramTest();
            break;
        case 6:
            RegisterTest();
            break;
        case 7:
            cout << "Input member key : ";
            cin >> s;
            memberDeleteUpdate.memberSearch(s);
            break;
        case 8:
            memberDeleteUpdate.memberInsert();
            break;
        case 9:
            memberDeleteUpdate.memberUpdate();
            break;
        case 10:
            cout << "Input delete member id : ";
            cin >> s;
            memberDeleteUpdate.memberDelete(s);
            break;
        case 11:
            cout << "Input program key : ";
            cin >> s;
            programDeleteUpdate.programSearch(s);
            break;
        case 12:
            programDeleteUpdate.programInsert();
            break;
        case 13:
            programDeleteUpdate.programUpdate();
            break;
        case 14:
            cout << "Input delete program id : ";
            cin >> s;
            programDeleteUpdate.programDelete(s);
            break;
        case 15:
            cout << "Input register key : ";
            cin >> s;
            registerDeleteUpdate.registerSearch(s);
            break;
        case 16:
            registerDeleteUpdate.registerInsert();
            break;
        case 17:
            registerDeleteUpdate.registerUpdate();
            break;
        case 18:
            cout << "Input delete register id : ";
            cin >> s;
            registerDeleteUpdate.registerDelete(s,false);
            break;
        case 19:
            return 0;
        default:
            return -1;
    }
	return 1;
}
void processErrorMessage(int error) {
    if ( error == -1 ) printf("error: select menu range over\n");
}

