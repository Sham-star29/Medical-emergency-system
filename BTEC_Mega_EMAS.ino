#include <LiquidCrystal.h>


LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


#define GsM_RF_iD Serial3
#define RF_iD Serial3
#define gsm_g GsM_RF_iD
#define Serial Serial
#define ard_node Serial2



float temp_r, temp_fn;
#define splash splash2

int tup = 20;


String xy;
String user[] = { "SHAMRUTHA J A" };
String num[] = { "+91" };



String ta = "";
unsigned int pul, pulfn, pulStat;
String id_fn;

int hb_r, hb_fn, spo2;
int tu;
int H_B, SPO_2;
int dis_t = 3;
int disp = dis_t;
float celsius, fahrenheit;

int id = 3;
int rf_status = 0, sens_stat = 0;
void (*resetFunc)(void) = 0;
//String unum = "+";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.begin(115200);
  ard_node.begin(115200);

  GsM_RF_iD.begin(9600);
  RF_iD.begin(9600);
  gsm_g.begin(9600);

  LcDSet();

  delay(1000);
  SendSmS(num[0], "GSM Initialized.", "", "Sending SMS.........");

  delay(1000);
  String SS = "";
  String SSs = "";
  while (ard_node.available() > 0) {
    char S = ard_node.read();
    SS += S;
    delay(10);
  }
  lcd.clear();
}


void LcDSet() {
  lcd.begin(20, 4);
  lcd.clear();

  lcd.home();


  splash(0, "Emergency");
  splash(1, "Medical");
  splash(2, "Assistant");
  splash(3, "System");
  delay(2000);
  lcd.clear();
}


void loop() {
  // put your main code here, to run repeatedly:
  getRF_iD();

  getArd();
  temp_fn = (temp_r * 9 / 5) + 32;
  hb_fn = H_B;
  spo2 = SPO_2;




  setDisplay();

  delay(30);
}



void getArd() {
  String SS = "";
  String SSs = "";
  while (ard_node.available() > 0) {
    char S = ard_node.read();
    SS += S;
    delay(10);
  }
  if (SS.length() > 0) {
    //    Serial.println(SS);
    String hb = getSplitValue(SS, ',', 0);
    String sp = getSplitValue(SS, ',', 1);
    String te = getSplitValue(SS, ',', 2);


    H_B = hb.toInt();
    SPO_2 = sp.toInt();
    temp_r = te.toFloat();


    ard_node.flush();
  }
}


void setDisplay() {

  disp++;
  //  Serial.println(disp);
  if (disp > dis_t) {
    lcd.setCursor(0, 0);
    lcd.print("T :       ");
    lcd.setCursor(3, 0);
    lcd.print(temp_fn, 1);
    lcd.print(char(223));
    lcd.print(" F    ");
    lcd.setCursor(0, 1);
    lcd.print("HB:        ");
    lcd.setCursor(3, 1);
    lcd.print(hb_fn);
    lcd.print(" BPM");
    lcd.setCursor(10, 1);
    lcd.print("SPO2:    ");
    lcd.setCursor(15, 1);
    lcd.print(spo2);
    lcd.print("% ");
    splash(2, "");
    disp = 0;
  }
}

void getRF_iD() {
  xy = "";

  while (RF_iD.available()) {
    int x = RF_iD.read();
    //    Serial.println(x);
    xy += x;
    delay(10);
  }

  if (xy.length() > 0) {
    Serial.print("id : ");
    Serial.println(xy);
    if (xy == "515648485148565766545155") {

      id = 0;
      splash(2, "Prescribed Tablets");
      delay(2000);
      String msg = " Prescribed Tablets \n";
      msg += "Paracetamol \n!";
      msg += "Cetirizine \n!";
      String msgg = "Hello Mr / Ms / Mrs : ";
      msgg += user[id];

      Serial.print(msgg);
      Serial.println(msg);

      SendSmS(num[id], msgg, msg, "Sending SMS.........");
      rf_status = 1;

    } else if (xy == "515648485148545552525066") {

      id = 0;

      rf_status = 1;

      splash(2, "Prescribed Tablets");
      delay(2000);
      String msg = " Prescribed Tablets \n";
      msg += "Paracetamol (Acetaminophen) \n!";
      msg += "Aspirin \n!";
      String msgg = "Hello Mr / Ms / Mrs : ";
      msgg += user[id];

      Serial.print(msgg);
      Serial.println(msg);
      SendSmS(num[id], msgg, msg, "Sending SMS.........");
    }
  }
}
