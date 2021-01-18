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

#include <filesystem>

namespace fs = std::filesystem;

// proc is 10847


int main()
{

	std::vector<std::string> pids; // contains each running pid

    DIR* dir;
    struct dirent *dp;

    dir = opendir("/proc"); // open /proc to find PID of csgo
    while((dp = readdir(dir)) != NULL){
    	if (std::atoi(dp->d_name) != 0){
    		pids.push_back(dp->d_name); // put all PIDs into a vector to be parsed later
    	}
    }

    std::vector<std::string>::iterator iter;
    std::stringstream commPath;
    std::string process;
    std::ifstream commFile(commPath.str(), std::ios::binary);

    for (iter = pids.begin(); iter != pids.end(); iter++) {
    	commPath << "/proc/" << *iter << "/comm"; // put together full file path
  		commFile.open(commPath.str());
    	if(commFile.is_open()) {
    	    while (getline(commFile, process)){
    	    	if (!(std::strcmp(process.c_str(), "csgo_linux64"))){
    	    		std::cout << *iter << "\n";
    	    	}
    		}
    	}
    	else 
    		std::cout << "Bad file\n";

    	commFile.close();
    	commPath.str("");
    }

}