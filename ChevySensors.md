# Chevrolet / GM CAN Bus Signal Reference

## Network Types
- High Speed CAN (Powertrain): 500 kbps
- Low Speed GMLAN (Body): 33.3 kbps
- Diagnostic CAN: 500 kbps
- LIN buses for sensors and modules

---

# Powertrain Signals

## Engine Status
- ID 0x0C9: Engine RPM
- ID 0x0CA: Engine RPM Validity
- ID 0x0CB: Engine Running Status
- ID 0x0CC: Engine Torque
- ID 0x0CD: Engine Torque Request
- ID 0x0CE: Engine Torque Delivered
- ID 0x0CF: Engine Torque Limit

## Throttle / Air
- ID 0x0AA: Throttle Position
- ID 0x0AB: Throttle Position Commanded
- ID 0x0AC: Throttle Motor Current
- ID 0x0AD: Throttle Motor Duty Cycle
- ID 0x0AE: Throttle Plate Angle
- ID 0x0AF: Throttle Plate Status

## Pedal Position
- ID 0x0B4: Accelerator Pedal Position
- ID 0x0B5: Accelerator Pedal Sensor 1
- ID 0x0B6: Accelerator Pedal Sensor 2
- ID 0x0B7: Pedal Plausibility Status

## Airflow
- ID 0x0D1: Mass Air Flow
- ID 0x0D2: Intake Air Temperature
- ID 0x0D3: Intake Air Pressure
- ID 0x0D4: Manifold Absolute Pressure
- ID 0x0D5: Barometric Pressure
- ID 0x0D6: Intake Air Humidity

## Fuel System
- ID 0x0E1: Fuel Rail Pressure
- ID 0x0E2: Fuel Pump Duty Cycle
- ID 0x0E3: Fuel Trim Short Term
- ID 0x0E4: Fuel Trim Long Term
- ID 0x0E5: Fuel Consumption Rate
- ID 0x0E6: Fuel Injector Pulse Width
- ID 0x0E7: Fuel Pressure Command

## Engine Temperatures
- ID 0x0F1: Intake Air Temperature
- ID 0x0F2: Coolant Temperature
- ID 0x0F3: Engine Oil Temperature
- ID 0x0F4: Cylinder Head Temperature
- ID 0x0F5: Exhaust Gas Temperature

---

# Ignition / Timing

- ID 0x101: Ignition Timing Advance
- ID 0x102: Knock Retard
- ID 0x103: Spark Cylinder 1
- ID 0x104: Spark Cylinder 2
- ID 0x105: Spark Cylinder 3
- ID 0x106: Spark Cylinder 4

---

# Transmission Signals

## Gear and State
- ID 0x2A1: Current Gear
- ID 0x2A2: Selected Gear
- ID 0x2A3: Gear Command
- ID 0x2A4: Transmission Mode
- ID 0x2A5: Transmission Limp Mode

## Temperatures
- ID 0x2A6: Transmission Oil Temperature
- ID 0x2A7: Transmission Clutch Temperature

## Torque Converter
- ID 0x2A8: Torque Converter Slip
- ID 0x2A9: Torque Converter Lock Status

---

# Vehicle Motion

## Speed
- ID 0x1F5: Vehicle Speed
- ID 0x1F6: Speed Validity
- ID 0x1F7: Speed Source

## Wheel Speed
- ID 0x1B0: Front Left Wheel Speed
- ID 0x1B1: Front Right Wheel Speed
- ID 0x1B2: Rear Left Wheel Speed
- ID 0x1B3: Rear Right Wheel Speed

## Steering
- ID 0x1A1: Steering Angle
- ID 0x1A2: Steering Angle Rate
- ID 0x1A3: Steering Torque
- ID 0x1A4: Driver Steering Torque

## Stability Control
- ID 0x1A5: Yaw Rate
- ID 0x1A6: Lateral Acceleration
- ID 0x1A7: Longitudinal Acceleration
- ID 0x1A8: Stability Control Active

---

# Brake System

- ID 0x224: Brake Pedal Position
- ID 0x225: Brake Pressure
- ID 0x226: ABS Active
- ID 0x227: Traction Control Active
- ID 0x228: Electronic Stability Control State
- ID 0x229: Parking Brake Status

---

# Body Control Module (BCM)

## Doors
- ID 0x3D1: Driver Door Status
- ID 0x3D2: Passenger Door Status
- ID 0x3D3: Rear Left Door Status
- ID 0x3D4: Rear Right Door Status
- ID 0x3D5: Trunk Status
- ID 0x3D6: Hood Status

## Lighting
- ID 0x3E1: Headlights
- ID 0x3E2: High Beam Status
- ID 0x3E3: Low Beam Status
- ID 0x3E4: Daytime Running Lights
- ID 0x3E5: Fog Lights
- ID 0x3E6: Brake Lights
- ID 0x3E7: Reverse Lights

## Turn Signals
- ID 0x3E8: Left Turn Signal
- ID 0x3E9: Right Turn Signal
- ID 0x3EA: Hazard Lights

---

# Driver Inputs

- ID 0x4A1: Steering Wheel Buttons
- ID 0x4A2: Cruise Control Status
- ID 0x4A3: Cruise Set Speed
- ID 0x4A4: Cruise Cancel
- ID 0x4A5: Cruise Resume

---

# HVAC

- ID 0x6A1: Cabin Temperature
- ID 0x6A2: Cabin Set Temperature
- ID 0x6A3: Fan Speed
- ID 0x6A4: HVAC Mode
- ID 0x6A5: AC Compressor Status
- ID 0x6A6: Recirculation Mode

---

# Fuel System

- ID 0x5B1: Fuel Level
- ID 0x5B2: Fuel Pump Status
- ID 0x5B3: Fuel Pump Duty
- ID 0x5B4: Fuel Range Estimate

---

# Battery / Electrical

- ID 0x7A1: Battery Voltage
- ID 0x7A2: Battery Current
- ID 0x7A3: Alternator Output
- ID 0x7A4: Charging System Status

---

# Security

- ID 0x7E1: Immobilizer Status
- ID 0x7E2: Key Authentication
- ID 0x7E3: Alarm Status

---

# Diagnostics

- ID 0x7DF: OBD Broadcast Request
- ID 0x7E0: Engine ECU Diagnostic Request
- ID 0x7E8: Engine ECU Response
- ID 0x7E1: Transmission ECU Request
- ID 0x7E9: Transmission ECU Response

---

# Driver Assistance

- ID 0x520: Lane Assist Status
- ID 0x521: Lane Departure Warning
- ID 0x522: Forward Collision Warning
- ID 0x523: Adaptive Cruise Status

---

# Misc Vehicle Signals

- ID 0x600: Odometer
- ID 0x601: Trip Distance
- ID 0x602: Outside Air Temperature
- ID 0x603: Compass Heading
- ID 0x604: GPS Speed
