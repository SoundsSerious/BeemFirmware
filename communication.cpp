#include "communication.h"


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
}

void COM::open(){
  initialConnection = false; //Reset This Flag
  log("Opening COM Server");
  if ( !client.connected() ){
    client = server.available();
  }
  else{ log("Client Connected");}

  if (client){
    log("Connected To Client");
    initialConnection = true;
    read();
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
  unsigned long lastdata = millis();
  while ( client.available() || (millis()-lastdata < read_timeout)) {
    char out = client.read();
      message += String( out );
  }//while ( client.available() || (millis()-lastdata < timeout))
  client.read();
  log("Got "+message);
}

void COM::log(String message, bool force){
  //Super Debug Mode Will Try Both Serial And WiFi-zle if it's turn
  //We will default to serial always for zeee robust debugging
  if ( writeNow || force){
    Serial.println( message );
    if (initialConnection){
      server.println( message );
    }
  }
  delay(3);
}

void COM::telemetry(String message){
  //Send telemetry every opprotunity
  server.println( "TEL:\t"+ message );
}


/*void COM::serial_RealWorldData(){
  //Output Data On Serial
  Serial.print("GYR:\t");
  Serial.print( String(G.x,DEC));Serial.print("||\t");
  Serial.print( String(G.y,DEC));Serial.print("||\t");
  Serial.print( String(G.z,DEC));
  Serial.print("\tACL:\t");
  Serial.print( String(aa.x,DEC));Serial.print("||\t");
  Serial.print( String(aa.y,DEC));Serial.print("||\t");
  Serial.println(String(aa.z,DEC));
}

void COM::serial_RawAclGyrVals(){

  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.print("\t");
  Serial.println(packetSize);

}

void COM::serial_sendTelemetry(){
  //serial_RawAclGyrVals();
  serial_RealWorldData();
}

void COM::com_sendTelemetry(){
  //Send All Types O' Data
  com_sendDmpAcl();
  com_sendRealAcl();
  com_sendWorldAcl();
  com_sendGyro();
  com_sendGravity();
  com_sendMag();
  //com_sendRawAcl();
  //com_sendRawGy();
}

void COM::com_sendRawAcl(){

  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,RACL:\t");
  server.write(String(ax,DEC));
  server.write("\t");
  server.write(String(ay,DEC));
  server.write("\t");
  server.write(String(az,DEC));
  server.write("\n");
}

void COM::com_sendRawGy(){

  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,RGY:\t");
  server.write(String(gx,DEC));
  server.write("\t");
  server.write(String(gy,DEC));
  server.write("\t");
  server.write(String(gz,DEC));
  server.write("\n");
}

void COM::com_sendDmpAcl(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,ACL:\t");
  server.write(String(aa.x,DEC));
  server.write("\t");
  server.write(String(aa.y,DEC));
  server.write("\t");
  server.write(String(aa.z,DEC));
  server.write("\n");
}

void COM::com_sendRealAcl(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,REAL:\t");
  server.write(String(aaReal.x,DEC));
  server.write("\t");
  server.write(String(aaReal.y,DEC));
  server.write("\t");
  server.write(String(aaReal.z,DEC));
  server.write("\n");
}

void COM::com_sendWorldAcl(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,WORLD:\t");
  server.write(String(aaWorld.x,DEC));
  server.write("\t");
  server.write(String(aaWorld.y,DEC));
  server.write("\t");
  server.write(String(aaWorld.z,DEC));
  server.write("\n");
}

void COM::com_sendGyro(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,GY:\t");
  server.write(String(G.x,DEC));
  server.write("\t");
  server.write(String(G.y,DEC));
  server.write("\t");
  server.write(String(G.z,DEC));
  server.write("\n");
}

void COM::com_sendMag(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,MAG:\t");
  server.write(String(M.x,DEC));
  server.write("\t");
  server.write(String(M.y,DEC));
  server.write("\t");
  server.write(String(M.z,DEC));
  server.write("\n");
}

void COM::com_sendEuler(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,EUL:\t");
  server.write(String(euler[0],DEC));
  server.write("\t");
  server.write(String(euler[1],DEC));
  server.write("\t");
  server.write(String(euler[2],DEC));
  server.write("\n");
}

void COM::com_sendGravity(){
  server.write("TIME:\t");
  server.write(String(now,DEC));
  server.write("\t,GRAV:\t");
  server.write(String(gravity.x,DEC));
  server.write("\t");
  server.write(String(gravity.y,DEC));
  server.write("\t");
  server.write(String(gravity.z,DEC));
  server.write("\n");
}

void COM::initialize_cloud(){
  //Initialize_offset variables
  initialize_could_offset("ax_offset", ax_offset);
  initialize_could_offset("ay_offset", ay_offset);
  initialize_could_offset("az_offset", az_offset);
  initialize_could_offset("gx_offset", gx_offset);
  initialize_could_offset("gy_offset", gy_offset);
  initialize_could_offset("gz_offset", gz_offset);
}

int COM::initialize_could_offset(String commandName, int message){

    if (Particle.variable(commandName, message)==false)
  {
      could_offsets_registered = false;
  }
  could_offsets_registered = true;

}*/
