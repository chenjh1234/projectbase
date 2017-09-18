#include <iostream>

using namespace std;
#include "projectmng.h"
#include "filemng.h"
int main (int argc, char *argv[])
{
    cout << "hello world" << endl;
    projectMng pm;
    pm.createProject("pp");
    return(0);
}

