#include <ESP8266WiFi.h> 

const char* ssid = "Fadaei-MTN"; 
const char* password = "zahra1373"; 

int ledPin = D4; 

int OnTime;
int OffTime;
int value = 404;


WiFiServer server(8880); 

void setup() { 
  Serial.begin(9600); 
  delay(10); 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
  
  // Connect to WiFi network 
  Serial.println(); 
  Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000); 
    Serial.print("."); 
    digitalWrite(ledPin, !digitalRead(ledPin)); 
    } 
    
    Serial.println(""); 
    Serial.println("WiFi connected"); 
    
    // Start the server 
    server.begin(); 
    Serial.println("Server started"); 
    
    // Print the IP address 
    Serial.print("Use this URL : "); 
    Serial.print("http://"); 
    Serial.print(WiFi.localIP()); 
    Serial.println("/"); 
    
} 


void check_url (){
  
  // Check if a client has connected 
    WiFiClient client = server.available(); 
    if (!client) { 
      return;
    } 
    
  // Wait until the client sends some data 
    Serial.println("new client"); 
    while(!client.available()){
      delay(1);
    } 
      
  // Read the first line of the request 
    String request = client.readStringUntil('\r');
    Serial.println(request); 
    client.flush(); 
    delay(100);
  
  // parse the url  
    if (request.indexOf("OnTime=") != -1) { 
      int data1, data2;
      String timeon;
      data1 = request.indexOf("=");
      data2 = request.indexOf("&");
      timeon = request.substring(data1+1, data2);
      digitalWrite(ledPin, LOW); 
      OnTime = timeon.toInt();
      Serial.print("OnTime = ");
      Serial.println(OnTime);
    }
    
    if (request.indexOf("OffTime") != -1){
      int data3;
      String timeoff;    
      data3 = request.lastIndexOf("=");
      timeoff = request.substring(data3+1);
      digitalWrite(ledPin, HIGH);
      OffTime = timeoff.toInt();
      Serial.print("OffTime = ");
      Serial.println(OffTime); 
    } 
    
    if (request.indexOf("/LED-OFF") != -1){
      digitalWrite(ledPin, LOW);
      value = LOW;
      OnTime=0;
      OffTime=0;
    }
    
    if (request.indexOf("/LED-ON") != -1) {
      digitalWrite(ledPin, HIGH);
      value = HIGH;
      
      if (request.indexOf("OnTime=") == -1) { 
        OnTime = 0;
      }
      
      if (request.indexOf("OffTime") == -1){
        OffTime = 0; 
      }
    }
    
    delay (100);
  
  // Return the response 
    client.println("HTTP/1.1 200 OK"); 
    client.println("Content-Type: text/html"); 
    client.println(""); 
       
  // Send Html to clinet 
    client.println ("<!DOCTYPE html>");
    client.println ("<html lang='en'></html>");
    client.println ("<head></head>");
    client.println ("<meta charset='UTF-8'>");    
    client.println ("<meta http-equiv='X-UA-Compatible' content='IE=edge'>");    
    client.println ("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");    
    client.println ("<title>Final Project</title>");    
    client.println ("</head>");
    client.println ("<style>");
    client.println ("input[type=text], select {");    
    client.println ("width: 100%;");      
    client.println ("padding: 12px 20px;");  
    client.println ("margin: 8px 0;");     
    client.println ("display: inline-block;");     
    client.println ("border: 1px solid #ccc;");     
    client.println ("border-radius: 4px;");     
    client.println ("box-sizing: border-box;");     
    client.println ("}");  
    client.println ("input[type=submit] {");   
    client.println ("width: 100%;");   
    client.println ("background-color: #FF9999;");   
    client.println ("color: white;");    
    client.println ("padding: 14px 20px;");    
    client.println ("margin: 8px 0;");    
    client.println ("border: none;");    
    client.println ("border-radius: 4px;");    
    client.println ("cursor: pointer;");   
    client.println ("}"); 
    client.println ("input[type=submit]:hover {");   
    client.println ("background-color: #FF6666;");  
    client.println ("}");   
    client.println ("div {"); 
    client.println ("border-radius: 5px;");   
    client.println ("background-color: #404040;");   
    client.println ("padding: 20px;");    
    client.println ("}");  
    client.println (".button {");  
    client.println ("background-color: #FF9999;");     
    client.println ("border: none;");
    client.println ("color: white;");     
    client.println ("padding: 15px 32px;");     
    client.println ("text-align: center;");   
    client.println ("text-decoration: none;");     
    client.println ("display: inline-block;");     
    client.println ("font-size: 16px;");      
    client.println ("margin: 4px 2px;");      
    client.println ("cursor: pointer;");       
    client.println ("}");   
    client.println (".button:hover {"); 
    client.println ("background-color: #FF6666;");     
    client.println ("}");   
    client.println (".link {");  
    client.println ("display: flex;");     
    client.println ("justify-content: center;");     
    client.println ("}");
    client.println ("label{");
    client.println ("color: white;");
    client.println ("}");  
    client.println ("</style>");
    client.println ("<body>");
    client.println ("<div>");   
    client.println ("<form action='' method='GET'>");        
    client.println ("<label for='ontime'>On Time</label>");          
    client.println ("<input type='text' id='on' name='OnTime' required>");
    client.println ("<label for='offtime'>Off Time</label>");      
    client.println ("<input type='text' id='off' name='OffTime'required >");
    client.println ("<input type='submit' value='Submit'>");
    client.println ("</form>");
    client.println ("</div>");
    client.println ("<div class='link'>");
    client.println ("<a href='/LED-OFF\' class='button'>Turn OFF</a>");
    client.println ("<a href= '/LED-ON\' class='button'>Turn ON</a>");
    client.println ("<a href='/'class='button'>Clear URL</a>"); 
    client.println ("</div>");
    client.println ("</body>");
    client.println ("</html>");
    
    delay(100); 
       
    Serial.println("Client disconnected");
    Serial.println("");
  }


void loop() {

  check_url();
  
  while(1){
    
    if (value == LOW){
      digitalWrite(ledPin, HIGH);
    }
    
    if(value == HIGH & (OnTime + OffTime == 0)){
      digitalWrite(ledPin, LOW);
    }
    
    if(value == HIGH & (OnTime + OffTime > 0)){
      digitalWrite(ledPin, LOW);
      delay(OnTime);
      digitalWrite(ledPin, HIGH);
      delay(OffTime);
    }
    
    if (OnTime + OffTime > 0 ){
      digitalWrite(ledPin, LOW);
      delay(OnTime);
      digitalWrite(ledPin, HIGH);
      delay(OffTime);
    }
    
    check_url();
  }
}
