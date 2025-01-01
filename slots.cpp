#include "slots.h"
#include "ui_slots.h"
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QtConcurrent>
#include <ctime>
void delay2(int i)
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
Slots::Slots(QWidget *parent, QLabel* BLNS)
    : QWidget(parent)
    , ui(new Ui::Slots)
{
    ui->setupUi(this);
    BLNS2 = BLNS;
    parent2 = parent;
}
void Slots::resizeEvent(QResizeEvent* event){
    int hsl1 = ui->Sl2->geometry().width();

    ui->L1->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
    ui->L2->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
    ui->L3->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
    ui->Sl1->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
    ui->Sl2->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
    ui->Sl3->setStyleSheet("font: "+ QString::number(hsl1/20) +"pt;");
}
void Slots::SlowSpin1(){
    int i = globali1;
    while(true){
        if (fs) {return;}
        int d = 400/globalspeed1;
        if (i >= 30){
            i=0;
        }
        for (QChar c : symbols[i]) {
            ui->Sl1->setText(ui->Sl1->text().removeAt(0)+c);
            delay2(d);
        }
        if(brsp1){
            brsp1 = false;
            globali1 = i;
            break ;
        }
        int hsl1 = ui->Sl1->geometry().width();
        i++;
        delay2(d);

    }
    if((globalspeed2 <=1||ui->Keep2->isChecked()) && (globalspeed3<=1||ui->Keep3->isChecked())){
        Win();
    }
}
void Slots::SlowSpin2(){
    int i = globali2;
    while(true){
        if (fs) {return;}
        int d = 400/globalspeed2;
        if (i >= 30){
            i=0;
        }
        for (QChar c : symbols[i]) {
            ui->Sl2->setText(ui->Sl2->text().removeAt(0)+c);
          delay2(d);
        }
        int hsl1 = ui->Sl2->geometry().width();

        if(brsp2){
            brsp2 = false;
            globali2 = i;
            break;
        }

        i++;
        delay2(d);


    }
    if((globalspeed1 <=1||ui->Keep1->isChecked()) && (globalspeed3<=1||ui->Keep3->isChecked() )){
        Win();
    }
}
void Slots::SlowSpin3(){
    int i = globali3;
    while(true){
        if (fs) {return;}

        int d = 400/globalspeed3;
        if (i >= 30){
            i=0;
        }
        for (QChar c : symbols[i]) {
            ui->Sl3->setText(ui->Sl3->text().removeAt(0)+c);
            delay2(d);
        }
        delay2(d);
        int hsl1 = ui->Sl3->geometry().width();

        if(brsp3){
            brsp3 = false;
            globali3 = i;
            break;
        }
        i++;
        delay2(d); 
    }
    if((globalspeed2 <=1||ui->Keep2->isChecked()) && (globalspeed1<=1||ui->Keep1->isChecked())){
        Win();
    }
}
Slots::~Slots()
{
    fs = true;
    delete ui;
}
void Slots::Win(){
    int act1 = globali1;
    int act2 = globali2;
    int act3 = globali3;
    int acts[3];
    acts[0]=act1;
    acts[1]=act2;
    acts[2]=act3;
    win = ante;
    bool jpf = false;
    bool FUCK = false;
    int fk = 0;
    bool PREMIUM = false;
    int pr = 0;
    int jp = 1;
    for (int act : acts) {
        switch (act) {
            //0 x
        case 2:
            //4 x
        case 6:
            //5 x
        case 7:
            //6 x
        case 8:
            //28 x
        case 0:
            //29 x
        case 1:
            win = 0;
            break;
            //1 jp
        case 3:
            //2 jp
        case 4:
            //3 jp
        case 5:
            jpf?jp+=2:jpf=true;
            break;
            //9 - x4
        case 11:
            win*=4;
            break;
            //10 - ???
        case 12:
            fk != 2?++fk:FUCK = true;
            break;
            //11 - !!!
        case 13:
            pr != 2?++pr:PREMIUM = true;
            break;
            //13 - /2
            //14 - /2
            //15 - /2
        case 15:
        case 16:
        case 17:
            win /=2;
            break;
            //16 - /3
            //17 - /3
            //18 -/3
        case 18:
        case 19:
        case 20:
            win /=3;
            break;
            // 8 -x3
            // 19 - x3
            // 20 - x3
            // 21 - x3
        case 10:
        case 21:
        case 22:
        case 23:
            win *=3;
            break;
            // 7 -x2
            // 22 - x2
            // 23 - x2
            // 24 - x2
        case 9:
        case 24:
        case 25:
        case 26:
            win *=2;
            break;

            // 12 - /1
            // 25 - x1
            // 26 - x1
            // 27 -x1
            default:
            break;
        }
    }
    win*=tgamma(jp+1);
    ui->Keep1->setEnabled(true);
    ui->Keep2->setEnabled(true);
    ui->Keep3->setEnabled(true);
    if(win == 0 || FUCK || PREMIUM){
        ui->Spin->setEnabled(true);
     if (FUCK||PREMIUM){
        ui->Amount->setEnabled(true);
        ui ->L1->setText("You Win:\rPlease wait");
        ui->L2->setText("A place in a\nfor ToTW SC");
        ui->L3->setText("secret experiment!");
     } else {
         ui->L1->setText("▲0");
         ui->L2->setText("Loser!");
         ui->L3->setText("0▲");
     }
    }else {
        ui->Take->setEnabled(true);
        if (ui->Keep1->isChecked()||ui->Keep2->isChecked()||ui->Keep3->isChecked()){
            ui->Amount->setEnabled(true);
        }
        ui->L1->setText("▲"+QString::number(win));
        if(win>=ante){
            ui->L2->setText("You win!");
        } else {
         ui->L2->setText("You lose!");
        }
        ui->L3->setText(QString::number(win)+"▲");
    }
}
void Slots::on_Spin_clicked()
{
    srand (time (0));
    int f = ui->Keep1->isChecked() + ui->Keep2->isChecked() + ui->Keep3->isChecked();
   int n = pow(2, f);
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Balance", settings.value("Balance").toInt() - ui->Amount->value()+win);
    BLNS2->setText(settings.value("Balance").toString());
    ui->Spin->setEnabled(false);
    ui->Amount->setEnabled(false);
    ui->Take->setEnabled(false);
    ui->Keep1->setEnabled(false);
    ui->Keep2->setEnabled(false);
    ui->Keep3->setEnabled(false);
    ante = ui->Amount->value() / n;
    ui->L1->setText("▲"+QString::number(ante)); ui->L2->setText("Spinning..."); ui->L3->setText(QString::number(ante)+"▲");

    if(!(ui->Keep1->isChecked())){QtConcurrent::run(&Slots::SlowSpin1, this);}
    if(!(ui->Keep2->isChecked())){QtConcurrent::run(&Slots::SlowSpin2, this);}
    if(!(ui->Keep3->isChecked())){QtConcurrent::run(&Slots::SlowSpin3, this);}
    for (int ii = 1; ii < 20; ++ii) {
        globalspeed1 = ii;
        delay2(rand()%500);
        globalspeed2 = ii;
        delay2(rand()%500);
        globalspeed3 = ii;
        delay2(rand()%500);
    }
    if(!(ui->Keep1->isChecked())){ui->Stop1->setEnabled(true);}
    if(!(ui->Keep2->isChecked())){ui->Stop2->setEnabled(true);}
    if(!(ui->Keep3->isChecked())){ui->Stop3->setEnabled(true);}
}


