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
