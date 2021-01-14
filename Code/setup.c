#include <stdio.h>
#include "setup.h"
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

char* readings_file = "/var/www/html/PiGardener/index.php";
char* server_folder = "/var/www/html/PiGardener";
char* apache_folder = "/usr/sbin/apache2";
int web_folder_exists = 0;
int apache_folder_exists = 0;
int readings_file_exists = 0;

void CheckIfFileExists();
void CheckForApacheFolder();
void RunFirstTimeInstall(int apache_status, int web_folder_status);
void CheckInstallation();
void CheckForReadingFile();
void CreateReadingsPage();

void CheckIfFileExists() {
	DIR* dir = opendir(server_folder);
	if(dir) {
		printf("%s","\n\033[1;32mPiGardener web folder exists!\033[0m\n");
		web_folder_exists = 1;
	}
	else if (ENOENT == errno) {
		printf("%s", "\n\033[1;31mPiGardener web folder does not exist!!\033[0m\n");
		web_folder_exists = 0;
	}
	else {
		web_folder_exists = 0;
	}
}

void CheckForApacheFolder() {

    if( access( apache_folder, F_OK ) == 0 ) {
    	printf("%s","\n\033[1;32mApache installation located!\033[0m");
		apache_folder_exists = 1;
	} else {
				printf("%s","\033[1;31mApache installation not found!\033[0m");
		apache_folder_exists = 0;
	}
}

void CheckForReadingsFile() {
	if(access(readings_file, F_OK) == 0) {
		printf("%s","\033[1;32mReadings web page located!\033[0m");
		readings_file_exists = 1;
	} else {
		printf("%s","\033[1;31mReadings web page not found!\033[0m");
		readings_file_exists = 0;
	}
}

void CheckInstallation() {
	CheckForApacheFolder();
	CheckIfFileExists();
	CheckForReadingsFile();

	if (apache_folder_exists == 0 || web_folder_exists == 0 || readings_file_exists == 0)
	{
		printf("\n\n\033[1;33mOne or more requirements were not met. Would you like setup to automatically install the component(s)?\n\n[Y/N] : \033[0m");
		char option;
		scanf("%c", &option);

		if (option == 'y' || option == 'Y')
		{
			RunFirstTimeInstall(apache_folder_exists, web_folder_exists);
		}
	} else {

	}
}

void RunFirstTimeInstall(int apache_status, int web_folder_status) {
	printf("\n---------- First Time Setup ----------");
	if (apache_status == 0)
	{
		printf("\n\nInstalling Apache2...");
		system("sudo apt-get -y install apache2");

	} else if (apache_status == 1) {
		printf("\n\nSkipping Apache2 install as folder already exists!");
	}

	if (web_folder_status == 0)
	{
		printf("\n\nCreating Web Folder...");
		system("sudo mkdir /var/www/html/PiGardener");
		printf("%s","\033[1;32m   DONE!\033[0m");

	} else if (web_folder_status == 1) {
		printf("\n\nSkipping web folder creation as folder already exists!");
	}

	if (readings_file_exists == 0) {
		printf("\n\nCreating web page for readings...");
		CreateReadingsPage();

	} else if (readings_file_exists == 1) {
		printf("\n\nSkipping creating the web page for readings as it already exists!");
	}

	printf("\n\nSetup finished. Please re-run this program.\n\n");
	exit(0);
}

void CreateReadingsPage() {
	char page_content[] = "<?php $option = htmlspecialchars($_GET['reading']);$file = fopen('readings.csv','r') or die ('Unable to read from readings file!');$content = fread($file,filesize('readings.csv'));$readings = explode(',', $content); if($option == 'humidity') { echo $humidity[0]; } elseif ($option == 'temperature') { echo $readings[1];} ?>";

	FILE *fptr;
	fptr = fopen(readings_file,"w");
	fprintf(fptr, "%s", page_content);
	fclose(fptr);

	printf("%s","\033[1;32m   DONE!\033[0m");
}