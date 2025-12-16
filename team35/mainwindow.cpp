#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include <QPushButton>
#include <QThread>
#include <QTime>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initiate the ui
    initUI();
    updateUI();

    // detect change in connection level
    connect(ui->connectionLevelAdminComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(connectionBarUI()));

    //detect change in battery level | NOT NEEDED SINCE BATTERY LEVEL IS NOT DYNAMICALLY DISPLAYED
    connect(ui->batteryLevelAdminSpinxBox, SIGNAL(valueChanged(double)), this, SLOT(batteryLevel()));

    // detect change via admin panel for time
    connect(ui->timeAdminComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(cycleSessionTime()));

    // detect change via admin panel for session selected
    connect(ui->sessionComboBox, SIGNAL (currentIndexChanged(QString)), this, SLOT(cycleSessions()));


    // detect changes via admin panel for ear clip boolean values
    connect(ui->leftEarClip, SIGNAL (currentIndexChanged(QString)), this, SLOT (leftEarConnection()));
    connect(ui->rightEarClip, SIGNAL (currentIndexChanged(QString)), this, SLOT (rightEarConnection()));

    // detect changes for ces clip
    connect (ui->cesComboBox, SIGNAL (currentIndexChanged(QString)), this, SLOT (cesConnection()));

    // detect changes for recording
    //connect(ui->recordBox, SIGNAL (currentIndexChanged(QString)), this, SLOT (Recording(int)));

    //history session set
    connect(ui->historyComboBox, SIGNAL (currentIndexChanged(QString)), this, SLOT (setHistorySession()));

    QPixmap sidegraph (":/progress/progress/side_number_bar.png");
    ui->secondGraphLabel->setPixmap(sidegraph);

}


MainWindow::~MainWindow()
{
    delete ui;
}

// --------------------------------------- UI UPDATES -------------------------------------------------
// init thje UI
void MainWindow::initUI()
{
    QPixmap rImg2 (":/icon/icons_off/justR_Icon_off.png");
    ui->rightLabel->setPixmap(rImg2);

    QPixmap lImg2 (":/icon/icons_off/justL_Icon_off.png");
    ui->leftLabel->setPixmap(lImg2);

    QPixmap aboveRImg (":/icon/icons_off/aboveR_Icon_off.png");
    ui->aboveRightLabel->setPixmap(aboveRImg);

    QPixmap aboveLImg (":/icon/icons_off/aboveL_Icon_off.png");
    ui->aboveLeftLabel->setPixmap(aboveLImg);
    // setup oasis pro background image
    QPixmap oasis_pro_img (":/icon/oasis_pro.png");
    //    int w = ui->oasis_background->width();
    //    int h = ui->oasis_background->height();
    //    ui->oasis_background->setPixmap(oasis_pro_img.scaled(w,h, Qt::KeepAspectRatio));
    ui->oasis_background->setPixmap(oasis_pro_img);

    //setup connection level label image
    QPixmap connection_bar (":/progress/progress0.png");
    ui->connectionLevelLabel->setPixmap(connection_bar);

    QPixmap sidegraph (":/progress/progress/side_number_bar.png");
    ui->secondGraphLabel->setPixmap(sidegraph);

    // populate combo session drop down menu
    ui->sessionComboBox->addItems({ "MET", "Sub Delta", "Delta", "Theta", "Alpha", "Beta 1", "Beta 2", "100Hz"});

    // populate time combo sessions drop down menu
    ui->timeAdminComboBox->addItems({"20", "40", "180", "Custom"});

    // populate connection level drop down menu
    ui->connectionLevelAdminComboBox->addItems({"Bad Connection", "Okay Connection", "Excellent Connection"});

    ui->recordBox->addItems({"False", "True"});

    // populating the ear clips drop down menu
    ui->leftEarClip->addItems({"False", "True"});
    ui->rightEarClip->addItems({"False", "True"});

    // populate CES drop down menu
    ui->cesComboBox->addItems({"False", "True"});

    ui->console->setReadOnly(true);

    QPixmap cesOff (":/icon/icons_off/heart_off.png");
    ui->cesLabel->setPixmap(cesOff);

    // ui for buttons
    QIcon powerImg (":/icon/power_button.png");
    ui->powerPushButton->setIcon(powerImg);

    QIcon downImg (":/icon/down_arrow.png");
    ui->downPushButton->setIcon(downImg);

    QIcon upImg (":/icon/up_arrow.png");
    ui->upPushButton->setIcon(upImg);

    QIcon confirmImg (":/icon/confirm_button.png");
    ui->confirmPushButton->setIcon(confirmImg);

    ui->console->setReadOnly(true);
}

