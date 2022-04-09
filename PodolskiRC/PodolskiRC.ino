#include <Ps3Controller.h>
#include <analogWrite.h>

int player = 0;
int battery = 0;

  #define sharpD 34 //Direito
  #define sharpF 35 //Frontal
  #define sharpE 32 //Esquerdo
  
  #define pwmB 18 //pwmB
  #define b1 26  //Bin
  #define b2 19 //Bin
  
  #define a1 5  //Ain
  #define a2 1  //Ain
  #define pwmA 23 //pwmA
  
  #define stby 3 //Standby da ponte H
    
  bool direc = true;
  

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
    //Serial.println("Connected.");
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
      digitalWrite(stby,1);

      
      //Serial.begin(115200);
  
      Ps3.attach(notify);
      Ps3.attachOnConnect(onConnect);
      Ps3.begin("34:86:5D:3A:34:38");
  
      Serial.println("Ready.");
}

void loop()
{
    digitalWrite(2, HIGH);
    if(!Ps3.isConnected())
        return;
    if(Ps3.data.analog.stick.lx <= -50){
        esquerda(180, 180);
        delay(1);
        //Serial.println("Esquerda");
    }else if(Ps3.data.analog.stick.lx > 50){
        direita(180, 180);
        Serial.println(Ps3.event.analog_changed.button.l2);
        delay(1);
       //Serial.println("direita");
    }
    if(Ps3.event.button_down.r2){
        while(true){
          frente(180, 180);
          delay(1);
          if(Ps3.event.button_up.r2){
            break;
          }
        }
    }else if(Ps3.event.button_down.l2){
        while(true){
          tras(180, 180);
          delay(1);
          if(Ps3.event.button_up.l2){
            break;
          }
        }
    }else if(Ps3.event.button_down.cross > 0){ //atacar
        while(true){
          frente(255, 255);
          delay(1);
          Serial.println("Atacar");
          if(Ps3.event.button_up.cross){
            break;
          }
        }
    }else{
      frente(0, 0);
    }
    
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
void esquerda(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
 }
void direita(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
