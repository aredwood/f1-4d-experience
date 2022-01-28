// sources
// https://www.youtube.com/watch?v=X0LIKuzce1U
// https://www.youtube.com/watch?v=qCjCRBLv_VM

#define ENABLE 5
#define DIRA 3
#define DIRB 4

const unsigned int MSG_LENGTH = 16;

void forward()
{
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
}

void backward()
{
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
}

void off()
{
    analogWrite(ENABLE, 0);
}

void setSpeed(float kmh)
{
    float ratio = kmh / 330;
    int fanSpeed = ratio * 255;
    Serial.println(String("speed: " + String(kmh) + ", fanSpeed: " + fanSpeed));
    analogWrite(ENABLE, fanSpeed);
}

void setup()
{
    // open the serial port at 9600 bps:
    Serial.begin(9600);
    pinMode(ENABLE, OUTPUT);
    pinMode(DIRA, OUTPUT);
    pinMode(DIRB, OUTPUT);

    forward();

    setSpeed(0);
}

void loop()
{
    while (Serial.available() > 0)
    {
        // create arr
        static char msg[MSG_LENGTH];
        static unsigned int msg_pos = 0;

        char current = Serial.read();

        if (current != '\n' && (msg_pos < MSG_LENGTH - 1))
        {
            msg[msg_pos] = current;
            msg_pos++;
        }
        else
        {
            msg[msg_pos] = '\0';

            int speedValue = atoi(msg);
            setSpeed(speedValue);

            msg_pos = 0;
        }
    }
}