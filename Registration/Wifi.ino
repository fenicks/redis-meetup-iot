uint8_t nbNetworks;

MENUFCT(wifissid) {
  Serial.println();
  Serial.print("Scanning Networks...");
  nbNetworks = WiFi.scanNetworks();
  Serial.println(" done");
  if (nbNetworks == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(nbNetworks);
    Serial.println(" networks found");
    for (int i = 0; i < nbNetworks; ++i) {
      Serial.print(i); Serial.print(": "); Serial.print(WiFi.SSID(i));
      Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print("dB)");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : " secured");
      delay(10);
    }
  }
  Serial.println("");
  Serial.println("Please select a WiFi network SSID from the list");
  Serial.print("[");
  Serial.print(getCommandByName("wifissid")->value);
  Serial.println("] > ");

  CurrentState = wifissid_answer;
}

void wifissid_answer() {
  static int choice = -1;
  if (Serial.available() > 0) {
    choice = Serial.parseInt();
    while (Serial.available() > 0) Serial.read();
    if ((choice < 0) || (choice >= nbNetworks)) {
      Serial.print("Bad choice : "); Serial.println(choice);
      Serial.print("Same player shoot again... (between 0 and "); Serial.print(nbNetworks - 1); Serial.println(")");
      CurrentState = wifissid_func;
      return;
    }
    free(getCommandByName("wifissid")->value);
    getCommandByName("wifissid")->value = strdup(WiFi.SSID(choice).c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(wifipass) {
  Serial.println();
  Serial.print("Please enter the password for ");
  Serial.println(getCommandByName("wifissid")->value);
  Serial.print("[");
  Serial.print(getCommandByName("wifipass")->value);
  Serial.println("] >");
  CurrentState = wifipass_answer;
}

void wifipass_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("wifipass")->value);
    getCommandByName("wifipass")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(wifitest) {
  Serial.println();
  Serial.print("Testing Wifi connection [");
  Serial.print(getCommandByName("wifissid")->value);
  Serial.print("/");
  Serial.print(getCommandByName("wifipass")->value);
  Serial.print("]...");
  // Refresh available network list (if wifissid was not called before)
  nbNetworks = WiFi.scanNetworks();
  // Find SSID entry in the available networks
  int i = 0;
  while ((i < nbNetworks) && (strcmp(WiFi.SSID(i).c_str(), getCommandByName("wifissid")->value))) i++;
  if (i == nbNetworks) {
    Serial.println("The selected WiFi network is no longuer available, please choose again");
    CurrentState = wifissid_func;
    return;
  }
  // Try to connect, eventually with a password
  if (WiFi.encryptionType(i) == ENC_TYPE_NONE)
    WiFi.begin(getCommandByName("wifissid")->value);
  else
    WiFi.begin(getCommandByName("wifissid")->value, getCommandByName("wifipass")->value);
  // Wait for connection with a timeout
  uint8_t count = 0;
  while ((WiFi.status() != WL_CONNECTED) && (count < 40)) {
    delay(500);
    Serial.print(".");
    count++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Unable to connect to the selected WiFi, please choose again");
    CurrentState = wifissid_func;
    return;
  }
  Serial.println("OK");
  CurrentState = menu_func;
  Serial.print("WiFi (");
  Serial.print(WiFi.macAddress());
  Serial.print(") connected with IP ");
  Serial.println(WiFi.localIP());
  Serial.print("DNS0 : ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS1 : ");
  Serial.println(WiFi.dnsIP(1));

}