void Slots::on_Stop1_clicked()
{
    ui->Stop1->setEnabled(false);
    for (int ii = globalspeed1; ii > 0; --ii) {
        globalspeed1 = ii;
        delay2(rand()%500);
    }
    brsp1 = true;

}


void Slots::on_Stop2_clicked()
{
    ui->Stop2->setEnabled(false);
    for (int ii = globalspeed2; ii > 0; --ii) {
        globalspeed2 = ii;
        delay2(rand()%500);
    }
    brsp2 = true;

}


void Slots::on_Stop3_clicked()
{
    ui->Stop3->setEnabled(false);
    for (int ii = globalspeed3; ii > 0; --ii) {
        globalspeed3 = ii;
        delay2(rand()%500);

    }
    brsp3 = true;

}


void Slots::on_pushButton_2_clicked()
{

}


void Slots::on_Take_clicked()
{
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Balance", settings.value("Balance").toInt() + win);
    BLNS2->setText(settings.value("Balance").toString());
    win = 0;
    ui->Take->setEnabled(false);
    ui->Keep1->setChecked(false);
    ui->Keep1->setEnabled(false);
    ui->Keep2->setChecked(false);
    ui->Keep2->setEnabled(false);
    ui->Keep3->setChecked(false);
    ui->Keep3->setEnabled(false);
    ui->Spin->setEnabled(true);
    ui->Amount->setEnabled(true);
}


void Slots::on_Keep1_toggled(bool checked)
{
    if (ui->Keep1->isChecked()||ui->Keep2->isChecked()||ui->Keep3->isChecked()){
        ui->Amount->setEnabled(false);
        ui->Take->setEnabled(false);
        ui->Spin->setEnabled(true);
        int n = ui->Keep1->isChecked() + ui->Keep2->isChecked() + ui->Keep3->isChecked();
        if (n<3) {
        n = pow(2, n);
        }else{ ui->Keep3->setChecked(false);}
        ui->Amount->setValue(ante*n);
    } else {
        ui->Amount->setEnabled(true);
        ui->Take->setEnabled(true);
        if(win>0){ui->Spin->setEnabled(false);}
    }
}


void Slots::on_Keep3_toggled(bool checked)
{
    on_Keep1_toggled(checked);
}


void Slots::on_Keep2_toggled(bool checked)
{
    on_Keep1_toggled(checked);
}




