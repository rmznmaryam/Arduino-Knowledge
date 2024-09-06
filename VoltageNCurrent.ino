// Call libraries required for external breakout boards and communications.
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MCP4725.h> // DAC library
#include <Adafruit_INA219.h> // INA219 current sensor library


// Declare a current sensor object.
Adafruit_INA219 ina219; // Commands like ina219.getCurrent_mA() will read the current.


// Declare our voltage supply objects.
Adafruit_MCP4725 dac_LEDsupply;
#define DAC_RESOLUTION (9) // Set this value to 9, 8, 7, 6 or 5 to adjust the resolution.


// Declare some useful variables.
float voltageAcrossLED;
float currentAcrossLED;


void setup(void) {
Serial.begin(9600); // Initiates serial communication, so we can send our data to
// our computer. This is where the the baud rating is set.
// Initialize the INA219 sensor (current sensor).
ina219.begin();
// Initialize our DAC breakout board.
dac_LEDsupply.begin(0x62); // 0x62 sets the hex address of dac
// so the arduino addresses the correct DAC.
}


void loop() {
for( int i = 0; i < 4095;i += 20){
// Since the DAC provides 12-bit resolution, the command
dac_LEDsupply.setVoltage(i, false);
delay(10);
voltageAcrossLED = ina219.getBusVoltage_V(); //Take a voltage reading
Serial.print(voltageAcrossLED); //Print the voltage reading
Serial.print(" ");
currentAcrossLED = ina219.getCurrent_mA();
Serial.print(currentAcrossLED);
Serial.print(" ");
if(currentAcrossLED>100){ //Make a break condition
i = 4095;
}
dac_LEDsupply.setVoltage(0,false);// Turn off the LED voltage supply.
delay(30);
Serial.print(" ");
}
}
