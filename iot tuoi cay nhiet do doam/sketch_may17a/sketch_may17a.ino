#define BLYNK_TEMPLATE_ID "TMPL6j4c-Ioq2"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "k2TInLS2PP-0C6AH5gMUZGrU5tTIgixG"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"

#include "DHTesp.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int dht_pin=16;
int relay_bomtuoi=14;
int doam_bomtuoi=10;
int doam_tatbomtuoi=50;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHTesp dht;
unsigned long times=millis();
BlynkTimer timer;
WidgetLED ledconnect(V0);


void setup()
{
  Serial.begin(115200);
  delay(100);  
  pinMode(relay_bomtuoi,OUTPUT);
  digitalWrite(relay_bomtuoi,LOW);
  BlynkEdgent.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  dht.setup(dht_pin, DHTesp::DHT11);
}

void loop() {
  BlynkEdgent.run();
  if(millis()-times>1000){
    //Chớp tắt led connect trên app blynk
    if(ledconnect.getValue()){
      ledconnect.off();
    }else{
      ledconnect.on();
    }
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Blynk.virtualWrite(V1,temperature);
    Blynk.virtualWrite(V2,humidity);
    //Ghi giá trị độ ẩm đất lên blynk
    int doam_dat = analogRead(A0);
    doam_dat = map(doam_dat,0,1023,100,0);
    Serial.println("Độ ẩm đất: " + String(doam_dat));
    Blynk.virtualWrite(V3,doam_dat);
    //Chế độ tự động bơm tưới
      if(doam_dat<doam_bomtuoi){
        digitalWrite(relay_bomtuoi,HIGH);
        Blynk.virtualWrite(V4,digitalRead(relay_bomtuoi));
        Serial.println("Bật bơm tưới!");
      }else{
        if(doam_dat>doam_tatbomtuoi){
          digitalWrite(relay_bomtuoi,LOW);
          Blynk.virtualWrite(V4,digitalRead(relay_bomtuoi));
          Serial.println("Tắt bơm tưới!");
        }
      }
    if(dht.getStatusString()=="OK"){
      showOled(humidity, temperature,doam_dat);
    }
    times=millis();
  }
}
BLYNK_CONNECTED(){
  Blynk.syncVirtual(V4); //Đồng bộ dữ liệu từ server xuống esp khi kết nối
}

BLYNK_WRITE(V4){
    int p = param.asInt();
    digitalWrite(relay_bomtuoi,p);
    Serial.println("Relay bơm tưới: " + String(digitalRead(relay_bomtuoi)));
}

void showOled(float t, float h, float g) {
  display.clearDisplay();

  // Set larger text size for titles
  display.setTextSize(2);  
  display.setTextColor(SSD1306_WHITE);

  // Print the temperature
  display.setCursor(0, 0); 
  display.print("T:");
  display.print(t, 0); 
  display.print((char)247);

  // Print the humidity
  display.print("H:");
  display.print(h, 0);
  display.println("%");

  display.print("HC:");
  display.print(g, 0);
  display.print("%");

  display.display();  
}

