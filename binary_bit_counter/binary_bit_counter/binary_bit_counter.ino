/*
*This progarm iterates through a 4 "bit" array of 
*LED's. Each configuration of the four bits is explored
*incrementally from 0000-1111. The possible combinations
*correspond to HEX values. 
*Author: Dan Vyenielo
*9/27/2017
*/

static const short unsigned int PIN_BYTE0 = 10, PIN_BYTE1 = 11,
PIN_BYTE2 = 12, PIN_BYTE3 = 13;
static const short unsigned int HEX_SYMBOL_COUNT = 16;
static const short unsigned int BINARY_RADIX = 2;

void setup() {
	pinMode(PIN_BYTE0, OUTPUT);
	pinMode(PIN_BYTE1, OUTPUT);
	pinMode(PIN_BYTE2, OUTPUT);
	pinMode(PIN_BYTE3, OUTPUT);
	Serial.begin(9600); //setup serial
}


void loop() {
	short unsigned int sum = 0;
	for (short unsigned int c3 = 0; c3 < BINARY_RADIX; c3++) {
		for (short unsigned int c2 = 0; c2 < BINARY_RADIX; c2++) {
			for (short unsigned int c1 = 0; c1 < BINARY_RADIX; c1++) {
				for (short unsigned int c0 = 0; c0 < BINARY_RADIX; c0++) {
					sum = 8 * c3 + 4 * c2 + 2 * c1 + c0;
					switch_bits(c3, c2, c1, c0);
					print_sum_hex_bits(sum, c3, c2, c1, c0);
					delay(1000);
				}
			}
		}
	}
}

void switch_bits(const bool& c3, const bool& c2, const bool& c1,
	const bool& c0) {
	if (c3)
		digitalWrite(PIN_BYTE3, HIGH);
	else
		digitalWrite(PIN_BYTE3, LOW);
	if (c2)
		digitalWrite(PIN_BYTE2, HIGH);
	else
		digitalWrite(PIN_BYTE2, LOW);
	if (c1)
		digitalWrite(PIN_BYTE1, HIGH);
	else
		digitalWrite(PIN_BYTE1, LOW);
	if (c0)
		digitalWrite(PIN_BYTE0, HIGH);
	else
		digitalWrite(PIN_BYTE0, LOW);
}

void print_sum_hex_bits(const short unsigned int& sum, const short unsigned int& c3,
	const short unsigned int& c2, const short unsigned int& c1, const short unsigned int& c0) {
	Serial.print(sum);
	Serial.print(" | ");
	Serial.print(sum, HEX);
	Serial.print(" | ");
	Serial.print(c3);
	Serial.print(c2);
	Serial.print(c1);
	Serial.println(c0);
}
