#include <Ps3Controller.h>

int player = 0;
int battery = 0;


#include <BluetoothSerial.h>
#include <analogWrite.h>
#include <Arduino.h>
#include <IRremote.hpp>
#include <ESP32Servo.h>
#include "ESC.h" 



#define motor1 (25)
#define motor2 (13)
#define LED_BUILTIN (2)
#define MIN_SPEED 1040 
#define MAX_SPEED 1240
#define led 2


ESC motorD (motor1, 1000, 2000, 500);
ESC motorE (motor2, 1000, 2000, 500);

long int val;


void frente(){
  motorD.speed(2000);
  motorE.speed(1000);
  
}
void tras(){
  motorD.speed(1000);
  motorE.speed(2000);
 }
void esquerda(){
  motorD.speed(1560);
  motorE.stop();
} 
void direita(){
  motorD.stop();
  motorE.speed(1000);
}
void parar(){
  motorD.stop();
  motorE.stop();
}


void notify()
{
    
   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    motorD.arm();
    motorE.arm();
    delay(5000); //necessidade do delay para ligar o esc
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("94:B9:7E:D0:7D:40 ");

    Serial.println("Ready.");
}

void loop()
{
   if(!Ps3.isConnected())
        return;
    if(Ps3.data.analog.stick.lx <= -50){
        esquerda();
        delay(10);
        Serial.println("Esquerda");
    }else if(Ps3.data.analog.stick.lx > 50){
        direita();
        Serial.println(Ps3.event.analog_changed.button.l2);
        delay(10);
        Serial.println("direita");
    }else if(Ps3.event.button_down.cross > 0){ //atacar
        while(true){
          frente();
          delay(10);
          Serial.println("Atacar");
          if(Ps3.event.button_up.cross){
            break;
          }
        }
    }else if(Ps3.event.button_down.r2){
        while(true){
          frente();
          delay(10);
          if(Ps3.event.button_up.r2){
            break;
          }
        }
    }else if(Ps3.event.button_down.l2){
        while(true){
          tras();
          delay(10);
          if(Ps3.event.button_up.l2){
            break;
          }
        }
    }
 
     parar();    
}
