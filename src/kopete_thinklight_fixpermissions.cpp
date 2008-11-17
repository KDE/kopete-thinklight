//
// C++ Implementation: kopete_thinklight_fixpermissions
//
// Description: 
//
//
// Author: Bernhard Beschow <bbeschow (.at) cs.tu-berlin.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <sys/stat.h>

static const char path[] = "/proc/acpi/ibm/light";

int main()
{
	return chmod( path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
}
