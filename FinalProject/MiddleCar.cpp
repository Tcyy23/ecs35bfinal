
// hw3_miou_2022.cpp

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

Auto_V car;




int
main()
{
  cout << "===== This is the program for middle car =====\n\n";

  Json::Value mes;
  mes = car.send_message("emergency", car.dump2JSON());

  HttpClient httpclient_l("http://127.0.0.1:8881");
  hw5Client myClient_l(httpclient_l, JSONRPC_CLIENT_V2);

  HttpClient httpclient_r("http://127.0.0.1:8883");
  hw5Client myClient_r(httpclient_r, JSONRPC_CLIENT_V2);

  double ratingL, ratingR;
  Json::Value myv;

  try {
    myv = myClient_l.request(mes);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << myv.toStyledString() << endl;

    ratingL = car.cal_rating(myv);

  try {
    myv = myClient_r.request(mes);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << myv.toStyledString() << endl;

    ratingR = car.cal_rating(myv);
  

  cout<< "Left, Rating: " << ratingL << endl;
  cout<< "Right Rating: " << ratingR << endl;
    {
      cout << "\n Car decision is: ";
        if(ratingL < ratingR)
        {
            //error_code = -1;
            std::cout << "I will hit left" << std::endl;
        }
        else if(ratingL > ratingR)
        {
            //error_code = -2;
            std::cout << "I will hit right" << std::endl;
        }
        else if(ratingL == ratingR)
        {
            //error_code = 0;
            std::cout << "I will hit right because it protect my passager more" << std::endl;
        }
    }

  return 0;
}


