// bool readButton(int pin, bool &btn_val, bool &old_btn_val, int &btn_status) {
//   btn_val = digitalRead(pin);  // Read the button state
  
//   // Debounce logic: Only register a change if it's different from the previous state
//   if (btn_val != old_btn_val) {
//     delay(10);  // Short debounce delay to avoid bouncing issues
//     old_btn_val = btn_val;
    
//     // Handle the state changes
//     if (btn_val == HIGH) {  // Button pressed
//       if (btn_status == 0) {  // If it's the first time pressed
//         btn_status = 1;  // Rising edge detected
//       } else if (btn_status == 1) {  // If it's still pressed
//         btn_status = 2;  // On state
//       }
//     } else {  // Button released
//       if (btn_status == 2) {
//         btn_status = 3;  // Falling edge detected
//       } else if (btn_status == 3) {
//         btn_status = 0;  // Reset to off state
//       }
//     }
//   }
//   return btn_val;
// }




bool readButton(int btn_pin, bool &btn_val, bool &old_btn_val, int &btn_status, int &old_btn_status) {
  btn_val = digitalRead(btn_pin);

  if (!btn_val && !old_btn_val) {
    btn_status = 0;  // OFF
  } else if (btn_val && !old_btn_val) {
    btn_status = 1;  // RISING EDGE
    old_btn_val = 1;
  } else if (btn_val && old_btn_val) {
    btn_status = 2;  // ON
  } else if (!btn_val && old_btn_val) {
    btn_status = 3;  // FALLING EDGE
    old_btn_val = 0;
  }

  if (btn_status != old_btn_status) {

    old_btn_status = btn_status;

    switch (btn_status) {
      case 0:
        return false;
      case 1:
        return true;
      case 2:
        return true;
      case 3:
        return false;
    }
  }
}
