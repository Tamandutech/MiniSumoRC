#include <Ps3Controller.h>
#include <analogWrite.h>

int player = 0;
int battery = 0;

  #define sharpFE 36
  #define sharpFD 39
  #define sharpD 35

  #define pwmB 25
  #define b1 33
  #define b2 26
  #define stby 27
  #define a1 14
  #define a2 12
  #define pwmA 13
  //sensor de linha
  #define linhaD 15
  #define linhaE 4
  
  bool direc = true;
  

void notify()
{
  
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
    
      pinMode(pwmB, OUTPUT);
      pinMode(b1, OUTPUT);
      pinMode(b2, OUTPUT);
      pinMode(stby, OUTPUT);
      pinMode(a1, OUTPUT);
      pinMode(a2, OUTPUT);
      pinMode(pwmA, OUTPUT);
      pinMode(linhaE, INPUT);
      pinMode(linhaD, INPUT);
      pinMode(sharpD, INPUT);
      pinMode(sharpFE, INPUT);
      pinMode(sharpFD, INPUT);
      digitalWrite(stby,1);
      
      Serial.begin(115200);
  
      Ps3.attach(notify);
      Ps3.attachOnConnect(onConnect);
      Ps3.begin("8C:AA:B5:8C:B5:F8");
  
      Serial.println("Ready.");
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    if(Ps3.data.analog.stick.lx <= -50){
        esquerda(120, 120);
        delay(10);
        Serial.println("Esquerda");
    }else if(Ps3.data.analog.stick.lx > 50){
        direita(120, 120);
        Serial.println(Ps3.event.analog_changed.button.l2);
        delay(10);
        Serial.println("direita");
    }else if(Ps3.event.button_down.cross > 0){ //atacar
        while(true){
          frente(255, 255);
          delay(10);
          Serial.println("Atacar");
          if(Ps3.event.button_up.cross){
            break;
          }
        }
    }else if(Ps3.event.button_down.r2){
        while(true){
          frente(120, 120);
          delay(10);
          if(Ps3.event.button_up.r2){
            break;
          }
        }
    }else if(Ps3.event.button_down.l2){
        while(true){
          tras(120, 120);
          delay(10);
          if(Ps3.event.button_up.l2){
            break;
          }
        }
    }
     frente(0, 0);
    
}


void frente(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void tras(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void direita(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
 }
void esquerda(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }
