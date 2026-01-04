  /*
  * ════════════════════════════════════════════════════════════════════════════
  *    PWM Turn Signal LED Controller – 30 Modes
  * ════════════════════════════════════════════════════════════════════════════
  *
  * Copyright (c) 2026
  * ACH Milladitya Lazuwardi (apexCoderz)
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, and distribute the Software,
  * subject to the following conditions:
  *
  * 1. The above copyright notice and this permission notice shall be included in
  *    all copies or substantial portions of the Software.
  *
  * 2. The Software may NOT be sold, sublicensed, or used for commercial purposes,
  *    either in original or modified form.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  *
  * Version : 1.0 < initial release >
  * Year    : 2026
  */

  /*! ATTENTION:
  *  This firmware is specifically configured for the STM32F103 (Blue Pill) platform.
  *  The LED output is mapped to a predefined GPIO pin (LED_PIN).
  *  When porting this code to another microcontroller or board variant,
  *  update the LED_PIN definition to match the target GPIO port and pin,
  *  and ensure the selected pin supports the required output mode (PWM / GPIO).
  *
  *  NOTE:
  *  This program is provided as an example / demonstration firmware.
  *  The LED modes are designed to cycle automatically for testing and reference
  *  purposes only. It is intended to showcase PWM-based LED effects and mode
  *  transitions, not to serve as a finalized or production-ready control system.
  */


  //Predefined pin-out 
  #define LED_PIN PA1  // You can change this out pin to any pin that you want, but makesure that pin was an pwm pin !
  //#define LED_PIN 4 // example pin for ESP / ARDUIONO

  // Global variable 
  int mode = 1; 
  unsigned long lastSwitch = 0; 
  const int msPerMode = 10000; // change modes every 10 secods ( 10000 Ms ) autmatically

  void setup() {
    pinMode(LED_PIN, OUTPUT); 

  }

  void loop() {
  // Automatic LED mode cycler
    if (millis() - lastSwitch > msPerMode) {
      mode++;
      if (mode > 30) mode = 1;
      lastSwitch = millis();
      analogWrite(LED_PIN, 0); 
      pinMode(LED_PIN, OUTPUT); 
      digitalWrite(LED_PIN, LOW);
      delay(200); 
    }
    runMode(mode); // You can change this "mode" variable to the mode that you want to run without any cycle
    //runMode(7); // example : always running mode 7 without any cycle to different mode
  }

  void runMode(int m) {
    switch(m) {
      // MODE 1-5: BREATHING / FADING
      case 1: breathing(2); break;         // Fast
      case 2: breathing(4); break;         // Medium
      case 3: breathing(8); break;         // Slow
      case 4: breatheHeartbeat(); break;   // Slow heartbeat
      case 5: breatheStep(); break;        // Step Fade

      // MODE 6-10: STROBO / POLICE 
      case 6: strobe(2, 30, 80); break;   // Fast Double Tap
      case 7: strobe(3, 40, 150); break;  // Triple tap
      case 8: strobe(5, 20, 300); break;  // Burst 5 times
      case 9: policeStrobe(); break;      // police strobe
      case 10: hyperStrobe(); break;      // HyperStrobe (F1 style)

      // MODE 11-15: STANDART BLINKING 
      case 11: blink(500, 500); break;    // Standar 50% duty cycle
      case 12: blink(200, 200); break;    // Fast 
      case 13: blink(100, 400); break;    // Short On, Long Off
      case 14: blink(800, 200); break;    // Long On, Short Off
      case 15: blink(50, 50);   break;    // Hyperfast ( Jitter )

      // MODE 16-20: PULSE / HEARTBEAT (Organic)
      case 16: heartbeat(100); break; // Fast Beat
      case 17: heartbeat(200); break; // Standart Beat
      case 18: doublePulse(); break;  // Double Beat
      case 19: softBlink(); break;    // Step Blink
      case 20: sleepyLight(); break;  // SleepyLight

      // MODE 21-25: SAWTOOTH 
      case 21: sawtooth(true, 5); break;  // Fade In -> OFF (Fast)
      case 22: sawtooth(true, 15); break; // Fade In -> OFF (Slow)
      case 23: sawtooth(false, 5); break; // ON -> Fade Out (Fast)
      case 24: sawtooth(false, 15); break;// ON -> Fade Out (Slow)
      case 25: triangleWave(); break;     // Sharp Up & Down

      // MODE 26-30: SPECIAL EFFECTS / GLITCH
      case 26: glitch(); break;           // Glitch Effect
      case 27: lightning(); break;        // Lighting Effect
      case 28: morseSOS(); break;         // S-O-S Effect
      case 29: candle(); break;           // Candle Effect 
      case 30: machineGun(); break;       // Shooting Effect

      default: blink(100, 100); break;    // Default Blink
    }
  }

  // ==========================================
  // Animation Funct
  // ==========================================

  // 1. Fading Functions
  void breathing(int speed) {
    for (int i=0; i<=255; i+=5) { analogWrite(LED_PIN, i); delay(speed); }
    for (int i=255; i>=0; i-=5) { analogWrite(LED_PIN, i); delay(speed); }
    delay(100); 
  }

  void breatheHeartbeat() {
    for (int i=0; i<=255; i+=10) { analogWrite(LED_PIN, i); delay(2); }
    for (int i=255; i>=50; i-=2) { analogWrite(LED_PIN, i); delay(4); }
    for (int i=50; i>=0; i-=2) { analogWrite(LED_PIN, i); delay(8); }
    delay(300);
  }

  void breatheStep() {
    for (int i=0; i<=255; i+=50) { analogWrite(LED_PIN, i); delay(100); }
    analogWrite(LED_PIN, 0); delay(200);
  }

  // 2. Strobe Functions
  void strobe(int count, int onTime, int waitTime) {
    for(int i=0; i<count; i++) {
      digitalWrite(LED_PIN, HIGH); delay(onTime);
      digitalWrite(LED_PIN, LOW); delay(onTime);
    }
    delay(waitTime);
  }

  void policeStrobe() {
    strobe(3, 25, 50);
    delay(50);
    strobe(3, 25, 200);
  }

  void hyperStrobe() {
    digitalWrite(LED_PIN, HIGH); delay(15);
    digitalWrite(LED_PIN, LOW); delay(15);
  }

  // 3. Blinking Functions
  void blink(int onTime, int offTime) {
    digitalWrite(LED_PIN, HIGH); delay(onTime);
    digitalWrite(LED_PIN, LOW); delay(offTime);
  }

  // 4. Pulse / Heartbeat Functions
  void heartbeat(int speed) {
    analogWrite(LED_PIN, 50); delay(speed);
    analogWrite(LED_PIN, 0);   delay(speed);
    analogWrite(LED_PIN, 255); delay(speed);
    analogWrite(LED_PIN, 0);   delay(speed * 4);
  }

  void doublePulse() {
    analogWrite(LED_PIN, 20);  delay(100);
    analogWrite(LED_PIN, 255); delay(80);
    analogWrite(LED_PIN, 50);  delay(80);
    analogWrite(LED_PIN, 0);   delay(500);
  }

  void softBlink() {
    analogWrite(LED_PIN, 255); delay(300);
    analogWrite(LED_PIN, 20);  delay(300);
  }

  void sleepyLight() {
    digitalWrite(LED_PIN, HIGH); delay(50);
    digitalWrite(LED_PIN, LOW); delay(50);
    digitalWrite(LED_PIN, HIGH); delay(50);
    digitalWrite(LED_PIN, LOW); delay(800);
  }

  // 5. Sawtooth / Ramp Functions
  void sawtooth(bool fadeIn, int speed) {
    if(fadeIn) {
      for(int i=0; i<255; i+=5) { analogWrite(LED_PIN, i); delay(speed); }
      digitalWrite(LED_PIN, LOW); delay(200);
    } else {
      digitalWrite(LED_PIN, HIGH); delay(50);
      for(int i=255; i>0; i-=5) { analogWrite(LED_PIN, i); delay(speed); }
      digitalWrite(LED_PIN, LOW); delay(100);
    }
  }

  void triangleWave() {
    for(int i=0; i<255; i+=15) { analogWrite(LED_PIN, i); delay(10); }
    for(int i=255; i>0; i-=15) { analogWrite(LED_PIN, i); delay(10); }
  }

  // 6. Special Effects
  void glitch() {
    int r = random(1, 10);
    for(int i=0; i<r; i++) {
      digitalWrite(LED_PIN, HIGH); delay(random(10, 50));
      digitalWrite(LED_PIN, LOW); delay(random(10, 50));
    }
    delay(random(100, 500));
  }

  void lightning() {
    analogWrite(LED_PIN, 255); delay(20);
    analogWrite(LED_PIN, 0); delay(50);
    analogWrite(LED_PIN, 150); delay(30);
    analogWrite(LED_PIN, 0); delay(50);
    analogWrite(LED_PIN, 255); delay(20);
    analogWrite(LED_PIN, 0); delay(1000);
  }

  void morseSOS() {
    // S (...)
    strobe(3, 100, 200); 
    // O (---)
    blink(300, 200); blink(300, 200); blink(300, 200);
    // S (...)
    strobe(3, 100, 1000);
  }

  void candle() {
    analogWrite(LED_PIN, random(100, 255));
    delay(random(30, 100));
  }

  void machineGun() {
    for(int i=0; i<10; i++) {
      digitalWrite(LED_PIN, HIGH); delay(15);
      digitalWrite(LED_PIN, LOW); delay(30);
    }
    delay(500);
  }
  // ==========================================
  //             END OF PROGRAMS
  // ==========================================
  // Copyright (C) 2026 Aditya ELectronics / Aditya Project ( apexCoderz )