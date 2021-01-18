// Memory management class
#ifndef MMC_H
#define MMC_H

class MMC
{

	int read_buf;
	int size = sizeof(read_buf); // transfer 16 bytes

public:
	void getPID();
	void getPlayerBase();
	int readMem();
	void writeMem();
};

#endif