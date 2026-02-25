#include <OneWire.h>                 //this library is used to covert temp sensor data in esp 32 understandable language
#include <DallasTemperature.h> //this library is used to covert that sensor data into human readable form
#include <Wire.h>        //to work with i2c
#include <Adafruit_GFX.h>    //to work with display
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// defining our Dasboard Address
#define IO_USERNAME  "BRAVO_COWBOY"
#define IO_KEY       "aio_kKbP70Ci4BwnZQN1Rqh62U8sI1U8"
#define AIO_SERVER   "io.adafruit.com"
#define AIO_SERVER_PORT   1883

// defining WIFI Stuff
#define WIFI_SSID   "Wokwi_GUEST"
#define PASSWORD  ""

#define TEMP_SENSOR 5    
#define BUZZER_PIN  25     // defined the wire line that send sensor data to microcontroller
#define SCREEN_WIDTH 126
#define SCREEN_HEIGHT 64
#define OLED_RESET -1     //does not have any reset
#define OLED_ADDRESS 0x3C   //arduino send dato to specific adress of led

WiFiClient client;   // initiates the WIFI

Adafruit_MQTT_Client mqtt(&client,AIO_SERVER ,AIO_SERVER_PORT,IO_USERNAME ,IO_KEY )   // Broker
Adafruit_MQTT_PUBLISH temperaturefeed(&mqtt,IO_USERNAME "/feeds/temperature")   // inserting mqtt data to feeds


OneWire oneWire(TEMP_SENSOR);      // senoor is connected to pin 5 using one wire comm..
DallasTemperature sensor(&oneWire);        //converting that sensor data into human readble form using dallas library
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

Queuehandle_t tempqueue              //"tempqueue" is the name of the queue , "QueueHandle_t" is a datatype

//now we will create the task

//task1 : sense the temp and display it
void sensor_display_task(void *param){
  float temperature;

  while(1){  // since 1 is always true , it will run infinite times
  sensor.requestTemperatures();      //request sensoor to sense data and provide the value
  float temperature = sensor.getTempCByIndex(0);    // 0-> one temp sensoor is being used  // covert data in esp understandable language
 // reads temp in celcius and store the value in temperature

  display.clearDisplay();
  display.setCursor(0,30);    //set cursor to intial location to display text
  display.print(temperature);
  display.print("deg C");

  display.display();    // to display the text finally
 
  Serial.print("temperature");
  Serial.print(temperature);
  Serial.println("degree C");    //ln-> prints data in new line
  
  if(temperature > 20){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(50);
  }

  temperaturefeed.publish(temperature);   // feed the temperature to temperature feed
  )
  xQueueOverwrite(tempqueue,&temperature);  // data exchange 

  vtaskDelay(pdMS_TO_TICKS(1000));   //to delay of 1000 ticks 
}

// task2

void setup() {
 Serial.begin(115200); //show temp on serial temp, with speed of 115200
 Wire.begin(21,22);    //pin 21 ,22 is used as I2C pins 
 sensor.begin() ;  //prepare sensor to read data]

 display.begin(SSD1306_SWITCHCAPVCC,OLED_ADDRESS);      // without this OLED will will not work
 display.clearDisplay();   //clear dislay
 display.setTextSize(2);    // doubles text size     // these are inbuilt fxns of adafruit library
 display.setTextColor(SSD1306_WHITE);     //set text color as white
 
 // check is wifi connected
 Serial.print("connecting to wifi");
 WiFi.begin(WIFI_SSID ,PASSWORD )    
 while(!WiFi.isConnected()){
  Serial.print("WIFI is Still Connecting"); 
  delay(500);
 }
Serial.print("WiFi Is Connected"); 

// check is mqtt connected
Serial.print("connecting to mqtt"); 
 while (!mqtt.connected()) {
  Serial.print("MQTT is Still Connecting"); 
  delay(500);
 
}  // setup code runs only once
Serial.print("ADAFRUIT IO Is Connected"); 


void loop() {

  // in FreeRTOS we dont need the void loop therefore we need to stop the lopp for forever
  vTaskDelay(PortMAX_DELAY);   //"PortMAX_DELAY" delays the loop for infinite
}  //loop code runs again and again


