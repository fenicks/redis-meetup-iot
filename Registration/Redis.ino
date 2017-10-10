MENUFCT(redishost) {
  Serial.println();
  Serial.println("Please enter the redis server hostname or IP address");
  Serial.print("[");
  Serial.print(getCommandByName("redishost")->value);
  Serial.println("] >");
  CurrentState = redishost_answer;
}

void redishost_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("redishost")->value);
    getCommandByName("redishost")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(redispass) {
  Serial.println();
  Serial.println("Please enter the redis db password");
  Serial.print("[");
  Serial.print(getCommandByName("redispass")->value);
  Serial.println("] >");
  CurrentState = redispass_answer;
}

void redispass_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("redispass")->value);
    getCommandByName("redispass")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(redisport) {
  Serial.println();
  Serial.println("Please enter the redis server port number");
  Serial.print("[");
  Serial.print(getCommandByName("redisport")->value);
  Serial.println("] >");
  CurrentState = redisport_answer;
}

void redisport_answer() {
  static int answer = 0;
  if (Serial.available() > 0) {
    answer = Serial.parseInt();
    while (Serial.available() > 0) Serial.read();
    if ((answer <= 0) || (answer > 65535)) {
      Serial.println("Please enter a valid port number");
      CurrentState = redisport_func;
      return;
    }
    // Should always be 5 numbers + null except for initial value
    realloc(getCommandByName("redisport")->value, 6);
    itoa(answer, getCommandByName("redisport")->value, 10);
    CurrentState = menu_func;
  }
}

MENUFCT(redistest) {
  Serial.println();
  if (WiFi.status() != WL_CONNECTED)
    wifitest_func();
  Serial.print("Testing Redis endpoint DNS resolution [");
  Serial.print(getCommandByName("redishost")->value);
  Serial.print("]...");
  IPAddress redisEndpointIP;
  WiFi.hostByName(getCommandByName("redishost")->value, redisEndpointIP);
  Serial.print("IP:");
  Serial.println(redisEndpointIP);

  Serial.print("Testing Redis connection [");
  Serial.print(redisEndpointIP);
  Serial.print(":");
  Serial.print(getCommandByName("redisport")->value);
  Serial.print("]...");
  WiFiClient redis;
  if (!redis.connect(redisEndpointIP, atoi(getCommandByName("redisport")->value))) {
    Serial.println(" Failed");
    CurrentState = redishost_func;
    return;
  }
  Serial.println("OK...");
  //Serial.print("Testing Redis authentication (AUTH)...");
  //redis.print((String("*2\r\n$4\r\nAUTH\r\n$3\r\n")+getCommandByName("redispass")->value+"\r\n").c_str());
  //delay(100);
  //while (redis.available()!=0)
  //  Serial.print((char)redis.read());

  Serial.print("Testing Redis health (INFO)...");
  redis.print("*1\r\n$4\r\nINFO\r\n");
  delay(100);
  if (!redis.find("redis_version:")) {
    Serial.println("No redis_version answer to INFO");
    CurrentState = redishost_func;
    return;
  }
  Serial.println("OK");
  CurrentState = menu_func;
}

