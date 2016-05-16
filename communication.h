#include "application.h"
#include "MDNS.h"
#include <vector>


#define MAX_CLIENTS 4
#define BEEMO_PORT 18330

class COM { //, public Subject{
  //In which we send information
  //Obsever so it can recieve notifications
  //Subject model may work to send data to other clients
public:
  Client *_clients[MAX_CLIENTS];
  int numberOfClients;

  IPAddress serverIP;

  //Event Timing
  unsigned long old_time;
  //uint8_t retry_count;
  //uint8_t retry_limit = 10;
  unsigned long read_timeout = 2;
  int tickCount = 10;
  int _tick = tickCount + 1; //Tick Greater than tickCount will print first time

  //MDNS
  String hostname = "frisbeem";
  String serverMessage = "HTTP/1.1 200 Ok\n\n<html><body><h1>~HELLO BEEMO!~</h1></body></html>\n\n";
  std::vector<String> subServices;
  MDNS mdns;
  TCPServer server = TCPServer(BEEMO_PORT);
  TCPClient client;
  bool mdns_success;

  String input;
  bool debugMode = true;
  bool writeNow = true; //Tells log to write
  bool superDebugMode = true; //Write All The Things
  bool alwaysSerial = true;
  bool initialConnection = false;

  //Important Functions
  void log(String message,bool force=false);
  void initialize();
  void update();
  void open();
  void close();
  void read();

  void tick();
  void initialize_cloud();
  int initialize_could_offset(String commandName, int message);
  void initialize_mdns();
  void initialize_server();
  void serial_RealWorldData();
  void serial_RawAclGyrVals();
  void serial_sendTelemetry();
  void com_sendTelemetry();
  void com_sendRawAcl();
  void com_sendRawGy();
  void com_sendDmpAcl();
  void com_sendWorldAcl();
  void com_sendGyro();
  void com_sendMag();
  void com_sendEuler();
  void com_sendGravity();

};
