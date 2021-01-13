#include <stdio.h>
#include "setup.h"
#include "control_loop.h"

int main() {
	CheckInstallation();
	printf("\n\nStartup checks... OK\nRunning main loop!\n\n------------------------------\n\n");
	StartMainLoop();
	return 0;
}
