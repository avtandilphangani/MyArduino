#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

#define DHT11_PIN 6
#define RELE_PIN 10
float last_temp;
float last_humi;

int out_temp_max = 28;
 int out_temp_min = 26;
 int out_temp;

void print_temperature(float temperature){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Temp: "); 
  lcd.print(last_temp = temperature);
  lcd.print((char)223);
  lcd.print("C");
}
void print_humidity(float humidity){
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(last_humi = humidity);
  lcd.print("%");  
}
void setup(){
  lcd.begin(16, 2);
  pinMode(RELE_PIN, OUTPUT); 
  out_temp = out_temp_max;
}

void loop(){
 int chk = DHT.read11(DHT11_PIN);
  
// ეკრანში დაბეჭდავს, თუ რომელიმე მონაცემი შეიცვალა და თუ დაბეჭდა last_ ცვლადშიც დამახსოვრდება ეს მონაცემი, რომ შემდეგ გაზომვას შედარდეს   
  if (last_temp != DHT.temperature)  print_temperature(DHT.temperature);
  if (last_humi != DHT.humidity) print_humidity(DHT.humidity);  
  
  if (last_temp >= out_temp){
    digitalWrite(RELE_PIN, LOW);
    out_temp = out_temp_min;
  }
  else {
    digitalWrite(RELE_PIN, HIGH);
    out_temp = out_temp_max;
  }    
    
  
  
  delay(2000); /* ეს მონაცემი უნდა, 1000 ადრეა და ვერ ასწრეს გაზომვას, წერს -99.00, თითქოს ცარიელი პინიდან ისე, ანუ დაჩიკის რეაგირებას უნდა დრო */
}
