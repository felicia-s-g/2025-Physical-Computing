bool btn_val = false;
bool old_btn_val = false;
int btn_pin = 11;
int btn_status = 0;  // 0: OFF, 1: RISING EDGE, 2: ON; 3: FALLING EDGE
int old_btn_status = -1;

int count = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	btn_val = digitalRead(btn_pin);
	
	if(!btn_val && !old_btn_val) {
		btn_status = 0;  // OFF
	}
	else if(btn_val && !old_btn_val) {
		btn_status = 1;  // RISING EDGE
    old_btn_val = 1;
	}
	else if(btn_val && old_btn_val) {
		btn_status = 2;  // ON
	}
	else if(!btn_val && old_btn_val) {
		btn_status = 3;  // FALLING EDGE
    old_btn_val = 0;
	}
	
	if(btn_status != old_btn_status) {
		switch(btn_status) {
			case 0:
				Serial.println("OFF");
				break;
			case 1:
				Serial.println("RISING EDGE");
				break;
			case 2:
				Serial.println("ON");
				break;
			case 3:
				Serial.println("FALLING EDGE");
				break;
		}
		old_btn_status = btn_status;
	}
}