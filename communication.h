#include "application.h"
//#include "observer.h"
//#include "subject.h"

#define MAX_CLIENTS 4
#define BEEMO_PORT 8330

class COM { //, public Subject{
  //In which we send information
  //Obsever so it can recieve notifications
  //Subject model may work to send data to other clients
public:
  Client *_clients[MAX_CLIENTS];
  int numberOfClients;

  byte serverIP[4] = {192,168,1,80};
  TCPClient beemoServer;

  //TCPServer server = TCPServer(BEEMO_PORT);
  TCPClient client;

  //Event Timing
  unsigned long old_time;
  uint8_t retry_count;
  int _tick = 100; //Tick Greater than tickCount will print first time
  int tickCount = 99;

  String input;
  bool debugMode = true;
  bool writeNow = true; //Tells log to write

  //Important Messages
  void log(String message);
  void initialize();
  void update();

  void tick();
  void initialize_cloud();
  int initialize_could_offset(String commandName, int message);
  void handleConnecting();
  void handleNetworking();
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
