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
#include "mmc.hpp"

int main()
{

	pid_t pid;
	long clientBase;
	long playerBase;

	MMC* mmc = new MMC; // create new memory management object
	pid = mmc->getPID(); // get pid for currently running csgo process
	// std::cout << pid;
	clientBase = mmc->getClientBase(pid);
	

	int healthBuf;
	long healthOffset;

	clientBase += (0x22861b0);
	std::cout << "clientBase: " << clientBase << "\n";

	mmc->readMem(pid, (void*)(clientBase), &playerBase, sizeof(playerBase));

	std::cout << "playerBase: " << playerBase << "\n";

	playerBase += 0x138;

	while (1){
		mmc->readMem(pid, (void*)(playerBase), &healthBuf, sizeof(healthBuf));
		std::cout << healthBuf << "\n";
	}

}