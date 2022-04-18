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

char SentidoE = 'F';
char SentidoD = 'F';

float VelocidadeE = 0;
float VelocidadeD = 0;

void notify() {
	//---------------------- Battery events ---------------------
	if( battery != Ps3.data.status.battery ){
		battery = Ps3.data.status.battery;
		Serial.print("The controller battery is ");
		if( battery == ps3_status_battery_charging)			Serial.println("charging");
		else if( battery == ps3_status_battery_full)		Serial.println("FULL");
		else if( battery == ps3_status_battery_high)		Serial.println("HIGH");
		else if( battery == ps3_status_battery_low)			Serial.println("LOW");
		else if( battery == ps3_status_battery_dying)		Serial.println("DYING");
		else if( battery == ps3_status_battery_shutdown)	Serial.println("SHUTDOWN");
		else Serial.println("UNDEFINED");
	}
}

void onConnect(){
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
	digitalWrite(stby,1);

	//Serial.begin(115200);

	Ps3.attach(notify);
	Ps3.attachOnConnect(onConnect);
	Ps3.begin("34:86:5D:3A:34:38");

	Serial.println("Ready.");
}

void move(char SE, int VE, char SD, int VD) {
	/*
		variaveis com final D sao do motor direito e com final E sao do esquerdo
		S = qual sentido de rotação
		'F' -> frente || 'T' -> tras
		V = velocidade de rotação 0 ~ 255
	*/

	if (SD == 'F')
	{
		digitalWrite(a1, 1);
		digitalWrite(a2, 0);
		analogWrite(pwmA, VD);
	}
	else
	{
		digitalWrite(a1, 0);
		digitalWrite(a2, 1);
		analogWrite(pwmA, VD);
	}

	if (SE == 'F')
	{
		digitalWrite(b1, 1);
		digitalWrite(b2, 0);
		analogWrite(pwmB, VE);
	}
	else
	{
		digitalWrite(b1, 0);
		digitalWrite(b2, 1);
		analogWrite(pwmB, VE);
	}
}

void loop() {
	digitalWrite(2, HIGH);
	if(!Ps3.isConnected()){
		digitalWrite(2, LOW);
		move('F', 0, 'F', 0);
		return;
	}

	VelocidadeE = 180;
	VelocidadeD = 180;
	SentidoE = 'F';
	SentidoD = 'F';
	


	if(Ps3.event.button_down.cross > 0){ //atacar
		while(true){
			move('F', 255, 'F', 255);
			if(Ps3.event.button_up.cross){
			break;
			}
		}
	}else{

		if(Ps3.event.button_down.r2){

			SentidoE = 'F';
			SentidoD = 'F';

			if(Ps3.data.analog.stick.lx <= -50){
				VelocidadeE*= 0.5;
				VelocidadeD*= 2;
			}else if(Ps3.data.analog.stick.lx > 50){
				VelocidadeE*= 2;
				VelocidadeD*= 0.5;
			}

		}else if(Ps3.event.button_down.l2){

			SentidoE = 'T';
			SentidoD = 'T';

			if(Ps3.data.analog.stick.lx <= -50){
				VelocidadeE*= 0.5;
				VelocidadeD*= 2;
			}else if(Ps3.data.analog.stick.lx > 50){
				VelocidadeE*= 2;
				VelocidadeD*= 0.5;
			}

		}else if(Ps3.data.analog.stick.lx <= -50){

			SentidoE = 'T';
			SentidoD = 'F';

		}else if(Ps3.data.analog.stick.lx > 50){

			SentidoE = 'F';
			SentidoD = 'T';

		}else{
			VelocidadeE = 0;
			VelocidadeD = 0;
		}

		move(SentidoE, VelocidadeE, SentidoD, VelocidadeD);
	}
}
