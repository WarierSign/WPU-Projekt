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
