/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
 *Modified by Ritu Ahmed 24-02-2020
 *if the body temperature and the humidity are normal then there is no virus.(GREEN LED)
 *if the body temperature goes 22-25 degree celsius with humidity 40-50% then virus in solution.(BLUE LED)
 *if the body temperature more than 33 degree celsius with humidity more than 95% then virus in solution.(RED LED)
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>         // OLED
#include <Adafruit_SSD1306.h> 
#include <Adafruit_NeoPixel.h>  //Version 1.3.4

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define PIN       2   // DIN Data in of RGBLED
#define NUMPIXELS 1   // how many RGBLED are there
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);// Graphic

#define SEALEVELPRESSURE_HPA (1012)


#define OLED_RESET 4 // not used nicht genutzt bei diesem Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Adafruit_SSD1306 display(OLED_RESET); Treiber vor Version1.2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme; // I2C
       // Primary I2C Address
                                        /*!
                                         *  @brief  alternate I2C address
                                         */
//#define BME280_ADDRESS_ALTERNATE (0x76)
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
    Wire.begin();
    Serial.begin(115200);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));
    pixels.begin();

    unsigned status;

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(5000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(INVERSE);
    
    // default settings
    status = bme.begin(BME280_ADDRESS_ALTERNATE);  
      
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 10000;

    Serial.println();


}


void loop() { 
    printValues();
    delay(delayTime);
    float temp=bme.readTemperature();
    float HUM= bme.readHumidity(); 
    if (temp){
      pixels.setPixelColor(0, pixels.Color(255,0,0));
      pixels.show();
      }
     
    else if (temp>=22.00 && temp<25.00 && HUM>=40.00 && HUM<=50.00){
      pixels.setPixelColor(0, pixels.Color(0,0,255));
      pixels.show();
      }
      
      else if ( temp >=33.00 && HUM >= 95.00 ){
      pixels.setPixelColor(0, pixels.Color(0, 255,0));
      pixels.show();
      }
}


void printValues() {

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
  

    
    

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
 

    //display.println();
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    
    display.print("Temperature = ");
    display.print(bme.readTemperature());
    display.println("*C");
    display.println();
    
    display.print("Humidity = ");
    display.print(bme.readHumidity());
    display.println("%");
    display.println();
                  
    display.display();
    
    
    

}
