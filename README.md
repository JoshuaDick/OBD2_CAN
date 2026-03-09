# OBD2_CAN
Custom OBD2 reader built with Arduino CANBed V1. Also some reverse engineering for specific manufacturers.

## Faultcodes.md
Contains a list of OBD2 fault codes for interpretation after retrieving them through the software.

## ChevySensors.md
Contains a list of GM specific addresses on the CAN bus for various sensors (still unverified atm)

## GUI.py
Front end user interface for interacting with the Arduino CANBed when it is plugged in.

## Embedded.ino
Embedded code to flash onto the Arduino CANBed V1 so it can read/write to the CAN bus
