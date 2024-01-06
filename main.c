//-----------------------------------------
// NAME: Deepta Mandal
// STUDENT NUMBER: 7833371
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: assignment #04, QUESTION: question #01
// 
// REMARKS: Testing Object Manager
//
//-----------------------------------------


#include <stdio.h>
#include "ObjectManager.h"


int main()

{


    Ref ref1, ref2, ref3, ref4;

    initPool();

    ref1=insertObject(500);


    ref2=insertObject(1000);
    dropReference(ref2);

    ref3=insertObject(100);
    ref4=insertObject(500);

    dumpPool();
    destroyPool();

    return 0;

}