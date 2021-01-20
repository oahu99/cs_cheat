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
#include "kbd.hpp"
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
	long flFlashDurationOffset;

	MMC* mmc = new MMC; // create new memory management object
	KBD* kbd = new KBD;
	pid = mmc->getPID(); // get pid for currently running csgo process
	// std::cout << pid;
	clientBase = mmc->getClientBase(pid);
	

	int healthBuf;
	int fFlags;
	int jump;
	bool isGround;
	int flashDuration;

	flashDuration = 0;

	localPlayer = clientBase + (signatures::dwLocalPlayer);
	forceJump = clientBase + (signatures::dwForceJump);
	//std::cout << "clientBase: " << clientBase << "\n";

	mmc->readMem(pid, (void*)(localPlayer), &playerBase, sizeof(playerBase));

	//std::cout << "playerBase: " << playerBase << "\n";

	healthOffset = playerBase + netvars::CBasePlayer::m_iHealth;
	fFlagsOffset = playerBase + netvars::CBasePlayer::m_fFlags;
	flFlashDurationOffset = playerBase + netvars::CCSPlayer::m_flFlashDuration;

	kbd->kbd = kbd->getKeyboardPointer();

	long entityObject;
	long entityBase;
	int team;
	int myteam;

	int glowIndex;

	int yes = 1;
	int no = 0;

	long glowObject;

	mmc->readMem(pid, (void*)(playerBase + signatures::dwGlowObjectManager), &glowObject, sizeof(glowObject));

	float red, green, blue;

	mmc->readMem(pid, (void*)(playerBase + 0x12c), &myteam, sizeof(myteam));
	std::cout << "my team: " << myteam << "\n";

	for (int i = 0; i < 64; i++){
		entityBase = clientBase + signatures::dwEntityList + i*0x10;
		//std::cout << entityBase << "\n";

		mmc->readMem(pid, (void*)(entityBase), &entityObject, sizeof(entityObject)); // read out entity ID
		mmc->readMem(pid, (void*)(entityObject + 0xa330), &glowIndex, sizeof(glowIndex));

		if (entityObject != 0){
			mmc->readMem(pid, (void*)(entityObject + 0x12c), &team, sizeof(team));
			std::cout << "entity team: " << team << "\n";

			if (myteam != team && (team != 0)){
				red = 2.0;
				mmc->writeMem(pid, (void*)(glowObject + (glowIndex * 0x38) + 0x24), &yes, sizeof(yes));
				mmc->writeMem(pid, (void*)(glowObject + (glowIndex * 0x38) + 0x25), &no, sizeof(no));
				mmc->writeMem(pid, (void*)(glowObject + (glowIndex * 0x38) + 0x4), &red, sizeof(red));
			}
			else{

			}

		}

		// sleep(100);
	}

	while (1){
		mmc->readMem(pid, (void*)(healthOffset), &healthBuf, sizeof(healthBuf));
		mmc->readMem(pid, (void*)(fFlagsOffset), &fFlags, sizeof(fFlags));
		mmc->readMem(pid, (void*)(forceJump), &jump, sizeof(jump));

		mmc->writeMem(pid, (void*)(flFlashDurationOffset), &flashDuration, sizeof(flashDuration));

		isGround = fFlags&(1<<0);
		// //std::cout << "Health: " << healthBuf << " isGround: " << isGround << " jump: " << jump << "\n";

		int jumpVal = 0x6;

		// std::cout << kbd->isKeyPressed("lshift", kbd->kbd) << "\n";

		if (isGround && (kbd->isKeyPressed("space", kbd->kbd)==2)){ // bunnyhop
			mmc->writeMem(pid, (void*)(forceJump), &jumpVal, sizeof(jumpVal));
		}
	}

}