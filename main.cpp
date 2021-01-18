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

// proc is 10847

int main()
{

	int read_buf;
	int size = sizeof(read_buf); // transfer 16 bytes

	struct iovec iosrc;
	struct iovec iodst;

	iodst.iov_base = (void*)&read_buf;
	iodst.iov_len = size;

	iosrc.iov_base = (void*)(0x7faf5172f000 + 0x22861b0 + 0x13c);
	iosrc.iov_len = size;

	while (1) {
		process_vm_readv(29333, &iodst, 1, &iosrc, 1, 0);
		// if (read_buf) {
		// 	//std::cout << read_buf << "\n";
		// 	std::cout << "ground \n";
		// }
		// else {
		// 	std::cout << "air \n";
		// }
		std::cout << read_buf << "\n";
	}
}