#include <NTPClient.h>
#include <ESP8266WiFi.h> // provides ESP8266 specific Wi-Fi routines we are calling to connect to network
#include <WiFiUdp.h> //handles sending and receiving of UDP packages
/*
#include <SPI.h> // SPI for interfacing OLED with NodeMCU
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   D7
#define OLED_CLK   D5
#define OLED_DC    D2
#define OLED_CS    D8
#define OLED_RESET D3
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
*/

const char *ssid     = "hotspotname";
const char *password = "password";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800,60000);
String arr_days[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String date_time;
// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
  

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin(); 
/*  display config
  if(!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(5, 2);
  display.println("WELCOME TO");
  display.println("  CIRCUIT");
  display.println("  DIGEST");
  display.display();
  delay(3000);
  */
  
}

void loop() {
  timeClient.update();
  

  Serial.print(timeClient.getFormattedTime());
  if ( WiFi.status() != WL_CONNECTED ){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  int day = timeClient.getDay();
  Serial.println("  '"+arr_days[day]+"'");
  delay(1000);
  
/* 
 *  this is to add dat functionality
 *  Serial.print("  ");Serial.print(timeClient.getFormattedDate());
*/
  
 /* displaying the data on led display
  *  
  display.clearDisplay();
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(BLUE);
  display.setCursor(0, 2);
  int hh = timeClient.getHours();
  int mm = timeClient.getMinutes();
  int ss = timeClient.getSeconds();
  
  if(hh>12)
  {
    hh=hh-12;
    display.print(hh);
    display.print(":");
    display.print(mm);
    display.print(":");
    display.print(ss);
    display.println(" PM");
  }
  else
  {
    display.print(hh);
    display.print(":");
    display.print(mm);
    display.print(":");
    display.print(ss);
    display.println(" AM");   
  }

  int day = timeClient.getDay();
  display.println("'"+arr_days[day]+"'");
  
  date_time = timeClient.getFormattedDate();
  int index_date = date_time.indexOf("T");
  String date = date_time.substring(0, index_date);
  
  display.println(date);
  display.display();      // Show initial text

  
  Displaying ends
  */

}

