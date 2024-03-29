#include <Ps3Controller.h>
#include <analogWrite.h>

#define pwmB 32
#define b1 25
#define b2 33
#define a1 27
#define a2 26
#define pwmA 14
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

void tras(int pa, int pb)
{
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb, 255);
    analogWrite(pwmA, pa, 255);
}
void frente(int pa, int pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb, 255);
    analogWrite(pwmA, pa, 255);
}
void direita(int pa, int pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb, 255);
    analogWrite(pwmA, pa, 255);
}
void esquerda(int pa, int pb)
{
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb, 255);
    analogWrite(pwmA, pa, 255);
}

void setup()
{
    pinMode(pwmB, OUTPUT);
    pinMode(b1, OUTPUT);
    pinMode(b2, OUTPUT);
    pinMode(a1, OUTPUT);
    pinMode(a2, OUTPUT);
    pinMode(pwmA, OUTPUT);
    pinMode(LED, OUTPUT);

    Ps3.attachOnConnect(onConnect);
    Ps3.attachOnDisconnect(onDisconnect);
    Ps3.begin("c0:49:ef:e4:e0:0c");
}

void loop()
{
    if (Ps3.isConnected())
    {
        if (Ps3.data.analog.stick.lx <= -50)
        {
            while (true)
            {
                esquerda(255, 255);
                delay(1);
                if (Ps3.event.button_down.r2 || Ps3.event.button_down.l2 || Ps3.event.button_down.cross || (Ps3.data.analog.stick.lx < 50 && Ps3.data.analog.stick.lx > -50))
                    break;
            }
        }
        else if (Ps3.data.analog.stick.lx > 50)
        {
            while (true)
            {
                direita(255, 255);
                delay(1);
                if (Ps3.event.button_down.r2 || Ps3.event.button_down.l2 || Ps3.event.button_down.cross || (Ps3.data.analog.stick.lx < 50 && Ps3.data.analog.stick.lx > -50))
                    break;
            }
        }
        if (Ps3.event.button_down.r2)
        {
            while (true)
            {
                frente(255, 255);
                delay(1);
                if (Ps3.event.button_up.r2)
                    break;
            }
        }
        else if (Ps3.event.button_down.l2)
        {
            while (true)
            {
                tras(255, 255);
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
        if (Ps3.event.button_down.circle > 0)
        {
            direita(255, 255);
            delay(90);
            frente(255, 160);
            delay(500);
            esquerda(255, 255);
            delay(150);
        }
        else if (Ps3.event.button_down.square > 0)
        {
            esquerda(255, 255);
            delay(90);
            frente(160, 255);
            delay(500);
            direita(255, 255);
            delay(150);
        }
        frente(0, 0);
    }
}
