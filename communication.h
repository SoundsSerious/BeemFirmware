#include "application.h"
#include "MDNS.h"
#include <vector>


#define MAX_CLIENTS 4
#define BEEMO_PORT 18330
#define LOG_DEBUG false //5ms log delay

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
  int tickCount = 100;
  int _tick = tickCount - 1; //Tick One Less than tickCount will print first time

  //MDNS
  String hostname = "frisbeem";
  String serverMessage = "HTTP/1.1 200 Ok\n\n<html><body><h1>~HELLO BEEMO!~</h1></body></html>\n\n";
  std::vector<String> subServices;
  MDNS mdns;

  //Client Server Objects
  TCPServer server = TCPServer(BEEMO_PORT);
  TCPClient client;

  //Message Parsing
  String lastMsg;
  String unParsedMsg;

  //Boolean Values
  bool mdns_success;
  bool debugMode = true;
  bool writeNow = true; //Tells log to write. True Means First Time will print
  bool initialConnection = false;

  //Important Functions
  void log(String message,bool force=false);
  void telemetry(String pck, String message);
  void initialize();
  void update();
  void open();
  void close();
  String read();
  void parseStringForMessage(String inputString);
  void handleCommand(String pk, String sk, String arg);

  void tick();

  //Initialize Sub Funcitons
  void initialize_mdns();
  void initialize_server();

  //Telemetry Functions
  void send_telemetry();
  void send_time();
  void send_acl();
  void send_acl_rl();
  void send_gyro();
  void send_vel();
  void send_pos();

  // void serial_sendTelemetry();
  // void com_sendTelemetry();
  // void com_sendRawAcl();
  // void com_sendRawGy();
  // void com_sendDmpAcl();
  // void com_sendWorldAcl();
  // void com_sendGyro();
  // void com_sendMag();
  // void com_sendEuler();
  // void com_sendGravity();

};
