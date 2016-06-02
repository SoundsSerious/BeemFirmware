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
  lastMsg = read();
  parseStringForMessage(lastMsg);
  //send_acl();
  //send_gyro();
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

String COM::read(){
  String message;
  log("Checking For Input");
  log(String(client.available())+" In Client Buffer");
  while ( client.available()) {
    char out = client.read();
    message += String( out );
  }
  return message;
}

void COM::parseStringForMessage(String inputString){
  //Messages Will End With A \r\n and will be of the format
  //PRIMARY_CMD\tSECONDARY_CMD\tARGUMENT\r\n
  //PRIMARY_CMD and SECONDARY_CMD are each 3 char (for development... int later)

  //Combine The Unparsed String & inputString
  //We will check for an ending, if one exists will parse the arguments
  //If It Doesn't Exist We'll reset unParsedMsg = messageString to work at a
  //Later Iteration
  String messageString = unParsedMsg + inputString;
  int currentIndex = 0;
  int it = 0;
  while( true ){ //This is dangerous to loop all the time
    int endIndex = messageString.indexOf("\r\n",currentIndex);
    if (endIndex == -1){ //Line Feed Character Return Not Found
      unParsedMsg = messageString.substring(currentIndex);
      unParsedMsg.replace("\r","");
      unParsedMsg.replace("\n","");
      break;
    }
    else{
      //Check Primary Keys return "" (empty char if none). Format Message
      String currentMessage = messageString.substring( currentIndex, endIndex);
      currentMessage.replace("\r\n","");
      String primary_key = currentMessage.substring(0,3);
      String secondary_key = currentMessage.substring(4,7);
      String argument = currentMessage.substring(8);
      log(String(it)+" From: "+currentMessage, true);
      log(String(it)+" Got: PK||"+primary_key+"||SK||"+secondary_key+"||ARG||"+argument, true);

      //For Now We'll Handle The Command. Well want to event the sheeeet out of this later
      handleCommand(primary_key, secondary_key, argument);
      currentIndex = endIndex+1;
      it++;
    }
  }//while
}

void COM::handleCommand(String pk, String sk, String arg)
{
  if (pk.equals("PWR")){
    if (sk.equals("OFF")){ frisbeem._lights._on = false;}
    if (sk.equals("ONN")){ frisbeem._lights._on = true;}
  }
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
