import subprocess
import os
from dht_readings import RunReadingsLoop

print ("\n\033[1;37;40mThe program will now check for the required components...\n")
print ("Checking Apache Installation...")

# Check if the apache is installed...

rc = subprocess.call(['which', 'apache2'], stdout=open(os.devnull, 'wb'))
if rc == 0:
    print('\033[1;32;40mApache is installed!\033[1;37;40m')
else:
    print('\033[1;31;40mApache is missing! Setup will install before proceeding...\033[1;37;40m')
    subprocess.call(['sudo', 'apt-get', 'install','-y', 'apache2'], stdout=open(os.devnull, 'wb'))
    subprocess.call(['sudo', 'apt', 'install','-y', 'php', 'libapache2-mod-php', 'php-mysql'], stdout=open(os.devnull, 'wb'))

# Check if the apache executable exists...

if os.path.exists("/usr/sbin/apache2") :
  print("\033[1;32;40mApache executable exists!\033[1;37;40m")
else:
  print("\033[1;31;40mApache executable doesn't exist!\033[1;37;40m")
  
print ("\n\033[1;37;40mChecking for web folder...")

# Check if the web folders/files for PiGardener exists...

if os.path.exists("/var/www/html/PiGardener"):
	print("\033[1;32;40mWeb folder exists!\033[1;37;40m")
else:
	print("\033[1;31;40mWeb folder doesn't exist! Setup will create the folder before proceeding...\033[1;37;40m")
	subprocess.call(['sudo', 'mkdir', '/var/www/html/PiGardener'], stdout=open(os.devnull, 'wb'))
	
if os.path.exists("/var/www/html/PiGardener/index.php"):
	print("\033[1;32;40mWeb page exists!\033[1;37;40m")
else:
	print("\033[1;31;40mWeb page doesn't exist! Setup will create the file before proceeding...\033[1;37;40m")
	f = open("/var/www/html/PiGardener/index.php", "w")
	f.write("<?php $option = htmlspecialchars($_GET['reading']);$file = fopen('readings.csv','r') or die ('Unable to read from readings file!');$content = fread($file,filesize('readings.csv'));$readings = explode(',', $content); if($option == 'humidity') { echo $readings[1]; } elseif ($option == 'temperature') { echo $readings[0];} ?>")
	f.close()

RunReadingsLoop()
