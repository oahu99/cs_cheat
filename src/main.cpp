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
#include "netvars.hpp"
#include "offsets.hpp"

int main()
{

	pid_t pid;
	long clientBase;
	long playerBase;
	long localPlayer;
	long forceJump;

	long healthOffset;
	long fFlagsOffset;

	MMC* mmc = new MMC; // create new memory management object
	pid = mmc->getPID(); // get pid for currently running csgo process
	// std::cout << pid;
	clientBase = mmc->getClientBase(pid);
	

	int healthBuf;
	int fFlags;
	int jump;
	bool isGround;

	localPlayer = clientBase + (signatures::dwLocalPlayer);
	forceJump = clientBase + (signatures::dwForceJump);
	//std::cout << "clientBase: " << clientBase << "\n";

	mmc->readMem(pid, (void*)(localPlayer), &playerBase, sizeof(playerBase));

	//std::cout << "playerBase: " << playerBase << "\n";

	healthOffset = playerBase + netvars::CBasePlayer::m_iHealth;
	fFlagsOffset = playerBase + netvars::CBasePlayer::m_fFlags;

	while (1){
		mmc->readMem(pid, (void*)(healthOffset), &healthBuf, sizeof(healthBuf));
		mmc->readMem(pid, (void*)(fFlagsOffset), &fFlags, sizeof(fFlags));
		mmc->readMem(pid, (void*)(forceJump), &jump, sizeof(jump));

		isGround = fFlags&(1<<0);
		std::cout << "Health: " << healthBuf << " isGround: " << isGround << " jump: " << jump << "\n";

		int jumpVal = 0x6;

		if (isGround){
			mmc->writeMem(pid, (void*)(forceJump), &jumpVal, sizeof(1));
		}
	}

}