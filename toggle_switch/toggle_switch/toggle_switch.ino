/*
 Name:		toggle_switch.ino
 Created:	9/27/2017 5:32:45 PM
 Author:	dvyen
*/

static unsigned short int TOGGLE_PIN = 2;
static unsigned short int RED_LED = 3;
static unsigned short int YELLOW_LED = 4;

class toggle_switch {
public:
	toggle_switch::toggle_switch() {
		bit = false;
	}
	void toggle_switch::set(const boolean& in) {
		bit = in;
	}
	boolean toggle_switch::get() {
		return bit;
	}
private:
	boolean bit;
};

void setup() {
	pinMode(TOGGLE_PIN, INPUT);
	pinMode(RED_LED, OUTPUT);
	pinMode(YELLOW_LED, OUTPUT);
	Serial.begin(9600);
}

toggle_switch pushbutton;

void loop() {
	if (digitalRead(TOGGLE_PIN) == HIGH)
	{
		if (pushbutton.get())
			pushbutton.set(false); //set off
		else
			pushbutton.set(true);	//set on
		flash(RED_LED);
	}

	delay(100);

	if (pushbutton.get())
		digitalWrite(YELLOW_LED, HIGH);
	else
		digitalWrite(YELLOW_LED, LOW);
}

void flash(unsigned short int& pin) {
	digitalWrite(pin, HIGH);
	delay(50);
	digitalWrite(pin, LOW);
}