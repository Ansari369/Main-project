#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Ansari";//Replace with your network SSID
const char* password = "333666999@a";//Replace with your network password

ESP8266WebServer server(80);

String page = "";
char input[12];
int count = 0;


int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;

double total = 0;
int count_prod = 0;
void setup()
{
  pinMode(12,INPUT_PULLUP);  //push_button
  pinMode(13,OUTPUT);         //Red_led
  pinMode(15,OUTPUT);         //Green_led
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin(4, 5);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO       ");
  lcd.setCursor(0, 1);
  lcd.print("   GEC MART       ");

  delay(2000);

  lcd.clear();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting...  ");
  }
  Serial.print(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print(" PLZ ADD ITEMS     ");
  lcd.setCursor(0, 1);
  lcd.print("    TO CART          ");

server.on("/", []()
  {
    page = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
    page += "<tr><td>Book</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Chocolate</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Kurkure</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px;height: 50px\"></center></body></html>";
    server.send(200, "text/html", page);
  });
  server.begin();
  Serial.println("Web server started!");
}
void loop()
{
  int a=digitalRead(12);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "300050A3A360", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):25.00      ");
        p1++;
        digitalWrite(15,HIGH);
        delay(2000);
        total = total + 25.00;
        count_prod++;
        digitalWrite(15,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "300050A3A360", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Removed!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        p1--;
        total = total - 25.00;
        count_prod--;
        lcd.clear();
        digitalWrite(13,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        digitalWrite(13,LOW);
        lcd.clear();
        }
      }
      else if ((strncmp(input, "30004F9F3ADA", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Book Added          ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):30.00         ");
        total = total + 30.00;
        digitalWrite(15,HIGH);
        delay(2000);
        p2++;
        count_prod++;
        digitalWrite(15,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "30004F9F3ADA", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Book Removed!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        p2--;
        total = total - 30.00;
        count_prod--;
        lcd.clear();
        digitalWrite(13,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(13,LOW);
        }
      }
      else if ((strncmp(input, "300050B9C910", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Chocolate Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):15.00      ");
        total = total + 15.00;
        digitalWrite(15,HIGH);
        delay(2000);
        count_prod++;
        p3++;
        lcd.clear();
        digitalWrite(15,LOW);
      }
      else if ((strncmp(input, "300050B9C910", 12) == 0) && (a==0))
      {
        if(p3>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Chocolate Removed!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        total = total - 15.00;
        p3--;
        count_prod--;
        lcd.clear();
        digitalWrite(13,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(13,LOW);
        }
      }
      else if ((strncmp(input, "30004F899660", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Kurkure Added            ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):20.00        ");
        total = total + 20.00;
        count_prod++;
        digitalWrite(15,HIGH);
        p4++;
        delay(2000);
        lcd.clear();
        digitalWrite(15,LOW);
      }
      else if ((strncmp(input, "30004F899660", 12) == 0) && (a == 0))
      {
        if(p4>0)
        {
        lcd.clear();
        total = total - 20.00;
        lcd.setCursor(0, 0);
        count_prod--;
        p4--;
        lcd.print("Kurkure Removed!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(13,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(13,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(13,LOW);
        }
      }
      else if (strncmp(input, "300050984EB6", 12) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod:");
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price:");
        lcd.setCursor(6, 1);
        lcd.print(total);
        digitalWrite(15,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(15,LOW);
        lcd.setCursor(0, 0);
        lcd.print("   Thank you        ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping        ");
        digitalWrite(15,LOW);
      }
    }
    c1=p1*25.00;
    c2=p2*30.00;
    c3=p3*15.00;
    c4=p4*20.00;
  }
server.handleClient();
}
