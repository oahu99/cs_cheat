#include "mmc.hpp"
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
#include <stdio.h>

pid_t MMC::getPID()
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
    	    		//std::cout << *iter << "\n";
    	    		return std::stoi(*iter);
    	    	}
    		}
    	}
    	else 
    		std::cout << "Bad file\n";

    	commFile.close();
    	commPath.str(""); // clear path stringstream
    }
    return(0);
}

long MMC::getClientBase(pid_t pid)
{
    std::stringstream mapsPath;
    std::ifstream mapsFile;
    std::string line;
    std::string playerBaseString;
    std::stringstream playerBaseStringStream;
    long playerBaseLong;

    mapsPath << "/proc/" << pid << "/maps";
    mapsFile.open(mapsPath.str());
    if(mapsFile.is_open()){
    	while(getline(mapsFile, line)){
    		if(line.find("/client_client.so") != std::string::npos){
    			//std::cout << line << "\n";
    			playerBaseString = line.substr(0, line.find("-"));
    			//std::cout << playerBaseString << "\n";

    			playerBaseStringStream << std::hex << playerBaseString;
    			playerBaseStringStream >> playerBaseLong;
    			//std::cout << playerBaseLong << "\n";

    			return(playerBaseLong);
    		}
    	}
    }
    else
    	std::cout << "Bad File\n";

	return(0);
}

void MMC::readMem(pid_t pid, void* src, void* dst, size_t size)
{
	/*
    pid  = target process id
    src  = address to read from on the target process
    dst  = address to write to on the caller process
    size = size of the buffer that will be read
    */

    struct iovec iosrc;
    struct iovec iodst;
    iodst.iov_base = dst;
    iodst.iov_len  = size;
    iosrc.iov_base = src;
    iosrc.iov_len  = size;

    process_vm_readv(pid, &iodst, 1, &iosrc, 1, 0);
}

void MMC::writeMem(pid_t pid, void* dst, void* src, size_t size)
{
    /*
    pid  = target process id
    dst  = address to write to on the target process
    src  = address to read from on the caller process
    size = size of the buffer that will be read
    */

    struct iovec iosrc;
    struct iovec iodst;
    iosrc.iov_base = src;
    iosrc.iov_len  = size;
    iodst.iov_base = dst;
    iodst.iov_len  = size;

    process_vm_writev(pid, &iosrc, 1, &iodst, 1, 0);
}
