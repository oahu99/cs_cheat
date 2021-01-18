#ifndef KBD_H
#define KBD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <linux/input.h>

class KBD
{

public:
	FILE* kbd;
	int isKeyPressed(std::string keyName, FILE* kbd);
	FILE* getKeyboardPointer();

};

#endif