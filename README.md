# COMP3004Final

Navin Haider 101081934
Contributons: coding logic for the device, creation of assets, testing and bug fixing, and tracibilty matrix, uml diagram

Hassan Allam 100981031 
Contributons: GUI button + logic, coding logic for device, admin panel, database, sequence diagrams, testing and bug fixing, use cases

Mohamed Abou Ziab 101119933
Contributons: GUI button + logic, use cases, and activity and state diagrams, testing and bug fixing

Leo Xu 101149896
Contributons: Coding dynamic features of device (ex: intensity, battery depletion), testing and bug fixing, and use cases

    Tested Scenarios:
    We had tested scenario for each use case and project requirement.
    
        Normal case: Have the user select a session, and have it end normally without issue
        
        Battery depletion: Verify that the user is notified of low battery during a session, and device turns off, and is unable to turn on due to insufficient power
        
        Connection: Verify that session cannot start if ces, and clips are not connected, and at the beginning o fthe session it shows you current connection level
        
        Intensity: Verify that you can change intensity before and during a session.
        
        Selecting a session: Verify you can select different types of sessions.
        
        Recording: Verify that if a record is selected that the time, session type, and intensity is saved to the recording history in admin.
        
        No session selected: Verify that if a session has not been started within a period of time that the device will turn off by itself.
        

    Submission Structure:

    COMP3004Final-main -> 

        team35 -> 

            -- A collection of png's used for the GUI 
            icon -> 
                icons_off 
                icons_on
            progress 

            -- Database class that holds the session history as a QVector of QStringLists
            db.cpp 
            db.h 

            images_resource.qrc

            -- QT C++ generated main class
            main.cpp
            main.h

            -- QT C++ mainwindow function, bulk of the code logic is based in mainwindow.cpp
            mainwindow.ui 
            mainwindow.h
            mainwindow.cpp

            team35.pro 

        .gitignore 
        
        

Tested Scenarios 

Scenario's that passed 

    - User trying to turn on the batter at 0 % 
    
    - User removing ear connection and/or ces connection during session selection/sessions
    
    - Battery running out during session time 
    
    - Interuptting soft off resets the timer 
    
    - User changing intensity during session 
    
    - Changing intensity during session time while recording saves the last intensity set 
    
    - User cannot connect CES module or Ear clips while device is powered on
    
    - User can power off the machine during a session
    
    - Machine powers off after 30 seconds if the user fails to confirm a session time/session length 
    
 Scenario's that failed 
 
    - User cannot select a session from their history if there is only 1 session to select from 
