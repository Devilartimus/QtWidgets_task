# Touchstone data visualization and processing software
---
## Requirements:

- Windows >= 10
- Qt >= 5
- MinGw compiler
---
## Instructions for building and running the application:

### 1. Clone the repo

    git clone https://github.com/Devilartimus/QtWidgets_task  
    cd QtWidgets_task
### 2. Build project via Qt Creator
1. Open *QT Creator*
2. Open project by choosing *CMakeList.txt*
3. Select *Release* build in Qt configuration
4. Press *Build -> Build Project*
5. After the build is complete, run the project via Qt Creator or via the executable file in the *Release* directory

---
### 3.Deploy build 
1. Open Command Prompt and head to *Release* directory  
   
        cd build\<your_directory>_Release  

2. Run *windeployqt* build

        windeployqt Touchstone_Task.exe -dir <your_deploy directory>
    
3. After build complete copy following files from MinGw directory (By default: *Qt\6.7.2\mingw_64\bin*) to deploying directory.
    1. libgcc_s_seh-1.dll
    2. libstdc++-6.dll
    3. libwinpthread-1.dll  
    
4. Copy *.exe* file from *Release* directory to *deploy* directory and start the .exe file
5. Pack the directory to archive to share it
6. To start the software launch *.exe* file

---
## How to use
1. Press *Select file* button
2. Select *Touchstone* file *(.s1p or .s2p)*
3. The program will display a graph of the data from the file.
