# README: File Monitor

## Introduction

**File Monitor** is a console application developed in C++ using the Qt framework as part of Laboratory Work #1: \"File Monitoring.\" The program is designed to monitor selected files for changes in their existence and size, outputting notifications to the console.

## Task Description

The goal is to create a console application that tracks changes in selected files, focusing on two characteristics:
- **Existence**: Whether the file exists.
- **Size**: The file's size in bytes.

The program outputs notifications based on the following situations:
1. **File exists and is not empty**: Displays the file's existence and size.
2. **File exists and has been modified**: Displays the file's existence, a modification notice, and size.
3. **File does not exist**: Displays a message indicating the file's absence.

Upon detecting a change in a file's state (an event), the application outputs a corresponding message. It uses Qt's signal-slot mechanism to handle file state change events and operates in an infinite loop, updating file states every 100 milliseconds (e.g., using `std::this_thread::sleep_for(std::chrono::milliseconds(100))`).

## Requirements

- Compiler supporting C++11 or higher.
- Qt framework (version 5 or later).
- Operating system: Windows.

## Project Structure

### Classes and Interfaces

- **`FileObserver`**
  - Main monitoring class.
  - Checks file states every 100 ms.
  - Emits signals on changes.
- **`IFileContainer`**
  - Interface for file containers.
  - Implementations:
    - **`StaticFileContainer`**: Stores a static list of files in a vector.
    - **`DynamicFileContainer`**: Reads file paths from `fileContainer.txt` and updates dynamically.
- **`ILog`**
  - Logging interface.
  - Implementation:
    - **`ConsoleLog`**: Outputs messages to the console with optional timestamps.
- **`main.cpp`**
  - Entry point.
  - Initializes objects and starts the monitoring loop.

### UML Diagram

A visual representation of the project structure: ![UML Diagram](uml.drawio.svg)

## Implementation

- **Monitoring**: `FileObserver` uses `QFileInfo` to check file existence and size, with a 100 ms delay via `std::this_thread::sleep_for`.
- **Signals and Slots**: Qt handles events asynchronously (e.g., `onFileUpdate` signal triggers `ConsoleLog` output).
- **Containers**: `DynamicFileContainer` reads `fileContainer.txt` using `std::ifstream` and refreshes the file list.

## Author

### Aleksandr Gorevoy
