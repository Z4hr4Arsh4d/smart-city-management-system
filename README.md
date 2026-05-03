# Smart City Management System (C++)

A comprehensive Smart City simulation system developed in C++ that integrates multiple city services such as education, transport, healthcare, population management, and commercial systems into a single platform.

The system is menu-driven and allows users to interact with different modules representing real-world city operations.

---

##  Objective

To simulate a real-world smart city by integrating multiple management systems using programming concepts like modular design, data structures, and graph-based modeling.

---

## Modules Implemented

### Education Module

* School registration and management
* Student and faculty handling
* Subject-based search
* Nearest school detection
* Organogram system

---

### Medical Module

* Hospital management
* Emergency bed tracking
* Doctor registration
* Patient handling
* Nearest hospital search

---

### Pharmacy Module

* Pharmacy management
* Medicine search (by name & formula)
* Nearest pharmacy detection

---

### Transport Module

* Bus system simulation
* Route tracking
* Shortest path between stops
* Emergency routing
* Bus company management

---

### Population Module

* Person registration
* Family tree system
* Relationship management
* Population statistics (house, street, sector, city)

---

### Commercial Module

* Mall registration
* Product management
* Category-based search
* Nearest mall detection

---

### Public Facilities Module

* Mosques, parks, water coolers
* Search and nearest facility

---

### Map Module

* Sector-based city graph
* Shortest path between sectors
* Sector connectivity and degree
* Facility mapping per sector

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Graph Data Structures
* File Handling (CSV datasets)

---

## Dataset Usage

The system loads data from CSV files such as:

* `sectors.csv`
* `schools.csv`
* `hospitals.csv`
* `pharmacies.csv`
* `population.csv`
* `stops.csv`
* `buses.csv`

---

## How to Run

1. Open the project in a C++ environment
2. Make sure all dataset files are present in the correct folder
3. Compile the project
4. Run the program

---

## System Design

* Central controller: `CityManager` handles all modules
* Graph structure used for:

  * Sector connectivity
  * Shortest path calculations
* Modular architecture for scalability

---

## Project Structure

* `Source.cpp` → Main entry point
* `src/` → All modules (education, transport, medical, etc.)
* `dataset/` → CSV data files
* `*.h` → Header files

---

## Known Issues / Improvements

* Some modules can be further optimized
* UI is console-based and can be improved
* Error handling can be enhanced
* Performance improvements possible for large datasets

---

## Future Improvements

* GUI-based interface
* Database integration
* Real-time simulation features
* Improved module interaction

---

## Team Members

Zahra Arshad
Ahmed Ubaid
Tayyab Waheed

---
