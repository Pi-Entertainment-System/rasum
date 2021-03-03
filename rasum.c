/*
		MIT License

		Copyright (c) 2021 Neil Munday

		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:

		The above copyright notice and this permission notice shall be included in all
		copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
		SOFTWARE.

    Description:

    This program takes a ROM and calculates its RetroAchivements.org hash value.

    Use the -i option to specify the console ID as defined by RetroAchivements.org

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
