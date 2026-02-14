# Sleep Apnea Detection Device

Wearable biomedical monitoring system for detecting sleep apnea events during sleep.

## Overview

University engineering design project built as part of BEng Biomedical and Healthcare Engineering at City St George's, University of London (2024-2025). 

Designed a turtleneck-style wearable device that monitors breathing patterns in real-time and alerts users to potential sleep apnea events.

## Features

- Real-time breathing detection via conductive stretch sensor around neck
- Baseline calibration algorithm with 100-sample averaging on startup
- Smart activation requiring 3 consecutive breaths before monitoring starts
- Auto-deactivation detecting device removal via 30-second flatline check
- Bluetooth data transmission for wireless real-time monitoring
- Immediate piezo buzzer alerts when apnea event detected

## Hardware Components

- Arduino Nano (ATmega328P microcontroller)
- Conductive rubber stretch sensor for detecting chest/neck expansion
- HC05 Bluetooth module for wireless communication
- Piezo buzzer for auditory alerts
- 3.7V LiPo battery for portable power
- Custom turtleneck housing with elastic fabric
- Silicone wire for flexible, skin-safe connections
- Plastic enclosure protecting electronics during sleep

## How It Works

1. **Calibration Phase**: System samples stretch sensor 100 times on startup to establish breathing baseline
2. **Activation Phase**: Monitors for 3 consecutive breaths to confirm device is properly worn
3. **Monitoring Phase**: Continuously tracks breathing by measuring delta from baseline
4. **Detection Logic**: If no breath detected for 8 seconds, triggers apnea alert via buzzer
5. **Safety Feature**: If no movement detected for 30 seconds, assumes device removed and automatically deactivates

## Results

Successfully detected breathing patterns and apnea events during testing. Device accurately distinguished between normal breathing cycles, apnea events (breathing pauses >8 seconds), and device removal scenarios.

## My Role
Led 4-person engineering team with responsibility for:

- **Project Management** - Coordinated team tasks and deliverables
- **Hardware Design** - Designed circuit, soldered all components, built physical prototype
- **Software Development** - Wrote complete Arduino codebase in C++
- **Systems Integration** - Implemented Bluetooth communication and sensor interfacing
- **Technical Documentation** - Created project reports, design specifications, and bill of materials

## Future Improvements

If rebuilding this project, I would implement:

**Signal Processing**
- Add digital filtering (moving average, low-pass filter) to reduce sensor noise
- Implement pattern recognition algorithms beyond simple threshold-based detection

**Data Management**
- SD card storage for post-sleep analysis and pattern tracking over time
- Persistent calibration storage in EEPROM to avoid recalibration each startup

**User Interface**
- Custom mobile app with real-time graphing instead of generic Bluetooth terminal
- Multiple alert modes including vibration motor for silent alerts
- Battery monitoring and low-battery warning system

**Code Optimization**
- Use interrupts and millis() timing instead of delay() for more responsive operation

## Technical Challenges Solved

- Designed baseline calibration system to account for individual breathing variations
- Implemented state machine to prevent false positives during device activation
- Created logic to distinguish between apnea events and device removal
- Optimized sensor placement on neck for reliable breathing movement detection
- Ensured electrical safety with proper insulation and low-voltage design (3.7V)

## Repository Contents

- `sleep_apnea_detector.ino` - Complete Arduino sketch with embedded C++ code

## Technical Stack

- **Language**: C++ (Arduino framework)
- **Platform**: Arduino Nano (ATmega328P)
- **Communication**: Serial UART, Bluetooth (HC05)
- **Sensors**: Analog input, ADC conversion
- **Development**: Arduino IDE

## Design Process

Evaluated three wearable concepts using weighted design matrix:

**Smartwatch** - Rejected due to comfort issues during sleep and insufficient breathing measurement accuracy

**Smart Ring** - Rejected due to size constraints limiting component integration and inability to measure breathing directly

**Turtleneck** - Selected for optimal balance of comfort, accuracy, and practicality. Final design scored highest across functionality, usability, and safety criteria.

## License

MIT License
