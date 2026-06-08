void setup() {
  Serial.begin(9600);

  pinMode(Piezzo, OUTPUT);
  pinMode(Lichtschalter, INPUT_PULLUP);
  pinMode(Luefter, OUTPUT);

  SetupMonitor();
  BluetoothInit();
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
}
