import time
import board
import adafruit_dht
import subprocess
import os
 
# Initial the dht device, with data pin connected to:
dhtDevice = adafruit_dht.DHT22(board.D4)
 
# you can pass DHT22 use_pulseio=False if you wouldn't like to use pulseio.
# This may be necessary on a Linux single board computer like the Raspberry Pi,
# but it will not work in CircuitPython.
# dhtDevice = adafruit_dht.DHT22(board.D18, use_pulseio=False)

def RunReadingsLoop():
        
        print("\n----------------------------\n")
        print("Starting Apache Server...\n")
        subprocess.call(['sudo', 'service', 'apache2','start'], stdout=open(os.devnull, 'wb'))
        print("Running loop for DHT22 readings...\n")
        while True:
            try:
                # Print the values to the serial port
                temperature_c = dhtDevice.temperature
                ##temperature_f = temperature_c * (9 / 5) + 32
                humidity = dhtDevice.humidity
                print(
                    "Temp: {:.1f} C    Humidity: {}% ".format(
                        temperature_c, humidity
                    )
                )
                
                f = open("/var/www/html/PiGardener/readings.csv", "w")
                f.write("{:.1f},{}".format(temperature_c, humidity))
                f.close()
         
            except RuntimeError as error:
                # Errors happen fairly often, DHT's are hard to read, just keep going
                print(error.args[0])
                time.sleep(2.0)
                continue
            except Exception as error:
                dhtDevice.exit()
                raise error
         
            time.sleep(2.0)