// update UI
void MainWindow::updateUI ()
{
    batteryLevel();

    if (powerOn == true && menuPower == true && ui->batteryLevelAdminSpinxBox->value() > 0)
    {
        menuPowerOn();
    }
    // power off the machine
    else if (powerOn == false || ui->batteryLevelAdminSpinxBox->value() == 0)
    {
        turnOff();
    }
}


//turns on the symbol above the L and turns off the one above the R
void MainWindow::aboveLOnROff(){
    QPixmap aboveLImg (":/icon/icons_on/aboveL_Icon.png");
    ui->aboveLeftLabel->setPixmap(aboveLImg);
    QPixmap aboveRImg (":/icon/icons_off/aboveR_Icon_off.png");
    ui->aboveRightLabel->setPixmap(aboveRImg);
}

//changes the symbols above the L and R
void MainWindow::sessionSelector(){
    if(powerOn == true){
        if(ui->sessionComboBox->currentText() == "MET"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "Delta"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "Theta"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "Alpha"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "SMR"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "Beta"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "100Hz"){
            aboveLOnROff();
        }else if(ui->sessionComboBox->currentText() == "Sub Delta"){
            QPixmap aboveLImg (":/icon/icons_off/aboveL_Icon_off.png");
            ui->aboveLeftLabel->setPixmap(aboveLImg);
            QPixmap aboveRImg (":/icon/icons_on/aboveR_Icon.png");
            ui->aboveRightLabel->setPixmap(aboveRImg);
        }
    }
}

// turn off the machine
void MainWindow::turnOff()
{
    // power off the machine
    // set the menu to turn off

    // turn off all the booleans
    menuPower = false;
    cycleSession = false;
    cycleTime = false;
    setIntesity = false;
    confirm = false;
    confirmIntesity = false;
    softOffBool = false;
    powerOn = false;
    isBlinking = false;
    bat = 0;

    turnOffTimeMenu();
    turnOffSessionMenu();
    cesConnection();

    // turn off power level and power leds
    QPixmap connection_bar (":/progress/progress/progress0.png");
    ui->connectionLevelLabel->setPixmap(connection_bar);

    QPixmap led_label ("");
    ui->ledLabel->setPixmap(led_label);

    // OFF LED's FOR THE GUI
    // ui for session LEDS
    QPixmap rImg2 (":/icon/icons_off/justR_Icon_off.png");
    ui->rightLabel->setPixmap(rImg2);

    QPixmap lImg2 (":/icon/icons_off/justL_Icon_off.png");
    ui->leftLabel->setPixmap(lImg2);

    QPixmap aboveRImg (":/icon/icons_off/aboveR_Icon_off.png");
    ui->aboveRightLabel->setPixmap(aboveRImg);

    QPixmap aboveLImg (":/icon/icons_off/aboveL_Icon_off.png");
    ui->aboveLeftLabel->setPixmap(aboveLImg);

    // icon for top left wave thingy
    QPixmap topLeftImg (":/icon/icons_off/topLeft_off.png");
    ui->topLeftLabel->setPixmap(topLeftImg);

    QPixmap cesOff (":/icon/icons_off/heart_off.png");
    ui->cesLabel->setPixmap(cesOff);

    ui->rightEarClip->setCurrentIndex(0);
    ui->leftEarClip->setCurrentIndex(0);
}

