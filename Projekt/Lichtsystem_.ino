void Lichtsystem() {
  tasterstatus = digitalRead(Lichtschalter);

  if (tasterstatus == LOW && letzterTasterstatus == HIGH) {
    ToggleLight(Licht);
    delay(50);
  }
  
  letzterTasterstatus = tasterstatus;
}
