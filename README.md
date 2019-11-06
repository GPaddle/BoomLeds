

 # BoomLeds

 Display well, Sounds well

 ## How to run

***/!\\ Windows users*** : The process can request to have access to a Linux subsystem (Ubuntu can be added with the microsoft store since Windows10)

 - [ ] Install nodeJS
 - [ ] Install Platformio
 - [ ] Configure all of them correctly

 ## Configure Upload path

 Change the following in `ArduinoCode/platformio.ini`

         upload_port = /dev/ttyS14
         monitor_port = /dev/ttyS14

 ## Flash Web Client

Build the client and copy all files from `panel-painter/dist-gz/` to `ArduinoCode/data/`.

With the linux shell (possible with Windows 10 and the linux subsystem installed via the Microsoft Store)

On `root`
 
         npm install --no-optionnal --prefix ./panel-painter
         npm run build --prefix ./panel-painter
         npm run gzips --prefix ./panel-painter


         mkdir ./ArduinoCode/data
         cp ./panel-painter/dist-gz/* ./ArduinoCode/data

## Windows special

the /dev/ttyS XXX found on the linux system is the COM XXX found on the windows system
In my case, I have the ESP connected to the COM 14
In the linux shell it will be /dev/ttyS14

Then run

On `root`

         pio run --target buildfs -d ./ArduinoCode/
         pio run --target uploadfs -d ./ArduinoCode/
         
To build and upload to the ESP

         platformio run --target upload -d ./ArduinoCode/
         
# Test the good work :

         platformio device monitor -p /dev/ttySXX -b XXXX

With the first XX serie replaced by your port number and the second range by the baud used by your ESP
