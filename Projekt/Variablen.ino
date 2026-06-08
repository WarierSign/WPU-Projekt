int Temperatursensor = A0;
int AirQualityPin = A1;
int RXDPin = 2;
int TXDPin = 3;
int Lichtschalter = 4;
int Luefter = 5;
int Licht = 7;
int Piezzo = 8;

int RohOuputTemperatur = 0;
int temperatur;
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
int BleOutput;
int BleInput;

Thermistor* thermistor;
