//
//  FileDescriptors.cpp
//  
//
//  Created by Marisa Schmidt on 3/20/15.
//
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main (int argc, char * argv[])
{

/* fd_set manages the set of files/I/O that we want to monitor */
fd_set set_of_files;
struct timeval tval;
    
int result;
    
//for user input
string input;

/*set host socket as first and only element */
FD_ZERO(&set_of_files);
FD_SET(0, &set_of_files); //zero is standard input

/* init timeout */
tval.tv_sec = 20; //20 seconds
tval.tv_usec = 0; //microseconds

result = select(0 + 1, &set_of_files, NULL, NULL, &tval);
/* 0 + 1 == the largest fd in the set, plus 1
 &set_of_files == the set of files descriptors to monitor for read
 NULL == monitor for write
 NULL == monitor for exceptions/errors
 &tval == return after amount of time regardless of situation 
*/

    if (result==0) {
     //timed out...
        sleep (1);
    }
    else if (result==-1) { //something is wrong in the select call
        cout << "ERROR found with select call" << endl;
    }
    else {
    //we get some input from the keyboard... ok to read from it now ///
        getline(cin, input);
        cout << "entered input : " << input << endl;
    }
    
}
