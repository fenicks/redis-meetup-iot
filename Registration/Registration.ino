#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define MENUCMD(NAME,LABEL,VALUE)  { #NAME, LABEL, strdup(VALUE), NAME##_func }
#define MENUFCT(NAME) void NAME##_func(void)

typedef void (*CommandFunc_t)(void);

typedef struct Command_s {
  char* name;
  char* label;
  char* value;
  CommandFunc_t func;
} Command_t;

CommandFunc_t CurrentState;

MENUFCT(menu);
MENUFCT(wifissid);
MENUFCT(wifipass);
MENUFCT(wifitest);
MENUFCT(redishost);
MENUFCT(redisport);
MENUFCT(redispass);
MENUFCT(redistest);
MENUFCT(firstname);
MENUFCT(lastname);
MENUFCT(email);
MENUFCT(screenname);
MENUFCT(githubuser);
MENUFCT(githubproject);
MENUFCT(githubtest);
MENUFCT(twitteruser);
MENUFCT(twittertest);
MENUFCT(testADC);
MENUFCT(test);
MENUFCT(save);

Command_t commands[] =
{
  MENUCMD (menu, "Refresh menu", ""),
  MENUCMD (wifissid, "WIFI network SSID (to check connection)", "xxxxx"),
  MENUCMD (wifipass, "WIFI password (to check connection)", "xxxxx"),
  //  MENUCMD (wifitest, "WIFI connection test", ""),
  MENUCMD (redishost, "Redis cluster hostname or IP (to check connection and register)", "localhost"),
  MENUCMD (redisport, "Redis cluster port (to check connection and register)", "6379"),
  //  MENUCMD (redispass, "Redis db password (to check connection and register)", ""),
  //  MENUCMD (redistest, "Redis connection test (needs a working WIFI)", ""),
  MENUCMD (firstname, "Firstname (for pretty display)", "Christian"),
  MENUCMD (lastname, "Lastname (for pretty display)", "Kakesa"),
  MENUCMD (email, "Email (to send you the workshop materials)", "christian@kakesa.net"),
  MENUCMD (screenname, "Screenname (to be displayed on video projector)", "fenicks"),
  MENUCMD (githubuser, "GitHub account (to check the project creation)", "fenicks"),
  MENUCMD (githubproject, "GitHub Project (to check the project creation)", "redis-meetup-iot"),
  //  MENUCMD (githubtest, "GitHub account and project test (needs a working WIFI)", ""),
  MENUCMD (twitteruser, "Twitter account (to check the twits)", "christiankakesa"),
  //  MENUCMD (twittertest, "Twitter account test (needs a working WIFI)", ""),
  MENUCMD (testADC, "Test the sensor", ""),
  MENUCMD (test, "Check all the informations without registration", ""),
  MENUCMD (save, "Register your details and the device MAC address in the cluster", ""),
  0
};

Command_t *getCommandByName(const char* name) {
  Command_t *it = commands;
  while ((*(char*)it != 0) && (strcmp(name, it->name))) it++;
  return it;
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  CurrentState = menu_func;
}

void loop() {
  CurrentState();
}