// turn on the session and all other led's after initial poweron
void MainWindow::menuPowerOn()
{
    // ON LED's FOR THE GUI
    // these dont turn on by default, only when the ears are connected
    //    QPixmap RImg (":/icon/icons_on/justR_Icon.png");
    //    ui->rightLabel->setPixmap(RImg);

    //    QPixmap LImg (":/icon/icons_on/justL_Icon.png");
    //    ui->leftLabel->setPixmap(LImg);

    QPixmap aboveRImg (":/icon/icons_on/aboveR_Icon.png");
    ui->aboveRightLabel->setPixmap(aboveRImg);

    QPixmap aboveLImg (":/icon/icons_on/aboveL_Icon.png");
    ui->aboveLeftLabel->setPixmap(aboveLImg);

    QPixmap metImg (":/icon/icons_on/metIcon.png");
    ui->metLabel->setPixmap(metImg);

    QPixmap subDeltaImg (":/icon/icons_on/subDelta.png");
    ui->subDeltaLabel->setPixmap(subDeltaImg);

    QPixmap deltaImg (":/icon/icons_on/delta.png");
    ui->deltaLabel->setPixmap(deltaImg);

    QPixmap thetaImg (":/icon/icons_on/theta.png");
    ui->thetaLabel->setPixmap(thetaImg);

    QPixmap alphaImg (":/icon/icons_on/alpha.png");
    ui->alphaLabel->setPixmap(alphaImg);

    QPixmap betaOneImg (":/icon/icons_on/beta1.png");
    ui->betaOneLabel->setPixmap(betaOneImg);

    QPixmap betaTwoImg (":/icon/icons_on/beta2.png");
    ui->betaTwoLabel->setPixmap(betaTwoImg);

    QPixmap hundredImg (":/icon/icons_on/100hz.png");
    ui->hundredabel->setPixmap(hundredImg);

    // ui for time period led's
    QPixmap thirdCircleImg (":/icon/icons_on/thirdCircle.png");
    ui->thirdCircle->setPixmap(thirdCircleImg);

    QPixmap quarterCircleImg (":/icon/icons_on/quarterCircle.png");
    ui->quarterCircleLabel->setPixmap(quarterCircleImg);

    QPixmap threeHourImg (":/icon/icons_on/3hour.png");
    ui->threeHourLabel->setPixmap(threeHourImg);

    QPixmap plusImg (":/icon/icons_on/plus.png");
    ui->plusLabel->setPixmap(plusImg);


    // icon for top left wave thingy
    QPixmap topLeftImg (":/icon/icons_on/topLeft.png");
    ui->topLeftLabel->setPixmap(topLeftImg);

    // code to automatically connect the ces connection and ear clips, since this should be the default state
    ces = true;
    ui->cesComboBox->setCurrentText("True");
    ui->rightEarClip->setCurrentText("True");
    ui->leftEarClip->setCurrentText("True");

    cesConnection();

    //start a timer, if the user doesnt select a session within 30 seconds, turn off

        QTime stop = QTime::currentTime().addSecs(30);

        while(QTime::currentTime() <= stop){


            if (QTime::currentTime() == stop && confirm == false && powerOn == true)
            {
                turnOff();
                break;
            }

            //stop loop if window is closed
            if(QCoreApplication::closingDown()){
                break;
            }
            //makes sure to handle other request whike delaying
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
     }
    connectionBarUI();
}

// turns off LED's for the sessions
void MainWindow::turnOffSessionMenu()
{
    QPixmap metImg (":/icon/icons_off/metIcon_off.png");
    ui->metLabel->setPixmap(metImg);

    QPixmap subDeltaImg (":/icon/icons_off/subDelta_off.png");
    ui->subDeltaLabel->setPixmap(subDeltaImg);

    QPixmap deltaImg (":/icon/icons_off/delta_off.png");
    ui->deltaLabel->setPixmap(deltaImg);

    QPixmap thetaImg (":/icon/icons_off/theta_off.png");
    ui->thetaLabel->setPixmap(thetaImg);

    QPixmap alphaImg (":/icon/icons_off/alpha_off.png");
    ui->alphaLabel->setPixmap(alphaImg);

    QPixmap betaOneImg (":/icon/icons_off/beta1_off.png");
    ui->betaOneLabel->setPixmap(betaOneImg);

    QPixmap betaTwoImg (":/icon/icons_off/beta2_off.png");
    ui->betaTwoLabel->setPixmap(betaTwoImg);

    QPixmap hundredImg (":/icon/icons_off/100hz_off.png");
    ui->hundredabel->setPixmap(hundredImg);
}

// turns off the LED's for time
void MainWindow::turnOffTimeMenu()
{
    // ui for time period led's
    QPixmap thirdCircleImg (":/icon/icons_off/thirdCircle_off.png");
    ui->thirdCircle->setPixmap(thirdCircleImg);

    QPixmap quarterCircleImg (":/icon/icons_off/quarterCircle_off.png");
    ui->quarterCircleLabel->setPixmap(quarterCircleImg);

    QPixmap threeHourImg (":/icon/icons_off/3hour_off.png");
    ui->threeHourLabel->setPixmap(threeHourImg);

    QPixmap plusImg (":/icon/icons_off/plus_off.png");
    ui->plusLabel->setPixmap(plusImg);
}


