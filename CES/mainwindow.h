#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QTimer>
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    // buttons
    // trouble shooting
    int time;
    bool powerOn = false;
    bool menuPower = false;

    // bool checks if the user is cycling through menu options via power button
    bool cycleTime = false;

    // bool that checks if the user can cycle through the sessions
    bool cycleSession = false;
    bool confirm = false;

    bool intensityUp = false;
    bool intensityDown = false;
    int totalIntesity = 0;
    bool setIntesity = false;
    bool confirmIntesity = false;

    // ces connection for ear clips
    bool ces = false;

    // softoff bool
    bool softOffBool = false;
    bool batteryDead = false;

    bool isBlinking = false;
    int bat =0;

    int initalIntensity = 0;

    // boolean to record session
    bool recording = false;

    QTime releaseTime;
    QTime releaseTimeConfirm;

    db database;

    void sessionTimeDelay();

    private slots:
    // buttons
    void updateUI();
    void on_powerPushButton_released();
    void on_powerPushButton_pressed();
    void connectionBarUI();
    void aboveLOnROff();
    void sessionSelector();

    void batteryLevel();
    void batteryDecay();
    void initUI();
    void turnOff();
    void menuPowerOn();

    void cycleSessionTime();
    void selectIntesity();
    void turnOffTimeMenu();
    void turnOffSessionMenu();

    void cycleSessions();
    void on_upPushButton_released();
    void on_downPushButton_released();
    void on_confirmPushButton_pressed();
    void on_confirmPushButton_released();

    void leftEarConnection();
    void rightEarConnection();
    void cesConnection();

    void softOff();
    void softOffHelper();

    void batteryLevelOff();
    void batteryBlinking();

    void Recording(int);
    void setHistorySession();

    void setIntensityBar();
};
#endif // MAINWINDOW_H
