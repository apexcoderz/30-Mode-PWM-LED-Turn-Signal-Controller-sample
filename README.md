# 30-Mode PWM LED Signal Controller 🚦

![Platform](https://img.shields.io/badge/platform-STM32%20%7C%20Arduino-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-Demo-yellow)

A compact, production-minded firmware for the **STM32F103 (Blue Pill)** that drives LED turn signals and hazard lights with **30 polished animation patterns** using hardware PWM and robust timing logic.

> ⚠️ **Safety note:** This project is intended for educational and demonstration use. Do **not** use experimental lighting on public roads unless it complies with local regulations and vehicle standards.

---

## Table of Contents
- [Features](#-features)
- [Modes](#-modes)
- [Hardware Requirements](#-hardware-requirements)
- [Wiring & Pinout](#-wiring--pinout)
- [Build & Flash](#-build--flash)
- [Configuration](#-configuration)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features

- **30 Unique Modes:** A wide variety of patterns ranging from elegant fading to aggressive strobing.
- **Hybrid Control Logic:** Seamlessly switches between PWM (Fading) and Digital GPIO (Strobing) modes without signal locking.
- **Auto-Cycle System:** Automatically switches to the next pattern every 8 seconds (configurable).
- **Optimized for STM32:** Designed for 32-bit architecture but compatible with Arduino AVR with minor pin adjustments.

---

## 🎛️ Mode List

The controller cycles through 6 distinct categories of animations:

| ID | Category | Description |
| :--- | :--- | :--- |
| **01-05** | **Breathing** | Smooth fading in/out, heartbeat, and stepped dimming. |
| **06-10** | **Strobe (Jetbus)** | Aggressive "police-style" strobes, bursts, and rapid flashing. |
| **11-15** | **Blinking** | Standard turn signal emulation (Normal, Fast, Long-On, Hyper). |
| **16-20** | **Pulse** | Organic pulsing effects, double-beat, and "sleepy" rhythms. |
| **21-25** | **Sawtooth** | Sharp fade-in/cutoff or cutoff/fade-out (modern Audi/BMW style). |
| **26-30** | **Special FX** | Glitch, Lightning simulation, Morse Code (SOS), Candle flicker. |

---

## 🛠️ Hardware Requirements

1.  **Microcontroller:** STM32F103C8T6 (Blue Pill) recommended.
    *   *Compatible with Arduino Uno/Nano (requires changing `LED_PIN` to a PWM pin like 3, 5, 6, 9).*
2.  **Output Driver:**
    *   For small LEDs: 220Ω Resistor.
    *   **For Automotive LEDs (12V/24V):** You **MUST** use a **MOSFET Module (e.g., IRF520)** or a Transistor to drive the load. The STM32 pin cannot drive 12V bulbs directly.
3.  **Power Supply:** 5V (via USB) or 12V source (stepped down for the MCU).

### 🔌 Pin Configuration

Change the pin definition in `main.ino` to match your setup:

```cpp
// Ensure this pin supports PWM (Timer Output)
#define LED_PIN PA1
#define AUTO_CYCLE_INTERVAL_MS 8000 // 8 seconds
```

---

## 🔌 Wiring & Pinout

- Connect MCU ground to load ground and to the MOSFET module ground.
- MOSFET gate -> MCU PWM pin (via 100Ω resistor optional).
- MOSFET source -> Ground; MOSFET drain -> LED negative; LED positive -> 12V (through resistor if needed).

> ⚠️ For automotive installs, isolate power and ensure the MCU is protected from voltage spikes (use TVS diodes, transient suppression, and proper fusing).

---

## ⚙️ Build & Flash

- **Arduino IDE:** Install the STM32 board package (STM32duino), select your board and upload normally.
- **PlatformIO:** Use a `platformio.ini` with an appropriate board (e.g., `bluepill_f103c8`).

Quick PlatformIO example:

```ini
[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = arduino
```

---

## 🔧 Configuration

- Change `LED_PIN` and `AUTO_CYCLE_INTERVAL_MS` in `main.ino` to suit your hardware and preferences.
- Mode timing and behavior are defined in the source — tweak constants responsibly and test on a bench before vehicle installation.

---

## 🤝 Contributing

Contributions welcome: open an issue to propose features or improvements and submit pull requests with clear change descriptions and, where applicable, hardware test notes.

---

## 📄 License

This project is licensed under the **Modified MIT License** — see `LICENSE` for details.

---