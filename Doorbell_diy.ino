#include <RCSwitch.h> //https://github.com/sui77/rc-switch
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);
void send_notif();


ESP8266WiFiMulti WiFiMulti;
WiFiClientSecure client;
RCSwitch mySwitch = RCSwitch();

const char* b;
const String data = "101011101001010000100011";
const char* host = "api.pushbullet.com";
const int httpsPort = 443;
const char* PushBulletAPIKEY = "o.xxxxxxxxxxxxxxxxxxxxxx"; //pushbullet api key
const String pushbullet_dev = "xxxxxxxxxxxxxxxxxxx"; //pushbullet device iden
int ring_pin = 2; //Ring Trig Pin
int RFID_PIN = 4; //RFID Data Pin

void setup() {
  pinMode(ring_pin, OUTPUT);
  digitalWrite(ring_pin, LOW);
  Serial.begin(9600);
  mySwitch.enableReceive(RFID_PIN);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "KEY");
  Serial.println("Setup Finised");
}

void loop() {
  if (mySwitch.available()) {
    b = dec2binWzerofill(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength());
    if (String(b) == data) {
      Serial.println("Data Rcv");
      Serial.println(b);
      if ((WiFiMulti.run() == WL_CONNECTED)) {
        WiFiClient client;
        digitalWrite(ring_pin, HIGH);
        delay(1000);
        digitalWrite(ring_pin, LOW);
        send_notif();
      }
    } else {
      Serial.println("Garbage Data Rcv");
      Serial.println(b);
    }
    mySwitch.resetAvailable();
  }
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
  static char bin[64];
  unsigned int i = 0;

  while (Dec > 0) {
    --------------------------------------------------++
    bin[32 + i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j < bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';

  return bin;
}

void send_notif() {
  client.setInsecure();
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/v2/pushes";
  String messagebody_note = "{\"type\": \"note\", \"title\": \"Hello !\", \"body\": \"Este cineva la poarta!\" ,\"source_device_iden\": \"" + pushbullet_dev + "\"}\r\n";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + PushBulletAPIKEY + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " +
               String(messagebody_note.length()) + "\r\n\r\n");
  client.print(messagebody_note);


  Serial.println("req sent");

  while (client.available() == 0);

  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}
