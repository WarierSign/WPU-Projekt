void Lueftersystem() {
  if (temperatur >= Lueftertemp) {
    digitalWrite(Luefter, HIGH);
    Luefterstatus = true;
  } else {
    digitalWrite(Luefter, LOW);
    Luefterstatus = false;
  }
}
