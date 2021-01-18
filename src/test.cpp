#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <linux/input.h>
#include "kbd.hpp"
#include <cstring>

int main()
{

	KBD* kbd = new KBD;

	kbd->kbd = kbd->getKeyboardPointer();

	while(1)
	{
		if (kbd->isKeyPressed("lshift", kbd->kbd))
		{
			std::cout << "hello\n";
		}
	}

	return(0);
}
// int main()
// {
// 	int key;

//     // if ( strcmp(keyName.c_str(), "lshift") == 0 )       key = KEY_LEFTSHIFT;
//     // else if ( strcmp(keyName.c_str(), "rshift") == 0 )  key = KEY_RIGHTSHIFT;
//     // else if ( strcmp(keyName.c_str(), "lalt") == 0 )    key = KEY_LEFTALT;
//     // else if ( strcmp(keyName.c_str(), "ralt") == 0 )    key = KEY_RIGHTALT;
//     // else if ( strcmp(keyName.c_str(), "lctrl") == 0 )   key = KEY_LEFTCTRL;
//     // else if ( strcmp(keyName.c_str(), "rctrl") == 0 )   key = KEY_RIGHTCTRL;
//     // else if ( strcmp(keyName.c_str(), "space") == 0)	
//     key = KEY_SPACE;

//     while(1) {
//     FILE *kbd = fopen("/dev/input/by-path/pci-0000:43:00.3-usb-0:4.1:1.1-event-kbd", "r");
//     char key_map[KEY_MAX/8 + 1];    //  Create a byte array the size of the number of keys
// 	//cout << "in loop\n";
//     memset(key_map, 0, sizeof(key_map));    //  Initate the array to zero's
//     ioctl(fileno(kbd), EVIOCGKEY(sizeof(key_map)), key_map);    //  Fill the keymap with the current keyboard state

//     int keyb = key_map[key/8];  //  The key we want (and the seven others arround it)
//     int mask = 1 << (key % 8);  //  Put a one in the same column as out key state will be in;

//     //return (keyb & mask);  //  Returns true if pressed otherwise false
//     std::cout << (keyb&mask) << "\n";

//     fclose(kbd);
// 	}

// }