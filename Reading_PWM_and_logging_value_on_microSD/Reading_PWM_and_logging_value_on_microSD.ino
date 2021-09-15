#include <SD.h> //Libraries used to for microSD card module SD: https://www.arduino.cc/en/reference/SD
#include <SPI.h> //SPI: https://www.arduino.cc/en/reference/SPI

//Pinout for arduino uno: https://www.circuito.io/blog/arduino-uno-pinout/
//Pinout for arduino nano: https://upload.wikimedia.org/wikipedia/commons/e/e4/Arduino-nano-pinout.png

//const int means an integer variable that CANNOT change - it is constant.
//const int values need to be declared at run time.
const int chipSelect = 2; //Used to select memory module
const int readPIN = 8; // D8 (Digital pin 8) is the pin we a reading the PWM signal into
const int writePIN = 3; //D3 is the pin we are outputting the PWM signal from. Note: only certain pins can output PWM https://create.arduino.cc/projecthub/muhammad-aqib/arduino-pwm-tutorial-ae9d71
const int dutyCycle = 90; //Can be a value between 0 - 255

File myFile; //"myFile" is an object of class "File" 
             //More info: https://www.geeksforgeeks.org/c-classes-and-objects/

int value = 0; //Variable to store our values in microseconds (1000 microseconds = 1 millisecond)

void setup() { //Setup only runs once
               //Void means that the function does not return any value
               //If an arbitrary function had "int" instead of void, this means that function must return an integer value.
  pinMode(readPIN, INPUT); //Setup pins as Input/Output
  pinMode(writePIN, OUTPUT);
  Serial.begin(9600); //Opens debugging window. 9600 represents the baud rate.
                      //baud rate defines how fast data is sent over serial lines.
                      //More info: https://learn.sparkfun.com/tutorials/serial-communication/rules-of-serial
                      
  // More info on if else statements: https://www.arduino.cc/en/Tutorial/BuiltInExamples/ifStatementConditional
  // SD Card initialization
  if (SD.begin(chipSelect)) { //if initialization was successful...
    Serial.println("SD card is ready to use.");   
  }
  else {
    Serial.println("SD card initalization failed");
    return;
  }

//  Create/Open file
  myFile = SD.open("test.txt", FILE_WRITE); //(Specify what file you want use; specify if you want to read or write)
  if (myFile) {
    myFile.println("Hello World");          //I want to write "Hello World" to the text file
    myFile.close(); //Close file
    Serial.println("test.txt was successfully opened and closed");
  }
  else {
    Serial.println("Error opening test.txt"); //Error message is printed if myFile = SD.open returns 0.
   
    return;
  }
}

void loop() { //main loop that repeats once it reaches the bottom.

  //analogWrite(pin, val) "pin" is the physical pin on an uno, nano, etc. that will output the PWM. "val" must be between 0 - 255 to determine duty cycle.
  //analogWrite() https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
  analogWrite(writePIN, dutyCycle); //Tells microcontroller to output PWM signal at 35%   90/(255+1) ~ 35%.

  //pulseIn() https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/
  value = pulseIn(readPIN, HIGH);   // Store the amount of time signal is high for one period: https://learn.sparkfun.com/tutorials/pulse-width-modulation/all

  myFile = SD.open("test.txt", FILE_WRITE); //Write to myFile
    if (myFile) {
      myFile.println(value); //Store value on SD card
      myFile.close();
    }
   else {
    Serial.println("Error opening test.txt");
   
    return;
  }
}
