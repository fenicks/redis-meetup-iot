MENUFCT(firstname) {
  Serial.println();
  Serial.println("Please enter your firstname");
  Serial.print("[");
  Serial.print(getCommandByName("firstname")->value);
  Serial.println("] >");
  CurrentState = firstname_answer;
}

void firstname_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("firstname")->value);
    getCommandByName("firstname")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(lastname) {
  Serial.println();
  Serial.println("Please enter your lastname");
  Serial.print("[");
  Serial.print(getCommandByName("lastname")->value);
  Serial.println("] >");
  CurrentState = lastname_answer;
}

void lastname_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("lastname")->value);
    getCommandByName("lastname")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(email) {
  Serial.println();
  Serial.println("Please enter your email");
  Serial.println("There is no sanity check, please enter it carefully");
  Serial.print("[");
  Serial.print(getCommandByName("email")->value);
  Serial.println("] >");
  CurrentState = email_answer;
}

void email_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("email")->value);
    getCommandByName("email")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

MENUFCT(screenname) {
  Serial.println();
  Serial.println("Please enter your screenname");
  Serial.println("You can simply use your firstname and lastname");
  Serial.println("Make it original, it has to be unique in the room");
  Serial.print("[");
  Serial.print(getCommandByName("screenname")->value);
  Serial.println("] >");
  CurrentState = screenname_answer;
}

void screenname_answer() {
  static String answer = "";
  if (Serial.available() > 0) {
    answer = Serial.readString();
    answer.replace("\n", "");
    answer.replace("\r", "");
    while (Serial.available() > 0) Serial.read();
    free(getCommandByName("screenname")->value);
    getCommandByName("screenname")->value = strdup(answer.c_str());
    CurrentState = menu_func;
  }
}

