/*
    This file is part of the Pi Entertainment System (PES).

    PES provides an interactive GUI for games console emulators
    and is designed to work on the Raspberry Pi.

    Copyright (C) 2021 Neil Munday (neil@mundayweb.com)

    PES is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PES is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PES.  If not, see <http://www.gnu.org/licenses/>.

    Description:

    This program takes a ROM and calculates its RetroAchivements.org hash value.

    Use the -t option to specify the ROM type (nes, snes, genesis or generic).
    If not specified, then "generic" is assumed.

		Acknowledgements:

		https://github.com/RetroAchievements/rcheevos
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "rcheevos/include/rc_hash.h"

int main(int argc, char **argv){
	int c, consoleId;
	char *romFile = NULL;
	const char *consoleName = NULL;
  char hashBuffer[33];

	while ((c = getopt (argc, argv, "hi:")) != -1){
		switch(c){
			case 'i':
				consoleId = atoi(optarg);
				break;
			case 'h':
				printf("rasum -i CONSOLE_ID ROM_PATH\n\nUse the -i option to specify the console ID as defined by RetroAchievements.org.\n");
				return 0;
			case '?':
				if (optopt == 'i'){
					fprintf(stderr, "Option -%c requires a value.\n", optopt);
				}
				else if (isprint(optopt)){
					fprintf(stderr, "Unknown option -%c'\n", optopt);
				}
				else{
					fprintf(stderr, "Unknown option character '\\%x'.\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}

	if (optind == argc){
		fprintf(stderr, "Rom file path not specified!\n");
		return 1;
	}

	romFile = argv[optind];

	consoleName = rc_console_name(consoleId);
	if (strcmp(consoleName, "Unknown") == 0){
		fprintf(stderr, "Unknown console type\n");
		return 1;
	}

	rc_hash_generate_from_file(hashBuffer, consoleId, romFile);

	printf("%s\n", hashBuffer);

  return 0;
}
