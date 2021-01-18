#include <iostream>
#include <cstring>
#include <sstream>
#include <istream>
#include <fstream>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/io.h>
#include <sys/uio.h>
#include <dlfcn.h>
#include <link.h>
#include <fcntl.h>
#include <vector>
#include <string>

using namespace std;

int main ()
{
	stringstream commPath;
    string STRING;
	ifstream infile;

	commPath << "/proc/" << 1 << "/comm";

	infile.open (commPath.str());
        while(getline(infile,STRING)) // To get you all the lines.
        {
	        //getline(infile,STRING); // Saves the line in STRING.
	        cout<<STRING; // Prints our STRING.
        }
	infile.close();
}