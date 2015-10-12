//
////  filesys.cpp
////
////
////  Created by Marisa Schmidt on 5/6/15.
////
///

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <ftw.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>
using namespace std;



const unsigned int NUM_OF_BINS = 12;
unsigned int bins[NUM_OF_BINS];

vector<int> Sizes; //size of files stored in vector

void search( char* );
void binning();
void display();
int fn ( const char* , const struct stat* , int , struct FTW* );


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Error :: Usage <directory>" << endl;
    }
    else {
        search(argv[1]);
    }
    return 0;
}


/*******************************FUNCTIONS**************************************/

//The function nftw() is the same as ftw(), except that it has one additional argument, flags, and calls fn() with one more argument, ftwbuf. It walks through the directory and "bins" the sizes of the files it encounters

void search(char* dir) {
    int nopenfd = 0;
    int flags = FTW_PHYS; //do not follow symbolic links, nonexistant files
    nftw(dir, fn, nopenfd, flags); //ntfw(const char *dirpath, int (*fn), int nopenfd, int flags);.... int (*fn) takes (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
    binning();
    display();
}


/******************************************************************************/
//file tree walk using struct FTW - uses file descriptor for each level of directory tree, finds file entries in directory
int fn(const char* filepath, const struct stat* sb, int flag, struct FTW* ftwbuf){
    int rval = 0;
    if (!(flag & !S_IFDIR)) { //if flag and not directory
        Sizes.push_back(sb->st_size); //add size of file to our vector! otherwise...
        cout << "hello" << endl;
    }
    
    return rval;
}

/******************************************************************************/
//bins to separate the data into sections. the larger the files, the more likely to be placed in bigger bin. more smaller file sizes fit into one bin.
//calculate histogram
void binning() {
    
    for (auto j = Sizes.begin(); j != Sizes.end(); j++) {
        
        float KB = ((*j)/1024.0);
        
        if (KB < 1) { //because log is negative when input < 1
            bins[0]+=1;
        } else {
            int object = ceil(log2f(KB));
            
            if (object > NUM_OF_BINS - 1) { //if exceeds the greatest size
                object = NUM_OF_BINS - 1; //place file size in largest bin
            }
            else { //do nothing
                object = object;
            }
            
            bins[object]+=1;
        }
    }
}

/******************************************************************************/
//histogram of disk file size distribution
void display() {
    cout << endl;
    cout << "Max Range (KB)" << setw(20) << "Num of Files" << setw(20) << "Percentage(%)" << endl;
    cout << "***************************************************" << endl;
    for (int i = 0; i < NUM_OF_BINS; i++) {
        string range = "2^ ";
        range += i;
        
        int numfiles = bins[i];
        float percentage = (((float)bins[i])/(Sizes.size()))*100;
        
        cout << "2^" << left << setw(20) << setfill(' ') << i << left << setw(20) << numfiles << left << setw(25) << percentage << endl;
        cout << endl;
    }
}