//---------------------------------------- DYNAMIC UI CHANGES ---------------------------------------------------
// update batterylevel bar based on qcombobox value
void MainWindow::batteryLevel()
{
    if (ui->batteryLevelAdminSpinxBox->value() > 0)
    {
        batteryDead = false;
    }


    if (powerOn == true && menuPower == false && batteryDead == false)
    {
        QPixmap led_label (":/icon/green_light.jpg");
        ui->ledLabel->setPixmap(led_label);

        if(ui->batteryLevelAdminSpinxBox->value() >= 80){
            QPixmap connection_bar (":/progress/progress/progress8.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 70 && ui->batteryLevelAdminSpinxBox->value() < 60){
            QPixmap connection_bar (":/progress/progress/progress7.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 60 && ui->batteryLevelAdminSpinxBox->value() < 70){
            QPixmap connection_bar (":/progress/progress/progress6.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 50 && ui->batteryLevelAdminSpinxBox->value() < 60){
            QPixmap connection_bar (":/progress/progress/progress5.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 40 && ui->batteryLevelAdminSpinxBox->value() < 50){
            QPixmap connection_bar (":/progress/progress/progress4.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 30 && ui->batteryLevelAdminSpinxBox->value() < 40){
            QPixmap connection_bar (":/progress/progress/progress3.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if(ui->batteryLevelAdminSpinxBox->value() >= 20 && ui->batteryLevelAdminSpinxBox->value() < 30){
            QPixmap connection_bar (":/progress/progress/progress2.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else{
            QPixmap connection_bar (":/progress/progress/progress1.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }
    }

}

void MainWindow::setIntensityBar()
{
    QString s2 = QString::number(totalIntesity);

    QPixmap connectionBar (":/progress/progress/progress"+s2+".png");
    ui->connectionLevelLabel->setPixmap(connectionBar);
}

// changes the 1-8 graph to reflect connection level
void MainWindow::connectionBarUI()
{

    if (menuPower == true)
    {

        if (ui->leftEarClip->currentText() == "False" || ui->rightEarClip->currentText() == "False")
        {
            QPixmap connection_bar (":/progress/progress/progressRed.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
            ui->connectionLevelAdminComboBox->setCurrentText("Bad Connection");
        }

        else if(ui->connectionLevelAdminComboBox->currentText() == "Excellent Connection")
        {
            QPixmap connection_bar (":/progress/progress/progress3.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if (ui->connectionLevelAdminComboBox->currentText() == "Okay Connection")
        {
            QPixmap connection_bar (":/progress/progress/progressYellow.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }

        else if (ui->connectionLevelAdminComboBox->currentText() == "Bad Connection")
        {
            QPixmap connection_bar (":/progress/progress/progressRed.png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }
    }

}



// simulates the soft off, gradual reduction of CES stim, power off at end, graph scrolls from 8 to 1

//cycle between session times with the powerbutton
void MainWindow::cycleSessionTime()
{
    if (cycleTime == true)
    {
        turnOffTimeMenu();

        if (ui->timeAdminComboBox->currentText() == "20")
        {
            QPixmap thirdCircleImg (":/icon/icons_on/thirdCircle.png");
            ui->thirdCircle->setPixmap(thirdCircleImg);
        }

        else if (ui->timeAdminComboBox->currentText() == "40")
        {
            QPixmap quarterCircleImg (":/icon/icons_on/quarterCircle.png");
            ui->quarterCircleLabel->setPixmap(quarterCircleImg);
        }

        else if (ui->timeAdminComboBox->currentText() == "180")
        {
            QPixmap threeHourImg (":/icon/icons_on/3hour.png");
            ui->threeHourLabel->setPixmap(threeHourImg);
        }

        else if (ui->timeAdminComboBox->currentText() == "Custom")
        {
            QPixmap plusImg (":/icon/icons_on/plus.png");
            ui->plusLabel->setPixmap(plusImg);
        }
    }
}


// --------------------------------------------------- EAR AND CES CONNECTION CHECKS -----------------------------------------

// if the ear clips or CES Output is disconnected, change connection level
void MainWindow::leftEarConnection()
{
    if (powerOn == true && menuPower == true && ces == true)
    {
        if (ui->leftEarClip->currentText() == "False")
        {
            QPixmap lImg2 (":/icon/icons_off/justL_Icon_off.png");
            ui->leftLabel->setPixmap(lImg2);

            ui->connectionLevelAdminComboBox->setCurrentText("Bad Connection");
        }

        else if (ui->leftEarClip->currentText() == "True")
        {
            QPixmap lImg2 (":/icon/icons_on/justL_Icon.png");
            ui->leftLabel->setPixmap(lImg2);
        }
    }
    else if (ces == false || powerOn == false || menuPower == false)
    {
        // update admin panel on the disconnect of the left ear connection
        ui->connectionLevelAdminComboBox->setCurrentText("Bad Connection");
        ui->leftEarClip->setCurrentText("False");

        QPixmap lImg2 (":/icon/icons_off/justL_Icon_off.png");
        ui->leftLabel->setPixmap(lImg2);
    }
}

void MainWindow::rightEarConnection()
{
    if (powerOn == true && menuPower == true && ces == true )
    {
        if (ui->rightEarClip->currentText() == "False")
        {
            QPixmap rImg2 (":/icon/icons_off/justR_Icon_off.png");
            ui->rightLabel->setPixmap(rImg2);

            // set the connection to poor if the user removes the ear clips
            ui->connectionLevelAdminComboBox->setCurrentText("Bad Connection");
        }

        else if (ui->rightEarClip->currentText() == "True")
        {
            QPixmap rImg2 (":/icon/icons_on/justR_Icon.png");
            ui->rightLabel->setPixmap(rImg2);
        }
    }

    else if (ces == false || powerOn == false || menuPower == false)
    {
        // update admin panel on the disconnect of the right ear connection
        ui->connectionLevelAdminComboBox->setCurrentText("Bad Connection");
        ui->rightEarClip->setCurrentText("False");

        QPixmap rImg2 (":/icon/icons_off/justR_Icon_off.png");
        ui->rightLabel->setPixmap(rImg2);
    }
}

void MainWindow::cesConnection()
{


    if (ui->cesComboBox->currentText() == "True" && powerOn == true)
    {
        ces = true;

        QPixmap cesOn (":/icon/icons_on/heart_on.png");
        ui->cesLabel->setPixmap(cesOn);
    }

    else
    {
        ui->cesComboBox->setCurrentText("False");
        ces = false;

        QPixmap cesOff (":/icon/icons_off/heart_off.png");
        ui->cesLabel->setPixmap(cesOff);
    }

    leftEarConnection();
    rightEarConnection();
}

// cycle between sessions
void MainWindow::cycleSessions()
{

    if (cycleSession == true)
    {
        turnOffSessionMenu();

        if (ui->sessionComboBox->currentText() == "MET")
        {
            QPixmap met (":/icon/icons_on/metIcon.png");
            ui->metLabel->setPixmap(met);
            aboveLOnROff();
        }

        else if (ui->sessionComboBox->currentText() == "Sub Delta")
        {
            QPixmap subD (":/icon/icons_on/subDelta.png");
            ui->subDeltaLabel->setPixmap(subD);
            QPixmap aboveLImg (":/icon/icons_off/aboveL_Icon_off.png");
            ui->aboveLeftLabel->setPixmap(aboveLImg);
            QPixmap aboveRImg (":/icon/icons_on/aboveR_Icon.png");
            ui->aboveRightLabel->setPixmap(aboveRImg);
        }

        else if (ui->sessionComboBox->currentText() == "Delta")
        {
            QPixmap delta (":/icon/icons_on/delta.png");
            ui->deltaLabel->setPixmap(delta);
            aboveLOnROff();
        }

        else if (ui->sessionComboBox->currentText() == "Theta")
        {
            QPixmap theta (":/icon/icons_on/theta.png");
            ui->thetaLabel->setPixmap(theta);
            aboveLOnROff();
        }

        else if (ui->sessionComboBox->currentText() == "Alpha")
        {
            QPixmap alpha (":/icon/icons_on/alpha.png");
            ui->alphaLabel->setPixmap(alpha);
            aboveLOnROff();
        }

        else if (ui->sessionComboBox->currentText() == "Beta 1")
        {
            QPixmap beta1 (":/icon/icons_on/beta1.png");
            ui->betaOneLabel->setPixmap(beta1);
        }

        else if (ui->sessionComboBox->currentText() == "Beta 2")
        {
            QPixmap beta2 (":/icon/icons_on/beta2.png");
            ui->betaTwoLabel->setPixmap(beta2);
            aboveLOnROff();
        }

        else if (ui->sessionComboBox->currentText() == "100Hz")
        {
            QPixmap hundred (":/icon/icons_on/100hz.png");
            ui->hundredabel->setPixmap(hundred);
            aboveLOnROff();
        }
    }

}

// --------------------------------------- SOFT OFF ---------------------
void MainWindow::softOff()
{
    if (softOffBool == true && batteryDead == false && ui->rightEarClip->currentText() == "True" && ui->leftEarClip->currentText() == "True")
    {

        QString str = ui->console->toPlainText();

        str += "\n\n Initiating Soft Off mode.\n";

        // calls the helper every two seconds
        QTimer * timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(softOffHelper()));
        timer->start(2000);

        ui->console->setText(str);
    }

}


// recording and db function

void MainWindow::Recording(int e)
{
    QString str = ui->console->toPlainText();


    if (ui->recordBox->currentText() == "True" && batteryDead == false && powerOn == true )
    {
        database.addSession(ui->timeAdminComboBox->currentText(), ui->sessionComboBox->currentText(), e);

        QStringList ls = database.getLastSession();

        ui->historyComboBox->addItems({ls.at(0) + ", " + ls.at(1) + ", Intensity: " + ls.at(2)});
        recording = true;

        str += "\n Recording Session.\n";

        ui->console->setText(str);
    }

    else if (ui->recordBox->currentText() == "False")
    {
        QString str = ui->console->toPlainText();

        str += "\n Not Recording Session.\n";

        ui->console->setText(str);
    }
}

// decreases intensitiy
void MainWindow::softOffHelper()
{

    QString str = ui->console->toPlainText();

    if (totalIntesity -1 >= 1 && softOffBool == true && batteryDead == false && ui->rightEarClip->currentText() == "True" && ui->leftEarClip->currentText() == "True")
    {
        totalIntesity -= 1;

        QString s2 = QString::number(totalIntesity);

        if (isBlinking == false)
        {
            QPixmap connection_bar (":/progress/progress/progress"+s2+".png");
            ui->connectionLevelLabel->setPixmap(connection_bar);
        }
    }

    else if (totalIntesity == 1 && softOffBool == true && batteryDead == false && ui->rightEarClip->currentText() == "True" && ui->leftEarClip->currentText() == "True")
    {
        Recording(initalIntensity);

        str += "\nPowering System Off!\n";

        turnOff();
        softOffBool = false;
        totalIntesity = 0;

        ui->console->setText(str);
    }

}

void MainWindow::selectIntesity(){
    setIntesity = true;
    if(confirm == true && powerOn == true && menuPower == true){
        QString s = ui->console->toPlainText();
        if(intensityUp == true){
            if(totalIntesity+1 <= 8){
                s += "\n Intesity turned up";
                ui->console->setText(s);
                totalIntesity += 1;
                initalIntensity = totalIntesity;

                QString s2 = QString::number(totalIntesity);
                QPixmap connection_bar (":/progress/progress/progress"+s2+".png");
                ui->connectionLevelLabel->setPixmap(connection_bar);

                // begin tracking time before triggering soft off
                sessionTimeDelay();
            }
            else{
                s += "\n Max Intesity";
                ui->console->setText(s);
            }
            intensityUp = false;
        }
        else if(intensityDown == true && powerOn == true && menuPower == true){
            if(totalIntesity-1 >= 1){
                s+= "\n Intesity turned down";
                ui->console->setText(s);
                totalIntesity -= 1;
                initalIntensity = totalIntesity;

                QString s2 = QString::number(totalIntesity);
                QPixmap connection_bar (":/progress/progress/progress"+s2+".png");
                ui->connectionLevelLabel->setPixmap(connection_bar);
            }
            else{
                s+= "\n Lowest Intesity";
                ui->console->setText(s);
            }
            intensityDown = false;
        }
    }
}


// set history session
void MainWindow::setHistorySession()
{
    if (ui->historyComboBox->count() > 0 && powerOn == true && menuPower == true)
    {
        // split the string into a QLISTSTRING
        QString s2;
        s2 = ui->historyComboBox->currentText().remove(" Intensity:");

        QStringList ls = s2.split(", ");

        // convert string to int
        int intensity = ls.at(2).split(" ")[0].toInt();

        ui->sessionComboBox->setCurrentText(ls.at(1));
        ui->timeAdminComboBox->setCurrentText(ls.at(0));
        totalIntesity = intensity;

        cycleSession = true;
        cycleTime = true;

        cycleSessions();
        cycleSessionTime();
        setIntensityBar();

        cycleSession = false;
        cycleTime = false;

    }
}

//---------------------------------------- BUTTON PRESSES ----------------------------------------

void MainWindow::on_powerPushButton_released()
{
    // compares the time of the mouse button being released to the time it was pressed
    if (releaseTime.msecsTo(QTime::currentTime()) >= 150 && powerOn == false)
    {
        powerOn = true;
        updateUI();

        //check if the CES was connected while device was off
        cesConnection();
    }
    else if (releaseTime.msecsTo(QTime::currentTime()) >= 150 && powerOn == true)
    {
        powerOn = false;
        updateUI();
    }

    // if the user pushes the power button while the system is one, the session and rest of the menu should turn on
    // as per the video specs
    else if (powerOn == true && menuPower == false)
    {
        menuPower = true; // turn on the menu
        updateUI();
    }

    // if the system is full powered on, the power button functions as a menu selector
    else if (powerOn == true && menuPower == true)
    {
        // if the user presses the powerbutton and alreayd in cycling mode, they cyle through the time
        if (cycleTime == true)
        {
            ui->timeAdminComboBox->setCurrentIndex(ui->timeAdminComboBox->currentIndex() + 1);
        }

        cycleTime = true;
        cycleSession = true;
        cycleSessionTime();
        cycleSessions();
    }


}

void MainWindow::on_powerPushButton_pressed()
{
    // track the amount time the user held down the power button
    releaseTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < releaseTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::on_upPushButton_released()
{
    if (cycleSession == true && confirm == false)
    {
        ui->sessionComboBox->setCurrentIndex(ui->sessionComboBox->currentIndex() + 1);
        if(ui->sessionComboBox->currentIndex() > 7){
            ui->sessionComboBox->setCurrentIndex(0);
        }
    }
    else if (confirm == true){
        intensityUp = true;
        intensityDown = false;
        selectIntesity();
    }
}

void MainWindow::on_downPushButton_released()
{
    if (cycleSession == true && confirm == false)
    {
        ui->sessionComboBox->setCurrentIndex(ui->sessionComboBox->currentIndex() - 1);
        if(ui->sessionComboBox->currentIndex() < 0){
            ui->sessionComboBox->setCurrentIndex(7);
        }
    }
    else if (confirm == true){
        intensityDown = true;
        intensityUp = false;

        selectIntesity();
    }
}

void MainWindow::on_confirmPushButton_pressed()
{
    // track the amount time the user held down the power button
    releaseTimeConfirm = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < releaseTime)
    {        // load connection setting after confirming the session
        connectionBarUI();
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    if(cycleSession == true && cycleTime == true){
        ui->console->setText("Selected Session\n");
        confirm = true;
        cycleSession = false;
        cycleTime = false;

        // load the intensity graph

        QString s2 = QString::number(totalIntesity);
        QPixmap connection_bar (":/progress/progress/progress"+s2+".png");
        ui->connectionLevelLabel->setPixmap(connection_bar);
    }
}

void MainWindow::on_confirmPushButton_released()
{
    if (releaseTimeConfirm.secsTo(QTime::currentTime()) >= 1 )
    {
        if (confirmIntesity == false && confirm == true && ui->rightEarClip->currentText() == "True" && ui->leftEarClip->currentText() == "True"){
            //softOffBool = true;


            QString s = ui->console->toPlainText();
            s += "\n Starting Session";
            ui->console->setText(s);
            confirmIntesity = true;

            // load connection setting after confirming the session
            connectionBarUI();

            QTime stop = QTime::currentTime().addSecs(2);

            // load the intensity bar after 1 second
            while(QTime::currentTime() <= stop){
                //stop loop if window is closed
                if (QTime::currentTime() == stop)
                {
                    setIntensityBar();
                    break;
                }

                if(QCoreApplication::closingDown()){
                    break;
                }
                //makes sure to handle other request whike delaying
                QCoreApplication::processEvents(QEventLoop::AllEvents,100);
            }

            QTimer *timer23 = new QTimer(this);
            QObject::connect(timer23, SIGNAL(timeout()), this, SLOT(batteryDecay()));
            timer23->start(2000);

             sessionTimeDelay();
        }
    }

}


void MainWindow::batteryDecay(){

    if (ui->batteryLevelAdminSpinxBox->value() == 0 && batteryDead == false)
    {
        batteryDead = true;
        turnOff();

        QString s = ui->console->toPlainText();
        s += "\n Turned Off No Battery Left";
        ui->console->setText(s);
    }

    else if (batteryDead == false && powerOn == true && menuPower == true && confirm == true && confirmIntesity == true )
    {
        if(ui->batteryLevelAdminSpinxBox->value()-((0.1*totalIntesity) + ui->connectionLevelAdminComboBox->currentIndex()) <= 20 && ui->batteryLevelAdminSpinxBox->value()-((0.1*totalIntesity) + ui->connectionLevelAdminComboBox->currentIndex()) > 10){
            isBlinking = true;
            bat = 2;
            QTimer *timerLevel2 = new QTimer(this);
            QObject::connect(timerLevel2, SIGNAL(timeout()), this, SLOT(batteryLevelOff()));
            timerLevel2->start(400);

        }

        else if(ui->batteryLevelAdminSpinxBox->value()- ((0.1*totalIntesity) + ui->connectionLevelAdminComboBox->currentIndex()) <= 10 && ui->batteryLevelAdminSpinxBox->value() - ((0.1*totalIntesity) + ui->connectionLevelAdminComboBox->currentIndex()) >= 0){
            if (batteryDead == false && powerOn == true && menuPower == true && confirm == true)
            {
                isBlinking = true;
                bat = 1;

                QPixmap connection_bar (":/progress/progress/progress1.png");
                ui->connectionLevelLabel->setPixmap(connection_bar);

                QTimer *timerLevel1 = new QTimer(this);
                QObject::connect(timerLevel1, SIGNAL(timeout()), this, SLOT(batteryLevelOff()));
                timerLevel1->start(200);
            }
        }

        ui->batteryLevelAdminSpinxBox->setValue(ui->batteryLevelAdminSpinxBox->value() - ((0.1*totalIntesity) + (ui->connectionLevelAdminComboBox->currentIndex()) * 0.5));
        isBlinking = false;
    }
}


void MainWindow::batteryBlinking(){
    if(bat == 2 && batteryDead == false){
        QPixmap connection_bar (":/progress/progress/progress2.png");
        ui->connectionLevelLabel->setPixmap(connection_bar);
    }
    if(bat == 1 && batteryDead == false){
        QPixmap connection_bar (":/progress/progress/progress1.png");
        ui->connectionLevelLabel->setPixmap(connection_bar);
    }
    if(ui->batteryLevelAdminSpinxBox->value() == 0 && batteryDead == false){
            QString s = ui->console->toPlainText();
            s += "\n Turned Off No Battery Left";
            ui->console->setText(s);
            batteryDead = true;
            turnOff();
    }
}

// BATTERY ICON OVERRIDE FUNCTION
void MainWindow::batteryLevelOff()
{
    if (batteryDead == false && confirm == true)
    {
        QTimer *timer2 = new QTimer(this);
        QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(batteryBlinking()));
        timer2->start(250);

        QPixmap connectionBar (":/progress/progress/progress0.png");
        ui->connectionLevelLabel->setPixmap(connectionBar);
    }
}



void MainWindow::sessionTimeDelay(){
    QString time = ui->timeAdminComboBox->currentText();
    QTime stop;

    //create a delay depending on the the selected time length and if confirm is true
    if(time == "20" && confirm == true){
        stop = QTime::currentTime().addSecs(10);


        while(QTime::currentTime() <= stop){


            if (QTime::currentTime() == stop)
            {
                softOffBool = true;
                softOff();
                break;
            }

            //stop loop if window is closed
            if(QCoreApplication::closingDown()){
                break;
            }
            //makes sure to handle other request whike delaying
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }
    else if(time == "40" && confirm == true){
        stop = QTime::currentTime().addSecs(20);

        while(QTime::currentTime() <= stop){
            //stop loop if window is closed
            if (QTime::currentTime() == stop)
            {
                 softOffBool = true;

                softOff();
                break;
            }

            if(QCoreApplication::closingDown()){
                break;
            }
            //makes sure to handle other request whike delaying
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }
    else if(time == "180" && confirm == true){
        stop = QTime::currentTime().addSecs(40);

        while(QTime::currentTime() <= stop){

            if (QTime::currentTime() == stop)
            {
                softOffBool = true;
                softOff();
                break;
            }

            //stop loop if window is closed
            if(QCoreApplication::closingDown()){
                softOff();
                break;
            }
            //makes sure to handle other request whike delaying
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }
    return;
}

