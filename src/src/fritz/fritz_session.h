#pragma once
#include "fritz_thermostat.h"
#include <HTTPClient.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <WString.h>

class Session
{
private:
  const std::string fritz_host;
  int fritz_port;
  const char *loginPath = "/login_sid.lua?version=2";

  std::string mUsername;
  std::string mPassword;

  std::string mChallenge;
  std::string mSID;

  bool query_challenge();
  bool query_session_id();

public:
  Session(const char *host, int port, const char *username, const char *password);
  ~Session();

  bool establish_connection();
  std::string sid();
  int post_request(HTTPClient &http, const char *path, const char *post_template);
  String query_data(const char *path, const char *post_template);
  bool query_devices(std::vector<Thermostat> &thermostats);
  bool post_thermostat_state(Thermostat &thermostat);
};