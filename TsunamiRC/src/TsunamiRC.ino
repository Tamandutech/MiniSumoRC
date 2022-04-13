#include <Ps3Controller.h>
#include <analogWrite.h>

#define pwmB 18
#define b1 26
#define b2 19
#define stby 3
#define a1 5
#define a2 1
#define pwmA 23
#define LED 2

void onConnect()
{
    for (size_t i = 0; i < 10; i++)
    {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
    }
}

void onDisconnect()
{
    digitalWrite(LED, HIGH);
}

void tras(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void frente(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void direita(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void esquerda(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
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
    pinMode(LED, OUTPUT);
    digitalWrite(stby, 1);

    Ps3.attachOnConnect(onConnect);
    Ps3.attachOnDisconnect(onDisconnect);
    Ps3.begin("40:F5:20:80:BF:4C");
}

void loop()
{
    if (Ps3.isConnected())
    {
        if (Ps3.data.analog.stick.lx <= -50)
        {
            while (true)
            {
                esquerda(180, 180);
                delay(1);
                if (Ps3.event.button_down.r2 || Ps3.event.button_down.l2 || Ps3.event.button_down.cross || (Ps3.data.analog.stick.lx < 50 && Ps3.data.analog.stick.lx > -50))
                    break;
            }
        }
        else if (Ps3.data.analog.stick.lx > 50)
        {
            while (true)
            {
                direita(180, 180);
                delay(1);
                if (Ps3.event.button_down.r2 || Ps3.event.button_down.l2 || Ps3.event.button_down.cross || (Ps3.data.analog.stick.lx < 50 && Ps3.data.analog.stick.lx > -50))
                    break;
            }
        }
        if (Ps3.event.button_down.r2)
        {
            while (true)
            {
                frente(180, 180);
                delay(1);
                if (Ps3.event.button_up.r2)
                    break;
            }
        }
        else if (Ps3.event.button_down.l2)
        {
            while (true)
            {
                tras(180, 180);
                delay(1);
                if (Ps3.event.button_up.l2)
                    break;
            }
        }
        if (Ps3.event.button_down.cross > 0)
        { // atacar
            while (true)
            {
                frente(255, 255);
                delay(1);
                if (Ps3.event.button_up.cross)
                    break;
            }
        }
        frente(0, 0);
    }
}
