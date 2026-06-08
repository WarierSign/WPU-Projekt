void Feueralarm() {
  Feuer = (temperatur >= Feuertemp);
  
  Serial.print(Feuer);

  if (Feuer) {
    digitalWrite(Piezzo, HIGH);
    Serial.println(" - Feuer an");
  } else {
    Serial.println(" - Feuer aus");
    digitalWrite(Piezzo, LOW);
  }
}
