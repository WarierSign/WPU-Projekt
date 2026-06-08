void SetupHouseLight(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void ToggleLight(int pin) {
  Lichtstatus = !Lichtstatus;
  digitalWrite(pin, Lichtstatus ? HIGH : LOW);
}
