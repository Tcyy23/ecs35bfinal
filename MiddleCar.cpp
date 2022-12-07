

#include "ecs36b_Common.h"
#include "AutoVehicle.h"

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>
#include "ecs36b_Exception.h"

using namespace jsonrpc;
using namespace std;

Car car;

int main()
{
  cout << "-----Client Car-----" << endl << endl;

  Json::Value message;
  message = car.sendMessage("emergency", car.dump2JSON());

  HttpClient httpclientL("http://localhost:8383");
  hw5Client clientL(httpclientL, JSONRPC_CLIENT_V2);

  HttpClient httpclientR("http://localhost:8384");
  hw5Client clientR(httpclientR, JSONRPC_CLIENT_V2);

  int ratingL, ratingR;
  Json::Value leftValue;
  Json::Value rightValue;

  try {
    leftValue = clientL.request(message);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << leftValue.toStyledString() << endl;


  try {
    rightValue = clientR.request(message);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << rightValue.toStyledString() << endl;

  car.makeDecision(leftValue, rightValue);

  return 0;
}


