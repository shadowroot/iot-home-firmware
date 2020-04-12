#include <DHT.h>
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//pins
#define LIGHT_SENSOR_PIN 4
//Soil temperature
#define DS_TEMPERATURE_PIN 3
#define SOIL_MOISTURE_PIN A1

#define DHTPIN 2 
#define DHTTYPE DHT11   // DHT 11

//Dallas temperature - teplomer
//DS18B20
//DS18B20 Temperature Sensor Module Kit Waterproof 100CM Digital Sensor Cable Stainless Steel Probe Terminal Adapter For Arduino
/*
 * Pluggable terminal waterproof DS18B20 temperature sensor can be used in many places, such as soil temperature detection, hot water tank temperature control, waterproof DS18B20 temperature sensor must also be connected to a pull-up resistor can be used, for which we designed the converter to send use.
Product Specifications:
Temperature sensor supply voltage: 3.0V ~ 5.5V
Temperature sensor resolution: 9 to 12 adjustable resolution
Temperature range: -55 ~ +125 ° (lead can only withstand the highest temperature of 85 degrees)
Temperature Sensor Output Lead: Yellow (DATA) Red (VCC) and Black (GND)
Adapter Cables: DATA, VCC, BLK,
 */
// nastavení čísla vstupního pinu
// vytvoření instance oneWireDS z knihovny OneWire
OneWire oneWireDS(DS_TEMPERATURE_PIN);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature teplomerDS(&oneWireDS);

//Soil moisture
//Analog Capacitive Soil Moisture Sensor V1.2 3.3~5.5V
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilMoisturePercent=0;

//Light detection
//3.3 - 5.5 V
//Optical Sensitive Resistance Light Detection Photosensitive Sensor
int lightValue = 0;
//char outbuff[100];

//Hudnimity
//DHT11

DHT dht(DHTPIN, DHTTYPE);

float h=0,t=0,hic=0;
int n=0;

void setup() {
  Serial.begin(9600);
  // zapnutí komunikace knihovny s teplotním čidlem

  // put your setup code here, to run once:
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  
  teplomerDS.begin();
  dht.begin();
}

void loop() {
    Serial.print("{");
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds \"old\" (its a very slow sensor)
    h = dht.readHumidity();
    Serial.print("\"hud0\":");
    Serial.print(h);
    delim();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    Serial.print("\"airTemp0\":");
    Serial.print(t);
    delim();
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
    }
    else{
      // Compute heat index in Celsius (isFahreheit = false)
      hic = dht.computeHeatIndex(t, h, false);
      Serial.print("\"heatIndex0\":");
      Serial.print(hic);
      delim();
      //Serial.print(F("Humidity: "));
      //Serial.print(h);
      //Serial.print(F("%  Temperature: "));
      //Serial.print(t);
      //Serial.print(F("°C "));
      //Serial.print(F(" Heat index: "));
      //Serial.print(hic);
      //Serial.println(F("°C "));
    }
    
    lightValue = digitalRead(LIGHT_SENSOR_PIN);
      Serial.print("\"dark\":");
      Serial.print(lightValue);
      delim();
    //Serial.print("Light sensor value:");
    //Serial.println(lightValue);

    // načtení informací ze všech připojených čidel na daném pinu
    teplomerDS.requestTemperatures();
    // výpis teploty na sériovou linku, při připojení více čidel
    // na jeden pin můžeme postupně načíst všechny teploty
    // pomocí změny čísla v závorce (0) - pořadí dle unikátní adresy čidel
    //Serial.print("Teplota cidla DS18B20: ");
    //Serial.print(teplomerDS.getTempCByIndex(0));
    //Serial.println(" stupnu Celsia");
     Serial.print("\"soilTemp\":");
     Serial.print(teplomerDS.getTempCByIndex(0));
     delim();
   soilMoisture();
     Serial.print("\"soilMoist\":");
     Serial.print(soilMoistureValue);
     delim();

      Serial.print("\"soilMoistPer\":");
     Serial.print(soilMoisturePercent);
     delim();
  //n = sprintf(outbuff, "{\"soilTemp\":%d,\"soilMoist\":%d,\"soilMoistPer\":%d,\"hud0\":%f,\"airTemp\":%f,\"heatIndex0\": %f,\"light\":%d}", teplomerDS.getTempCByIndex(0), soilMoistureValue, soilMoisturePercent, h, t, hic, lightValue);
   //Serial.print(outbuff);
   Serial.println("}");
   delay(5000);

}

void delim(){
  Serial.print(",");
}

int soilMoisture(){
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);  //put Sensor insert into soil
  //Serial.println(soilMoistureValue);
  //Serial.print("SOIL Moisture:");
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if(soilMoisturePercent > 100)
  {
    soilMoisturePercent = 100;
    //Serial.println("100 %");
  }
  else if(soilMoisturePercent <0)
  {
    soilMoisturePercent = 0;
    //Serial.println("0 %");
  }
  //else if(soilMoisturePercent >0 && soilMoisturePercent < 100)
  //{
    //Serial.print(soilMoisturePercent);
    //Serial.print("%");
  //}
  
  //Serial.println(soilMoistureValue);
  
  return soilMoisturePercent;
}
