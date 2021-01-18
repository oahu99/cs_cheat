// Memory management class
#ifndef MMC_H
#define MMC_H
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

class MMC
{

	int read_buf;
	int size = sizeof(read_buf); // transfer 16 bytes

public:
	pid_t getPID();
	long getPlayerBase(pid_t pid);
	void readMem(pid_t pid, void* src, void* dst, size_t size);
	void writeMem(pid_t pid, void* dst, void* src, size_t size);
};

#endif