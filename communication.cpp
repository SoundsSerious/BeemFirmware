#include "communication.h"

void COM::initialize(){
  // The following line will wait until you connect to the Spark.io using
  //serial and hit enter. This gives you enough time to start capturing the
  //data when you are ready instead of just spewing data to the UART.
  Serial.begin( 115200 );
  log("Initlaize");
  // So, open a serial connection using something like:
  log(WiFi.localIP());
  log(WiFi.subnetMask());
  log(WiFi.gatewayIP());
  log(WiFi.SSID());

  //Start The Server Hijacking This for now
  beemoServer.connect(serverIP,BEEMO_PORT);
  if (beemoServer.connected()){
    log("successfully connected to beemo server");
  }
  else{
    log("beemo server connection failed");
  }

}

void COM::tick(){
  _tick += 1;
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
  handleNetworking();
}

void COM::log(String message){
  if (writeNow){ //Outer Loop Is set by events
    if (debugMode){ //Default Debug Handler
      //Serial.println( message );
      if (beemoServer.connected()){
        beemoServer.print(Time.timeStr());
        beemoServer.print("\t");
        beemoServer.println( message );
      }
    }
  }
}

void COM::handleConnecting(){
  //Got this from web... never really worked as intended
  if(millis() - old_time >= 2000){
     if(retry_count < 10){
         if(!WiFi.ready()){
             WiFi.connect();
             retry_count++;

         }
         else if (!Particle.connected()){
             Particle.connect();
             retry_count++;
         }
     }
     else{
         WiFi.off();
         retry_count = 0;
         WiFi.on();
     }
     old_time = millis();
  }
}

void COM::handleNetworking(){
  //Client Connection
  if (beemoServer.connected()) {
    // echo all available bytes back to the client
    log("Client Connected...");

    //Check If Client Connected
    if (beemoServer.available()){
      String thisCom;
      thisCom.reserve(256);
      thisCom = "";
      int count = 0;

      //Read Data While Available
      while (beemoServer.available()) {
        input = client.read();
        thisCom += input;
        if (input.length()) count++;
        //Attempt to prevent this com overflow
        if (count > 100){
          break;
        }
      }
      log(String("Got ")+thisCom);
      beemoServer.flush();
    }
  } else {
    // if no client is yet connected, check for a new connection and wait
    log("Checking For Beemo Server...");
    beemoServer.connect(serverIP,BEEMO_PORT);
  }
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
