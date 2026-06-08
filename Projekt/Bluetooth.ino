void BluetoothInit() {
  while (!Serial) {}
  bleSerial.begin(9600);
}

void BluetoothCheck() {
  if (!bleSerial.available()) {
    Serial.println("Bluetooth Gerät nicht verbunden");
    Serial.println("Warten auf Koppelung");
    delay(1000);
    Serial.print("Nach Gerät suchen");

    while (!bleSerial.available()) {
      Serial.print(".");
      delay(1000);
    }
  }
}

void BluetoothGet() {
  BluetoothCheck();
  BleOutput = bleSerial.read();
}

void BluetoothSend() {
  BluetoothCheck();
  bleSerial.write(BleInput);
}
