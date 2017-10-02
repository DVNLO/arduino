/*
Name:    temp_sensor.ino
Created: 9/30/2017 7:51:16 PM
Author:  dvyen
*/

struct Measurement {
	float most_recent_value;
};

class Sensor {
public:
	Sensor::Sensor() { pin_set = false; };
	Sensor::Sensor(const unsigned short int& in_pin) {
		pin = in_pin;
		pin_set = true;
	}
	void Sensor::set(const unsigned short int& in_pin) {
		pin = in_pin;
		pin_set = true;
	}
	boolean is_pin_set() {
		return pin_set;
	}
	unsigned short int Sensor::get_pin() const {
		if (pin_set)
			return pin;
	}
	virtual void Sensor::read() = 0;
private:
	boolean pin_set;
	unsigned short int pin;
};

class Analog : public Sensor {
public:	
	Analog::Analog() : Sensor() {}
	Analog::Analog(const unsigned short int& in_pin, const String& in_id) : Sensor(in_pin) {
		id = in_id;
	}
	void Analog::set(const unsigned short int& in_pin, const String& in_id){
		Sensor::set(in_pin);
		id = in_id;
	}
	void Analog::read() {
		if (Sensor::is_pin_set())
			data.most_recent_value = analogRead(get_pin());
	}
	float Analog::get_most_recent_value() const {
		return data.most_recent_value;
	}
private:
	String id;	//circuit component id
	Measurement data;
};

class Digital : public Sensor {
public:
	Digital::Digital() : Sensor() {}
	Digital::Digital(const unsigned short int& in_pin, const String& in_id) : Sensor(in_pin) {
		id = in_id;
	}
	void Digital::set(const unsigned short int& in_pin, const String& in_pin_mode_type, const String& in_id) {
		Sensor::set(in_pin);
		pin_mode_type = in_pin_mode_type;
		id = in_id;
	}
	void Digital::set_pin_mode_type(const String& in_pin_mode_type) {
		pin_mode_type = in_pin_mode_type;
	}
	String Digital::get_pin_mode_type() const {
		return pin_mode_type;
	}
	void Digital::set_pin_mode(const String& in_pin_mode_type) {
		if (Sensor::is_pin_set())
		{
			if (in_pin_mode_type == "INPUT")	//sensors only take input
				pinMode(get_pin(), INPUT);
		}
	}
	void Digital::read() {
		if (Sensor::is_pin_set())
			data.most_recent_value = digitalRead(get_pin());
	}
	float Digital::get_most_recent_value() const {
		return data.most_recent_value;
	}
private:
	String id;	//circuit component id
	String pin_mode_type;
	Measurement data;
};

constexpr unsigned short int SENSE_PIN = A0;	//put this in an ini file later.
Analog temperature(SENSE_PIN, "TMP 36GZ");

void setup() {
	Serial.begin(9600); //standard BAUD rt. 
}

void loop() {
	//map sensor voltage reading to Celcius value.
	Serial.print(temperature.is_pin_set());
	temperature.read();
	Serial.print("Temperature: ");
	Serial.print(temperature.get_most_recent_value());
	Serial.print(" degree C.\n");
}

