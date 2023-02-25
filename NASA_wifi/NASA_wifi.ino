/**
 * @brief This is the main file for the Mars Rover project for my L3ELEC course.
 * @details This file contains the main code for the Mars Rover project. The rover is guided by a GPS module to determine it's position. I don't think Mars has satelite coverage, so I'm not sure how this will work in production.
 *
 * @note the forward() or backward() functions must be called before utilising or calling the changeSpeed() function
 *
 * @author Oliver Parker (@parkero2)
 */
// WiFi includes
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index.h"

const char *ssid = "OliverMars";
const char *password = "roversarecool";

int leftForward = 3, leftBackward = 4, rightForward = 9, rightBackward = 10;

int lsp, rsp;
// bool current_dir; // 0 = forward, 1 = backward

// Webserver setup
AsyncWebServer server(80); // set listener port to 80

void drive(int lf = NULL, int rf = NULL)
{
    // lf annd rf stand for left forward and right forward respectively. If they are set to 0, the rover will go backwards. If they are set to 1, the rover will go forwards.
    // If no values are passed, use the current values for the speed
    if (lf == NULL && rf == NULL)
    {
        analogWrite(leftForward, lsp);
        analogWrite(rightForward, rsp);
        digitalWrite(leftBackward, LOW);
        digitalWrite(rightBackward, LOW);
    }
    if (!lf)
    {
        // Left backward
        digitalWrite(leftForward, 0);
        analogWrite(leftBackward, lsp);
    }
    else
    {
        // Left forward
        analogWrite(leftForward, lsp);
        digitalWrite(leftBackward, 0);
    }
    if (!rf)
    {
        // Right backward
        digitalWrite(rightForward, 0);
        analogWrite(rightBackward, rsp);
    }
    else
    {
        // Right forward
        analogWrite(rightForward, rsp);
        digitalWrite(rightBackward, 0);
    }
}

void changeSpeed(int l, int r)
{
    // Discard negative values
    lsp = abs(l) > 255 ? 255 : abs(l);
    rsp = abs(r) > 255 ? 255 : abs(r);
    // Check if direction is forward or backward
    // Serial.println("lsp: " + lsp.toString() + " rsp: " + rsp.toString());
    drive(l < 0 ? 0 : 1, r < 0 ? 0 : 1);
    // No need for else statement, the return statment has handled all other cases
}

void setup()
{
    /**pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);*/
    Serial.begin(115200);
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Print ESP8266 Local IP Address
    Serial.println(WiFi.localIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });
    // Handle a POST request. The request body is a JSON string with the keys lft and rgt.
    server.on(
        "/post", HTTP_POST, [](AsyncWebServerRequest *request)
        {
        // The request body is a JSON string with the keys lft and rgt.
        int lft = 0, rgt = 0;
        
        Serial.println("POST request received");
        //request->send(200, "text/plain", "OK");

        for(int i=0;i<request->params();i++){
            AsyncWebParameter* p = request->getParam(i);
            if (p->name() == "lft") {
                Serial.println("lft: " + String(p->value()));
                lft = p->value().toInt();
                changeSpeed(lft, rsp);
            }
            if (p->name() == "rgt") {
                Serial.println("rgt: " + String(p->value()));
                rgt = p->value().toInt();
                changeSpeed(lsp, rgt);
            }
        }
        request->send(200, "text/plain", "OK"); });
    server.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
}
