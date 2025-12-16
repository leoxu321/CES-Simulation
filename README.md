# CES Device Simulator

## Overview

This project is a **graphical simulation of a CES (Cranial Electrotherapy Stimulation) medical device**. The system models the behavior of a real consumer medical device, including **session control, intensity adjustment, safety constraints, persistence, and user interaction through a GUI**.

The application focuses on **state-based system design**, **user-driven workflows**, and **robust constraint enforcement**, ensuring that invalid or unsafe actions are prevented through software logic.

---

## Key Features

* **Interactive GUI-based device simulation**

  * Button-driven interface for powering on/off, selecting sessions, and adjusting intensity
  * Visual indicators and icons reflecting device state

* **Session management**

  * Users can start, confirm, and complete therapy sessions
  * Session duration and intensity are tracked throughout execution
  * Session history is recorded and persisted

* **Dynamic device behavior**

  * Real-time intensity adjustment during active sessions
  * Battery depletion simulation based on usage
  * Automatic power-off after inactivity

* **Safety and constraint enforcement**

  * Prevents unsafe operations (e.g., connecting modules while powered on)
  * Requires confirmation before starting sessions
  * Enforces correct operational order through state logic

* **Persistent storage**

  * Session history stored using a lightweight database layer
  * Previous sessions can be reviewed on subsequent runs

---

## System Architecture

### Device Logic

* Core device behavior implemented in C++
* State-based logic ensures valid transitions between:

  * Powered off
  * Idle
  * Session setup
  * Active session
* Handles intensity changes, timing, and battery state

### GUI Layer

* Implemented using **Qt (Qt Widgets)**
* Provides the primary user interaction surface
* Maps user input (button presses) to device actions using Qt signals and slots
* Updates visual indicators in response to device state changes

### Database Layer

* Stores session data such as:

  * Session duration
  * Intensity levels
  * Completion status
* Enables session history retrieval

---

## Tested Scenarios

The system was tested against all defined use cases and project requirements, including:

* Changing intensity during an active session
* Persisting the last intensity value when recording sessions
* Preventing hardware connections while powered on
* Powering off safely during an active session
* Automatic shutdown after inactivity if a session is not confirmed

### Known Limitation

* Session selection from history is limited when only a single historical session exists

---

## Technologies Used

* **Language:** C++
* **Language:** C++
* **GUI:** Qt (Qt Widgets)
* **Persistence:** Lightweight database abstraction
* **Design Artifacts:** UML diagrams, use-case diagrams, sequence diagrams, state diagrams, use-case diagrams, sequence diagrams, state diagrams

---

## Why This Project Is Significant

This project demonstrates:

* **State-driven system design** for safety-critical applications
* Careful handling of **user workflows and constraints**
* Integration of **GUI, core logic, and persistence layers**
* Strong emphasis on **correctness, testing, and validation**

Simulating a medical device introduces real-world constraints where incorrect behavior is unacceptable, making this project a strong example of disciplined software engineering.

---

## How to Run

1. Open the project in a C++ IDE (e.g., Visual Studio, CLion)
2. Build the project using the provided configuration
3. Run the application executable
4. Interact with the device through the GUI

---

## Team

* Navin Haider
* Hassan Allam
* Mohamed Abou Ziab
* Leo Xu
