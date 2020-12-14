/*
    to receive command and execute it
    using: NodeMCU(ESP8266)
*/
#include <ESP8266WiFi.h>

// LED variable
const int led_pin = 4;

// relay variable
const int relay_pin = 5;

// WiFi variables
const char* ssid = "ssid";
const char* password = "password";
bool is_connected = false;

// server variable
WiFiServer server(6666);

void setup() {
    Serial.begin(115200);
    // setup
    pinMode(led_pin, OUTPUT);
    pinMode(relay_pin, OUTPUT);
}

void loop() {
    if (is_connected) { // send cmds
        WiFiClient client = server.available(); // listen for incoming clients

        if (client) { // if you get a client
            Serial.println();
            Serial.println("New Client");

            while (client.connected()) {
                if (client.available()) {
                    digitalWrite(relay_pin, !digitalRead(relay_pin));
                    client.println("HTTP/1.1 200 OK");
                    client.println(); // end of headers
                    break;
                }
            }

            client.stop(); // close the connection
            Serial.println("Client Disconnected");
        }
    }
    else connectToWiFi();
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connection lost");
        is_connected = false;
        digitalWrite(led_pin, LOW);
    }
    
    delay(500);
}

void connectToWiFi() {
    Serial.println("Disconnect to previous connection...");
    WiFi.disconnect();
    delay(500);

    Serial.println("Connecting to " + String(ssid));
    
    WiFi.mode(WIFI_STA);
    WiFi.config(IPAddress(192, 168, 1, 15),  // local IP
                IPAddress(192, 168, 1, 1),   // default gateway
                IPAddress(255, 255, 255, 0), // subnet mask
                IPAddress(192, 168, 1, 1));  // dns server
                
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(led_pin, HIGH);
        delay(200);
        digitalWrite(led_pin, LOW);
        delay(200);

        Serial.print("Connecting... with WiFi status code: ");
        Serial.println(WiFi.status());
    }

    server.begin();
    printSTAInfo();

    is_connected = true;
    digitalWrite(led_pin, HIGH);
}

void printSTAInfo() {
    Serial.println();
    Serial.println("WiFi: " + String(WiFi.SSID()) + "(" + String(WiFi.RSSI()) + ") connected with info:");

    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());

    Serial.print("Local IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Default gateway: ");
    Serial.println(WiFi.gatewayIP());

    Serial.print("Subnet mask: ");
    Serial.println(WiFi.subnetMask());

    Serial.print("DNS server: ");
    Serial.println(WiFi.dnsIP());
    Serial.println();
}