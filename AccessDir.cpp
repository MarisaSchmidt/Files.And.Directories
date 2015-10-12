//
//  AccessDir.cpp
//  
//
//  Created by Marisa Schmidt on 5/5/15.
//
//

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
using namespace std;

int main (void)
{
    DIR *dp;
    struct dirent *ep;
    char folder[100];
    string j;
    const char* i;
    ifstream inn;
    const char *dirname="C:/folder/";
    
    dp = opendir (dirname);
    if (dp != NULL)
    {
        while (ep == readdir (dp))
        {
            j=ep->d_name;
            i = j.c_str();
            sprintf(folder,"C:/folder/%s",i);
            cout<<folder<<endl;
        }
        (void) closedir (dp);
    }
    else
    {
        perror ("Couldn't open the directory");
    }
    system("pause");
    return 0;
}
