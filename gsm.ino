
void SendSmS( String NuM, String MsG , String gps, String LcD)
{
  lcd.setCursor(0, 0);
  lcd.print(LcD);
  lcd.setCursor(0, 1);
  lcd.print(".");
  gsm_g.println("AT");
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  gsm_g.println("AT+CMGF=1");    //Sets the gsm_g Module in Text Mode
  lcd.print(".");
  delay(1000);
  lcd.print("."); // Delay of 1000 milli seconds or 1 second
  gsm_g.println("AT+CMGS=\"" + NuM + "\"\r"); //
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  //  gsm_g.print("Hello ");
  gsm_g.print(MsG);
  gsm_g.print(gps);
  delay(1000);
  lcd.print(".");
  gsm_g.println((char)26);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  lcd.clear();

}
