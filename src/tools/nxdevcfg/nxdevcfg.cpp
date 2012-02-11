/* 
** NetXMS - Network Management System
** Server startup module
** Copyright (C) 2003, 2004, 2005, 2006, 2007 NetXMS Team
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** File: nxdevcfg.cpp
**
**/

#include <nms_util.h>

#if HAVE_GETOPT_H
#include <getopt.h>
#endif


#define VALID_OPTIONS "bcClLPX"


//
// Show help
//

static void ShowHelp()
{
	printf("Available options:\n");
#if HAVE_DECL_GETOPT_LONG
	printf("   -b, --bindir    Binary directory\n"
	       "   -c, --cflags    C compiler flags\n"
	       "   -C, --cppflags  C/C++ compiler flags\n"
	       "   -X, --cxxflags  C++ compiler flags\n"
	       "   -d, --datadir   Data directory\n"
	       "   -l, --ldflags   Linker flags\n"
	       "   -L, --libdir    Library directory\n"
	       "   -P, --prefix    Installation prefix\n"
	      );
#else
	printf("   -b  Binary directory\n"
	       "   -c  C compiler flags\n"
	       "   -C  C/C++ compiler flags\n"
	       "   -d  Data directory\n"
	       "   -l  Linker flags\n"
	       "   -L  Library directory\n"
	       "   -P  Installation prefix\n"
	       "   -X  C++ compiler flags\n"
	      );
#endif
}


//
// main
//

int main(int argc, char *argv[])
{
#if HAVE_DECL_GETOPT_LONG
	static struct option longOptions[] = 
	{
		{ "bindir", 0, NULL, 'b' },
		{ "cflags", 0, NULL, 'c' },
		{ "cppflags", 0, NULL, 'C' },
		{ "cxxflags", 0, NULL, 'X' },
		{ "datadir", 0, NULL, 'd' },
		{ "ldflags", 0, NULL, 'l' },
		{ "libdir", 0, NULL, 'L' },
		{ "prefix", 0, NULL, 'P' },
		{ NULL, 0, 0, 0 }
	};
#endif
	int ch;

	if (argc < 2)
	{
		ShowHelp();
		return 1;
	}

#if HAVE_DECL_GETOPT_LONG
	while((ch = getopt_long(argc, argv, VALID_OPTIONS, longOptions, NULL)) != -1)
#else
	while((ch = getopt(argc, argv, VALID_OPTIONS)) != -1)
#endif
	{
		switch(ch)
		{
			case 'b':
				printf("%s\n", BINDIR);
				return 0;
			case 'd':
				printf("%s\n", DATADIR);
				return 0;
			case 'L':
				printf("%s\n", LIBDIR);
				return 0;
			case 'P':
				printf("%s\n", PREFIX);
				return 0;
			case '?':
				ShowHelp();
				return 1;
			default:
				break;
		}
	}
	printf("\n");
	return 0;
}
