/*
Name:    temp_sensor.ino
Created: 9/30/2017 7:51:16 PM
Author:  dvyen
*/

struct measurement {
	double value;
};

class sensor {
public:
	sensor::sensor() {};
	sensor::sensor(const unsigned short int& in) {
		read_pin = in;
	};
	void sensor::measure() {
		measurement data;
		if (read_pin == A0 || read_pin == A1 || read_pin == A2
			|| read_pin == A3 || read_pin == A4 || read_pin == A5)
		{
			data.value = analogRead(read_pin);
		}
		else
		{
			data.value = digitalRead(read_pin);
		}
		most_recent_read = data;
	};
	double sensor::get() const {
		return most_recent_read.value;
	};
private:
	unsigned short int read_pin;
	measurement most_recent_read;
};

constexpr unsigned short int SENSE_PIN = A0;
sensor temperature(SENSE_PIN);

void setup() {
	Serial.begin(9600); //standard BAUD rt. 
}

void loop() {
	//map sensor voltage reading to Celcius value.
	temperature.measure();
	Serial.print("Temperature: ");
	Serial.print(temperature.get());
	Serial.print(" degree C.\n");
}

