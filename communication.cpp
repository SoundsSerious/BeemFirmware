#import "communication.h"
#import "globals.h"

void COM::initialize(){
  Serial.begin( 115200 ); //Open Serial...Mmm breakfast
  delay(300);

  while(!Serial.available()){ Particle.process();};

  log("Initlaize:");
  log(WiFi.localIP());
  log(WiFi.subnetMask());
  log(WiFi.gatewayIP());
  log(WiFi.SSID());

  initialize_server();
  initialize_mdns();
}

void COM::initialize_server(){
  server.begin();
}

void COM::initialize_mdns(){
  log("Initlaizing MDNS");
  subServices.push_back("printer");
  log("Setting MDNS Host Name");
  mdns_success = mdns.setHostname( hostname );

  if (mdns_success) {
    log("Host Name Set Successfully");
    mdns_success = mdns.addService("tcp", "beem", BEEMO_PORT, "frisbeem", subServices);
  }

  mdns.addTXTEntry("frsibeem");

  if (mdns_success) {
    log("Starting MDNS");
    mdns_success = mdns.begin();
    log("MDNS Started");
  }
}

void COM::tick(){
  _tick += 1;
  log("tick...");
  if (_tick == tickCount){
    writeNow = true;
  }
  else{
    writeNow = false;
  }
  if (_tick > tickCount){
    _tick = 0;
  }
}

void COM::update(){
  log("Sending MDNS Information");
  mdns.processQueries();
  read();
  send_acl();
  send_gyro();
}

void COM::open(){
  initialConnection = false; //Reset This Flag
  log("Opening COM Server");
  if ( !client.connected() ){
    log("Checking Server For Client");
    client = server.available();
  }
  else{ log("Client Connected");}

  if (client){
    log("Connected To Client");
    initialConnection = true;
  }
  else{ log("No Client :(");}
}

void COM::close(){
  if ( initialConnection ){
    //client.flush();
    log("Closing");
    //client.stop();
  }
}

void COM::read(){
  String message;
  log("Checking For Input");
  log(String(client.available())+" In Client Buffer");
  while ( client.available()) {
    char out = client.read();
    message += String( out );
  }
  log("Got "+message);
}

void COM::log(String message, bool force){
  //Super Debug Mode Will Try Both Serial And WiFi-zle if it's turn
  //We will default to serial always for zeee robust debugging
  if ( writeNow || force){
    Serial.println( "LOG:\t"+message );
    if (initialConnection){
      server.println( "LOG:\t"+message );
    }
  }
  /*#ifdef LOG_DEBUG
    log("debug delay");
    delay(10);
  #endif*/
}

void COM::telemetry(String pck, String message){
  //Send telemetry every opprotunity only on wifi
  if ( initialConnection ){
    server.println( "TEL:\t"+pck+":\t"+ message );
  }
}


void COM::send_gyro(){
  //Send Gyro Values
  telemetry("GYR",  String(frisbeem._mpu.G.x,DEC)+","+
                    String(frisbeem._mpu.G.y,DEC)+","+
                    String(frisbeem._mpu.G.z,DEC)+";");
}
void COM::send_acl(){
  //Send ACL Values
  telemetry("ACL",  String(frisbeem._mpu.A.x,DEC)+","+
                    String(frisbeem._mpu.A.y,DEC)+","+
                    String(frisbeem._mpu.A.z,DEC)+";");
}
