# Operating Systems and Security Coursework

## Project Title
Hospital-Based Operating System and Security Simulation

## Module Code
ST5004CEM

## Submitted By
Babita Kumari Adhikari

## Submitted To
Rupak Rajbanshi

## Submission Date
31st July 2025

---

## Project Overview

This project demonstrates important concepts of Operating Systems and Security using a hospital-based scenario. The coursework is divided into four main tasks. Each task shows how operating system concepts can be applied in a real hospital emergency system.

The project includes process management, thread management, memory management, secure file management, encryption, audit logging and client-server network communication.

---

## Tasks Included

### Task 1: Hospital Emergency Process and Thread Management

This task demonstrates how an operating system manages processes and threads in a hospital emergency system.

It includes:

- Process creation using `fork()`
- Parent and child process execution
- Thread creation using POSIX threads
- Mutex synchronization
- Race condition prevention
- Round Robin scheduling
- Deadlock prevention

In this task, a hospital emergency system is used as a scenario where multiple patient-related operations run at the same time.

---

### Task 2: Hospital Emergency Memory Management Simulation

This task demonstrates memory management using paging and page replacement algorithms.

It includes:

- Paging system with configurable page size
- Logical address calculation
- Page number and offset calculation
- FIFO page replacement
- LRU page replacement
- Page hit and page fault calculation

In this task, the hospital emergency dashboard is divided into pages such as triage, vitals, lab results, X-ray, medication and patient notes.

---

### Task 3: Hospital Patient Secure File Management System

This task implements a secure file management system for hospital patient records.

It includes:

- User authentication
- Role-based permission system
- Audit logging
- File creation
- File writing
- File reading
- File deletion
- AES-256-CBC encryption using OpenSSL
- Decryption using correct password

The system includes three roles: admin, doctor and nurse. Each role has different access permissions.

---

### Task 4: Hospital Emergency Client-Server Network Communication

This task demonstrates TCP socket programming in C.

It includes:

- Basic TCP server
- Basic TCP client
- Client-server communication
- Command-based data exchange protocol
- Login authentication
- Data validation
- Multiple concurrent client handling using `fork()`

The client can request hospital information such as patient details, lab results, bed availability and emergency alerts.

---

## Technologies Used

- C Programming
- Linux Terminal
- GCC Compiler
- POSIX Threads
- Mutex
- Round Robin Scheduling
- Paging
- FIFO Page Replacement
- LRU Page Replacement
- OpenSSL
- TCP Socket Programming
- Git
- GitHub

---

## How to Compile and Run

Task 1: Hospital Emergency Process and Thread Management

Compile Task 1:
gcc task1_process_management.c -o task1_process_management -pthread
./task1_process_management

Task 2: Hospital Emergency Memory Management Simulation

Compile Task 2:
gcc task2_memory_management.c -o task2_memory_management
./task2_memory_management

Task 3: Hospital Patient Secure File Management System

Compile Task 3:
gcc task3_secure_file_system.c -o task3_secure_file_system
./task3_secure_file_system

Task 4: Hospital Emergency Client-Server Network Communication

Task 4 needs two terminals.

In Terminal 1, open project folder:
Task 4: Hospital Emergency Client-Server Network Communication

Task 4 needs two terminals.
In Terminal 1, open project folder:
gcc task4_server.c -o task4_server
./task4_server
In Terminal 2, open project folder:
cd ~/Desktop/Operating_System
gcc task4_client.c -o task4_client
./task4_client
