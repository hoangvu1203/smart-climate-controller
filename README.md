# Smart Climate Controller System (RTOS-Based)

This project implements a real-time climate control system on an ESP32-S3 (YoloUNO) development board using a cooperative scheduler and FreeRTOS. The system reads temperature and humidity from a DHT21 sensor and uses threshold-based logic to control a heater, cooler, and humidifier, with LED indicators for each state.

## 🧠 Key Features

- 🔁 **Real-Time Scheduling**: Custom cooperative scheduler with 1 ms tick resolution driven by FreeRTOS.
- 🌡️ **Sensor Integration**: Periodic readings from a DHT21 sensor (every 5 seconds).
- 🔥 **Actuator Control**:
  - **Heater**: Red/Orange/Green LED based on temperature thresholds.
  - **Cooler**: Turns on when too hot; turns off automatically after 5 seconds.
  - **Humidifier**: Runs a 3-phase FSM (Green → Yellow → Red) when humidity is too low.
- 💡 **Heartbeat**: On-board LED blinks every second to indicate system health.
- 🧱 **Modular Code Structure**: Separate modules for sensor reading, logic control, device drivers, and RTOS tasks.

## 🛠️ Hardware Requirements

- **ESP32-S3 (YoloUNO or equivalent)**
- **DHT21 Sensor**
- **Bi-color LEDs** for heater, cooler, humidifier (2 pins each)
- **On-board LED** (for heartbeat)

### Wiring Example:
| Component     | GPIO Pins     |
|---------------|---------------|
| DHT21         | A2 (Data), 3.3V, GND |
| Heater LED    | D6 & D7       |
| Cooler LED    | D8 & D9       |
| Humidifier LED| D10 & D17     |
| Heartbeat LED | D48           |

## 📁 Project Structure
project_climate/
├── src/
│ ├── main.ino # Main entrypoint
│ ├── scheduler/ # Custom scheduler
│ ├── platform/ # RTOS timer & heartbeat
│ ├── sensors/ # DHT21 sensor module
│ ├── control/ # LightControl logic
│ ├── devices/ # Heater, Cooler, Humidifier drivers
│ ├── tasks/ # Named task files
│ └── config.h # Pin mappings & thresholds
├── docs/ # Block diagram, FSM, timing chart
├── .gitignore
└── README.md


## 🚀 How It Works

1. `task_ReadSensors()` is scheduled every 5000 ms to read temperature and humidity.
2. Readings are passed to `LightControl_Update()`, which decides:
   - Heater color (RED, ORANGE, GREEN)
   - Whether to activate the cooler for 5 seconds
   - Whether to start the humidifier FSM
3. The `vTimerTask` (FreeRTOS) updates the scheduler every 1 ms and toggles the system heartbeat LED every second.
4. The scheduler calls `SCH_Dispatch_Tasks()` from the main loop to execute due tasks.

## 📷 Diagrams

- 🧩 [System Block Diagram](docs/SystemDesign_diagram.png)
- 🔄 [Humidifier State Machine](docs/Humidifier_FSM.png)
- 📉 [Task Timing Diagram](docs/timing_diagram.png)

## 💻 Development Environment

- **Arduino IDE**
- **DHT sensor library** by Adafruit
- **FreeRTOS** support for ESP32 (bundled with ESP32 board core)


