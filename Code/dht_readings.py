import time
import board
import adafruit_dht
import subprocess
import os
 
# Initialise the dht device, with the data pin connected to:
dhtDevice = adafruit_dht.DHT22(board.D4)

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
                # If an error happens, just keep running the code.
                print(error.args[0])
                time.sleep(2.0)
                continue
            except Exception as error:
                dhtDevice.exit()
                raise error
         
            time.sleep(2.0)
