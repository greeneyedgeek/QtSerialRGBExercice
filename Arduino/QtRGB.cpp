#include <Arduino.h>

const uint8_t red { 9 };
const uint8_t green { 10 };
const uint8_t blue { 11 };

void setup()
{
	pinMode(red, 0x1);
	pinMode(green, 0x1);
	pinMode(blue, 0x1);
	analogWrite(red, 0);
	analogWrite(green, 0);
	analogWrite(blue, 0);
	Serial.begin(9600);
}

void writeLED(char colour, int brightness)
{
	switch (colour)
	{
	case 'r':
		analogWrite(red, brightness);
		break;
	case 'g':
		analogWrite(green, brightness);
		break;

	case 'b':
		analogWrite(blue, brightness);
		break;
	}
	return;
}

void loop()
{
	if (Serial.available())
	{
		char colour = Serial.read();
		int brightness = Serial.parseInt();
		writeLED(colour, brightness);

	}
}
