#include <Servo.h>

// Create servo objects
Servo head;
Servo l_hand;
Servo r_hand;

// Define sonar sensor's pins
const int trig = 4;
const int echo = 5;

// Received data
byte val = "";

void setup() {
  // Attach servo motors to their respective pins
  head.attach(2);
  l_hand.attach(3);
  r_hand.attach(4);

  // Begin serial communication
  Serial.begin(9600); 
}

void standby() {
  // Set motors to standby positions
  head.write(90);
  int r_pos = 30;
  int l_pos = map(r_pos, 0, 180, 180, 0);
  
  l_hand.write(l_pos);
  r_hand.write(r_pos);
}

void hi() {
  // Perform a waving motion
  head.write(90);

  for (int i = 30; i <= 170; i++) {
    r_hand.write(i);
    delay(5);
  }

  for (int i = 170; i >= 30; i--) {
    r_hand.write(i);
    delay(5);
  }

  standby();
}

void hands_up() {
  // Move both hands up and down
  for (int i = 30; i <= 170; i++) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }

  delay(600);

  for (int i = 170; i >= 30; i--) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }
}

void weight_lift() {
  // Simulate weight lifting motion
  for (int i = 30; i <= 170; i++) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }

  for (int count = 0; count <= 4; count++) {
    for (int i = 170; i >= 60; i--) {
      int r_pos = i;
      int l_pos = map(r_pos, 0, 180, 180, 0);
      l_hand.write(l_pos);
      r_hand.write(r_pos);
      delay(5);
    }

    for (int i = 60; i <= 170; i++) {
      int r_pos = i;
      int l_pos = map(r_pos, 0, 180, 180, 0);
      l_hand.write(l_pos);
      r_hand.write(r_pos);
      delay(5);
    }
  }

  for (int i = 170; i >= 30; i--) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }
}

void look_left() {
  // Rotate head to left
  head.write(180);
}

void confused() {
  // Perform a confused motion
  for (int count = 0; count <= 1; count++) {
    head.write(30);
    r_hand.write(170);
    delay(700);
    r_hand.write(30);
    head.write(120);
    l_hand.write(30);
    delay(700);
    l_hand.write(160);
  }
  standby();
}

void double_punch() {
  // Perform a double punch
  for (int i = 30; i >= 0; i--) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }
  delay(2000);
  int r_pos = 80;
  int l_pos = map(r_pos, 0, 180, 180, 0);
  l_hand.write(l_pos);
  r_hand.write(r_pos);
  delay(500);
  standby();
}

void r_upper_cut() {
  // Perform a right upper cut
  for (int i = 30; i <= 170; i++) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }

  for (int count = 0; count <= 4; count++) {
    for (int i = 170; i >= 60; i--) {
      r_hand.write(i);
      delay(1);
    }

    for (int i = 60; i <= 170; i++) {
      r_hand.write(i);
      delay(1);
    }
  }
  standby();
}

void smash() {
  // Perform a smashing motion
  for (int i = 30; i <= 170; i++) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(5);
  }
  delay(2000);
  for (int i = 170; i >= 0; i--) {
    int r_pos = i;
    int l_pos = map(r_pos, 0, 180, 180, 0);
    l_hand.write(l_pos);
    r_hand.write(r_pos);
    delay(1);
  }
  delay(300);
  int r_pos = 180;
  int l_pos = map(r_pos, 0, 180, 180, 0);
  l_hand.write(l_pos);
  r_hand.write(r_pos);
  delay(1000);
  standby();
}

void loop() {
  // Main loop to read serial input and perform actions
  standby();

  while (Serial.available() > 0) {  // Check for serial data
    val = Serial.read();  // Read the serial value

    // Perform actions based on received serial commands
    if (val == 'h') {
      hi();
    } else if (val == 'p') {
      double_punch();
    } else if (val == 'u') {
      hands_up();
      delay(3000);
    } else if (val == 'l') {
      standby();
      look_left();
      delay(2000);
    } else if (val == 'U') {
      r_upper_cut();
      delay(2000);
    } else if (val == 's') {
      smash();
      delay(2000);
    }
  }
}
