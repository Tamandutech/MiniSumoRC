
#include <Ps3Controller.h>
//#include <analogWrite.h>

int player = 0;
int battery = 0;

#define pwmB 4
#define b1 16
#define b2 17
#define stby 5
#define a1 19
#define a2 18
#define pwmA 23

#define led 2
#define IR 15

char SentidoE = 'F';
char SentidoD = 'F';

float VelocidadeE = 0;
float VelocidadeD = 0;

bool L2 = false;
bool R2 = false;

void notify() {
  //---------------------- Battery events ---------------------
  if (battery != Ps3.data.status.battery) {
    battery = Ps3.data.status.battery;
    Serial.print("The controller battery is ");
    if (battery == ps3_status_battery_charging) Serial.println("charging");
    else if (battery == ps3_status_battery_full) Serial.println("FULL");
    else if (battery == ps3_status_battery_high) Serial.println("HIGH");
    else if (battery == ps3_status_battery_low) Serial.println("LOW");
    else if (battery == ps3_status_battery_dying) Serial.println("DYING");
    else if (battery == ps3_status_battery_shutdown) Serial.println("SHUTDOWN");
    else Serial.println("UNDEFINED");
  }
}

void curvao(bool direc) {
  if (direc) {
    move('T', 255, 'F', 255);
    delay(50);
    move('F', 255, 'F', 100);
    delay(400);
    move('F', 255, 'T', 255);
    delay(50);
  } else {
    move('F', 255, 'T', 255);
    delay(50);
    move('F', 100, 'F', 255);
    delay(400);
    move('T', 255, 'F', 255);
    delay(50);
  }
}

void onConnect() {
  //Serial.println("Connected.");
}

void setup() {

  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  digitalWrite(stby, 1);

  //Serial.begin(115200);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("08:B6:1F:34:DC:C0");

  Serial.println("Ready.");
}

void move(char SE, int VE, char SD, int VD) {
  /*
		variaveis com final D sao do motor direito e com final E sao do esquerdo
		S = qual sentido de rotação
		'F' -> frente || 'T' -> tras
		V = velocidade de rotação 0 ~ 255
	*/

  if (SD == 'F') {
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmA, VD);
  } else {
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmA, VD);
  }

  if (SE == 'F') {
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    analogWrite(pwmB, VE);
  } else {
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    analogWrite(pwmB, VE);
  }
}

void loop() {
  digitalWrite(2, HIGH);
  if (!Ps3.isConnected()) {
    digitalWrite(2, LOW);
    move('F', 0, 'F', 0);
    return;
  }

  VelocidadeE = 180;
  VelocidadeD = 180;
  SentidoE = 'F';
  SentidoD = 'F';



  if (Ps3.event.button_down.cross > 0) {  //atacar
    while (true) {
      move('F', 255, 'F', 255);
      if (Ps3.event.button_up.cross) {
        break;
      }
    }
  } else {
    if (Ps3.event.button_down.square > 0) {
      curvao(true);
    }
    if (Ps3.event.button_down.circle > 0) {
      curvao(false);
    }
    if (abs(Ps3.event.button_down.r2) > 0) {
      R2 = true;
    }

    if (abs(Ps3.event.button_up.r2) > 0) {
      R2 = false;
    }

    if (abs(Ps3.event.button_down.l2) > 0) {
      L2 = true;
    }

    if (abs(Ps3.event.button_up.l2) > 0) {
      L2 = false;
    }


    if (R2) {
      if (Ps3.data.analog.stick.lx <= -50) {
        VelocidadeE *= 0.5;
        VelocidadeD *= 2;
      } else if (Ps3.data.analog.stick.lx > 50) {
        VelocidadeE *= 2;
        VelocidadeD *= 0.5;
      }

    } else if (L2) {

      SentidoE = 'T';
      SentidoD = 'T';

      if (Ps3.data.analog.stick.lx <= -50) {
        VelocidadeE *= 0.5;
        VelocidadeD *= 2;
      } else if (Ps3.data.analog.stick.lx > 50) {
        VelocidadeE *= 2;
        VelocidadeD *= 0.5;
      }

    } else if (Ps3.data.analog.stick.lx <= -50) {

      SentidoE = 'T';
      SentidoD = 'F';

    } else if (Ps3.data.analog.stick.lx > 50) {

      SentidoE = 'F';
      SentidoD = 'T';

    } else {
      VelocidadeE = 0;
      VelocidadeD = 0;
    }

    move(SentidoE, VelocidadeE, SentidoD, VelocidadeD);
  }
}