**Automotive ECU Secure Boot & Firmware Protection Simulation**

## Overview
This project simulates secure boot mechanism used in automotive ECUs to ensure firmware authenticity and prevent rollback attacks.

## Features
- Firmware signature verification using cryptography
- Tamper detection
- Rollback attack detection
- Secure boot decision logic
- Security event logging

## Technologies
- C programming
- OpenSSL
- Linux environment

## Project Structure
src/ - secure boot verification code  
firmware/ - firmware and version files  
keys/ - cryptographic keys  
logs/ - security logs  
docs/ - architecture diagrams  

## Use Case
Demonstrates how automotive ECUs ensure only trusted firmware runs in safety-critical systems such as EV battery management and powertrain controllers.
