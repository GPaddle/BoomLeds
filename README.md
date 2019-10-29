

 # BoomLeds

 Display well, Sounds well

 ## How to run

***/!\\ Windows users*** : The process can request to have access to a Linux subsystem (Ubuntu can be added with the microsoft store since Windows10)

 - [ ] Install nodeJS
 - [ ] Install Platformio
 - [ ] Configure all of them correctly

 ## Configure Upload path

 Change the following in `ArduinoCode/platformio.ini`

         upload_port = COM14
         monitor_port = COM14

 ## Flash Web Client

 Build the client and copy all files from `panel-painter/dist-gz/` to `ArduinoCode/data/`.

#### Linux Way

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

#### Windows Way

With the ubuntu shell (installed via the Microsoft Store)

 On `/panel-painter`

         npm install --no-optionnal
         npm run build
         npm run gzips

 On `root`

         mkdir ./ArduinoCode/data
         cp ./panel-painter/dist-gz/* ./ArduinoCode/data

I find it easier to use power shell (And its windows operations) to use the COM XX  notation that can be found on the Arduino IDE

 Then run

 On `/ArduinoCode`

         pio run --target buildfs
         pio run --target uploadfs
