# Laboratory Work #1: File Monitoring
## Task Description
The goal of this project is to create a console-based program that monitors selected files for changes. The monitoring is limited to two characteristics:
1. **File Existence**: Whether the file exists or not.
2. **File Size**: The size of the file in bytes.
The program will output notifications to the console whenever changes in the monitored file(s) occur.
### Possible File States
The program handles the following situations for the monitored file:
1. **File exists and is not empty**: Displays a message confirming the file's existence and its size.
2. **File exists and has been modified**: Displays a message confirming the file's existence, a notification about the modification, and its new size.
3. **File does not exist**: Displays a message stating that the file does not exist.
Whenever a change in the file's state is detected (an event occurs), the program outputs a corresponding message to the console.
### Implementation Details
- The program uses a **signal-slot mechanism** to handle events related to changes in the monitored file.
- Monitoring is implemented using an infinite loop that updates the state of the observed file(s) every **1000/FileObserver::_refreshRate** miliseconds. For example:
  ```cpp
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ```
## Repository Structure
- **Main Branch**: Contains the solution to this laboratory work.
- Source files and implementation details can be found in the repository.
## Technologies Used
- **QT Libraries**: Qt objects and core application for **signal - slot mechanism**
- **C++**: Core language for implementation.
- **Standard Library**: For file handling (<filesystem>or<fstream>), threading (<thread>), and timing (<chrono>).
## Notes
- This implementation assumes a basic console interface.
- The signal-slot mechanism is used to decouple file state checking from event handling.
- The refresh rate is adjustable field in FileObserver class.
## Author
- GitHub: [Helbushek](https://github.com/Helbushek)

