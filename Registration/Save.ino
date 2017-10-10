#include "RedisClient.h"

RedisClient_t client;
RedisCommand_t cmd;

MENUFCT(save) {
  test_func(); if (CurrentState != menu_func) return;
  Serial.println();
  Serial.print("Registration...");

  redisclient_init(client, getCommandByName("redishost")->value, atoi(getCommandByName("redisport")->value),getCommandByName("redispass")->value);
  redisclient_setpipelinemaxsize(client, 1);
  char key[20] = "r:";
  strcat(key, WiFi.macAddress().c_str());

  // Delete an eventually existing key to avoid a TYPE conflict
  rediscommand_init(cmd);
  rediscommand_add(cmd, "DEL");
  rediscommand_add(cmd, key);
  redisclient_send(client, cmd);

  rediscommand_init(cmd);
  rediscommand_add(cmd, "HMSET");
  rediscommand_add(cmd, key);
  rediscommand_add(cmd, "macaddr");  rediscommand_add(cmd, WiFi.macAddress().c_str());
  rediscommand_add(cmd, "firstname");  rediscommand_add(cmd, getCommandByName("firstname")->value);
  rediscommand_add(cmd, "lastname");  rediscommand_add(cmd, getCommandByName("lastname")->value);
  rediscommand_add(cmd, "email");  rediscommand_add(cmd, getCommandByName("email")->value);
  rediscommand_add(cmd, "screenname");  rediscommand_add(cmd, getCommandByName("screenname")->value);
  rediscommand_add(cmd, "githubuser");  rediscommand_add(cmd, getCommandByName("githubuser")->value);
  rediscommand_add(cmd, "githubproject");  rediscommand_add(cmd, getCommandByName("githubproject")->value);
  rediscommand_add(cmd, "twitteruser");  rediscommand_add(cmd, getCommandByName("twitteruser")->value);
  redisclient_send(client, cmd);

  rediscommand_init(cmd);
  rediscommand_add(cmd, "SADD");
  rediscommand_add(cmd, "devices");
  rediscommand_add(cmd, WiFi.macAddress().c_str());
  redisclient_send(client, cmd);

  rediscommand_init(cmd);
  rediscommand_add(cmd, "PUBLISH");
  rediscommand_add(cmd, "refreshdevices");
  rediscommand_add(cmd, WiFi.macAddress().c_str());
  redisclient_send(client, cmd);

  CurrentState = menu_func;
}

MENUFCT(test) {
  Serial.println();
  Serial.println("Testing...");
  wifitest_func(); if (CurrentState != menu_func) return;
  redistest_func(); if (CurrentState != menu_func) return;
  githubtest_func(); if (CurrentState != menu_func) return;
  twittertest_func(); if (CurrentState != menu_func) return;
  return;
}

