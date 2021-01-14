#include <stdio.h>
#include "setup.h"
#include "control_loop.h"
#include <stdlib.h>
#include <unistd.h>

int main() {
	CheckInstallation();
	printf("\n\nStartup checks... OK\nRunning main loop!");
	system("sudo service apache2 start");
	printf("\n\n------------------------------\n\n");
	StartMainLoop();
	return 0;
}
