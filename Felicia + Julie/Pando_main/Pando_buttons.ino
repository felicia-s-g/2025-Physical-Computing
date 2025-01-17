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
