#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <SoftwareSerial.h>

int Temperatursensor = A0;
int AirQualityPin = A1;
int RXDPin = 2;
int TXDPin = 3;
int Lichtschalter = 4;
int Luefter = 5;
int Licht = 7;
int Piezzo = 8;

int RohOuputTemperatur = 0;
float temperatur;
int tasterstatus = 0;
int letzterTasterstatus = HIGH;
int AirQualityData;
int TemperaturUpdateDelay = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);
int Feuertemp = 25;
int Lueftertemp = 20;

bool Lichtstatus = false;
bool Feuer = false;
bool Luefterstatus = false;

SoftwareSerial bleSerial(RXDPin, TXDPin);
char BleToClient;
int BleFromClient;

Thermistor* thermistor;


void SetupTemperature(int pin) {
  thermistor = new NTC_Thermistor(pin, 10000, 10000, 25, 3950);
}

void Temperatursystem() {
  if (thermistor) {
    temperatur = thermistor->readCelsius();
  } else {
    RohOuputTemperatur = analogRead(Temperatursensor);
    temperatur = map(RohOuputTemperatur, 0, 410, -50, 150);
  }
}

void SetupMonitor() {
  lcd.init();
  lcd.backlight();
}

void WriteOnMonitor(String Message, int line) {
  lcd.setCursor(0, line);
  lcd.print(Message);
}

void EraseMonitor() {
  lcd.clear();
}

void Lueftersystem() {
  if (temperatur >= Lueftertemp) {
    digitalWrite(Luefter, HIGH);
    Luefterstatus = true;
  } else {
    digitalWrite(Luefter, LOW);
    Luefterstatus = false;
  }
}

void ToggleLight(int pin) {
  Lichtstatus = !Lichtstatus;
  digitalWrite(pin, Lichtstatus ? HIGH : LOW);
}


void Lichtsystem() {
  tasterstatus = digitalRead(Lichtschalter);

  if (tasterstatus == LOW && letzterTasterstatus == HIGH) {
    ToggleLight(Licht);
    delay(50);
  }
  
  letzterTasterstatus = tasterstatus;
}

void SetupHouseLight(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}


void Feueralarm() {
  Feuer = (temperatur >= Feuertemp);

  Serial.print("Feuer Status: ");
  Serial.println(Feuer);
  

  if (Feuer) {
    digitalWrite(Piezzo, HIGH);
    //Serial.println("Feuer!");
  } else {
    //Serial.println(" - Feuer aus");
    digitalWrite(Piezzo, LOW);
  }
}

//void BluetoothInit() {
//  while (!Serial) {}
//  bleSerial.begin(9600);
//}

//void BluetoothCheck() {
//  if (!bleSerial.available()) {
    //Serial.println("Bluetooth Gerät nicht verbunden");
    //Serial.println("Warten auf Koppelung");
    //delay(1000);
    //Serial.print("Nach Gerät suchen");

//    while (!bleSerial.available()) {
      //Serial.print(".");
      //delay(1000);
//    }
//  }
//}

//void BluetoothGet() {
//  BluetoothCheck();
//  BleOutput = bleSerial.read();
//}

//void BluetoothSend() {
//  BluetoothCheck();
//  bleSerial.write(BleInput);
//}

void SetupAirQuality(int pin) {
  pinMode(pin, INPUT);
}

String GetAirQuality(int pin) {
  AirQualityData = analogRead(pin);

  if (AirQualityData < 80) {
    return "Extrem schlecht";
  } else if (AirQualityData < 150) {
    return "Sehr schlecht";
  } else if (AirQualityData < 220) {
    return "Schlecht";
  } else if (AirQualityData < 300) {
    return "Mittel";
  } else if (AirQualityData < 380) {
    return "Gut";
  } else {
    return "Sehr gut";
  }
}



void setup() {
  Serial.begin(9600);

  pinMode(Piezzo, OUTPUT);
  pinMode(Lichtschalter, INPUT_PULLUP);
  pinMode(Luefter, OUTPUT);

  SetupMonitor();
  //BluetoothInit();
  SetupAirQuality(AirQualityPin);
  SetupHouseLight(Licht);
  SetupTemperature(Temperatursensor);

  EraseMonitor();
}

void loop() {
  Temperatursystem();
  Lichtsystem();
  Feueralarm();
  Lueftersystem();

  EraseMonitor();
  WriteOnMonitor("Temp: " + String(temperatur) + " C", 0);
  WriteOnMonitor("Luft: " + GetAirQuality(AirQualityPin), 1);

  delay(TemperaturUpdateDelay);

  //BluetoothGet();
  //delay(150);
  //Serial.println(BleOutput);
}
