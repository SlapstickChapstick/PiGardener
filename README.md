# PiGardener
C program for Raspberry Pi, which gets readings from a DHT22 sensor and hosts a web page. The information can then be obtained by a mobile app using GET requests.

# The Aim
The aim is to have a program that automatically takes humidity and temperature readings in a greenhouse, while providing the user with a way to access the readings via either a web page or a mobile app.

# How it works
The DHT22 sensor is connected to a Raspberry Pi 4 Model B, which will run this program constantly. Every 2 seconds, the program will poll the reader and retrieve the readings for both the humidity and the temperature of the surrounding area. These readings are then stored in a CSV file. The program utilises Apache2 to host a PHP site capable of handling both GET/POST requests. Then, users with the mobile app (seperate repo) can make GET requests to the RPi and retrieve the data, allowing the user to easily see this info in realtime, as well as past readings.

# Tech Specs

Hardware:
  - 1x Raspbery Pi 4 Model B with Power Supply
  - 1x DHT22 Temperature & Humidity Sensor
  - 3x Female/Female Jumper leads for GPIO
  - 1x 10k Resistor for pull-up pin.
  
Software:
  - Raspbian/Ubuntu
  - GCC/Build-essential
  - Apache2
  - WiringPi

# Installation
To install PiGardener, do the following

**Make sure your OS is up to date**
Ubuntu/Debian/Raspbian:<br />
`apt-get update && apt-get upgrade`

**Clone this repo**<br />
`git clone https://github.com/SlapstickChapstick/PiGardener.git` 

**Navigate to the 'Build' folder and run the file in there**<br />
`cd Build
./PiGardener`

**Follow the on-screen instructions to get started**
