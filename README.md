

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

## Linux Way

 On `/panel-painter`

         npm install --no-optionnal
         npm run build
         npm run gzips

 On `root`

         mkdir ./ArduinoCode/data
         cp ./panel-painter/dist-gz/* ./ArduinoCode/data

 Then run

 On `/ArduinoCode`

         pio run --target buildfs
         pio run --target uploadfs

## Windows Way

With the linux shell (installed via the Microsoft Store)

 On `/panel-painter`

         npm install --no-optionnal
         npm run build
         npm run gzips

 On `root`

         mkdir ./ArduinoCode/data
         cp ./panel-painter/dist-gz/* ./ArduinoCode/data

the /dev/ttyS XXX found on the linux system is the COM XXX found on the windows system
In my case, I have the ESP connected to the COM 14
In the linux shell it will be /dev/ttyS14

 Then run

 On `root`

         pio run --target buildfs -d ./ArduinoCode/
         pio run --target uploadfs -d ./ArduinoCode/
