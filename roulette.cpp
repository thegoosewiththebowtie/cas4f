#include "roulette.h"
#include "ui_roulette.h"
 #include <QPainter>
#include <qsettings.h>
#include <qtconcurrentrun.h>
#include <QTime>
#include <ctime>
Roulette::Roulette(QWidget *parent, QLabel* BLNS)
    : QWidget(parent)
    , ui(new Ui::Roulette)
{
    ui->setupUi(this);
    BLNS2 = BLNS;
    for (int i = 0; i < 38; ++i){
        QString name = "lbl"+QString::number(i);
        QLabel* templbl = this->findChild<QLabel*>(name);
        ui->betRouSlot->addItem(templbl->text());
    }
    resizeEvent(nullptr);
}
void delay3(int i)
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
int num2id(int numrun[38], int number){
    for (int var = 0; var < 39; ++var) {
        if (numrun[var] == number){
            return var;
        }
    }
    return -1;
}
void Roulette::resizeEvent(QResizeEvent* event){
    int uh = this->ui->rouGrid->geometry().height()/11;
    int wh = this->ui->rouGrid->geometry().width()/11;;
    int ih = this->ui->subGrid->geometry().height()/12;
    int iw = this->ui->subGrid->geometry().width()/16;
    for (int i = 0; i < 38; ++i){
        QString name = "lbl"+QString::number(i);
        QLabel* templbl = this->findChild<QLabel*>(name);
        QPushButton* tempbtn = this ->findChild<QPushButton*>("pushButton_"+QString::number(i));
        if(templbl!=NULL){
            templbl->setMinimumHeight(wh/2);templbl->setMaximumHeight(wh/2);
            templbl->setMaximumWidth(wh); templbl->setMinimumWidth(wh);
            ui->pbr->setMinimumHeight(wh/2);ui->pbr->setMaximumHeight(wh/2);
            ui->pbr->setMaximumWidth(wh); ui->pbr->setMinimumWidth(wh);
            ui->pbr2->setMinimumHeight(wh/2);ui->pbr2->setMaximumHeight(wh/2);
            ui->pbr2->setMaximumWidth(wh); ui->pbr2->setMinimumWidth(wh);
            templbl->setStyleSheet("font: "+ QString::number(uh/3) +"pt;");
        }
        if(tempbtn){
            int d = 1;
            int p = 0;
            if(i>=4 && i<=8){
                d = 3;
                p  = 18;
            } else if(i>=9&&i<=16){
                d = 2;
            }
            tempbtn->setMaximumHeight(iw/2); tempbtn->setMinimumHeight(iw/2);
            tempbtn->setMaximumWidth(iw*d+p); tempbtn->setMinimumWidth(iw*d+p);
            tempbtn->setStyleSheet("font: "+ QString::number(ih/3) +"pt;");
        }
        QLabel* templbl2 = this->findChild<QLabel*>(name+"_2");
        if(templbl2!=NULL){
            int d = 1;
            int p =0;
            if(i == 0||i==19){
                d = 3;
                p =18;
            }
            templbl2->setMaximumHeight(iw/2); templbl2->setMinimumHeight(iw/2);
            templbl2->setMaximumWidth(iw*d+p); templbl2->setMinimumWidth(iw*d+p);
            templbl2->setStyleSheet("font: "+ QString::number(ih/3) +"pt;");
        }
    }
    on_betRouSlot_currentIndexChanged(ui->betRouSlot->currentIndex());
    ui->winlbl->setMinimumWidth(ui->rouGrid->geometry().width()/3);
    ui->winlbl->setMaximumWidth(ui->rouGrid->geometry().width()/3);
    ui->winlbl->setStyleSheet("font: "+ QString::number(iw/3) +"pt;");
    if(!ui->SpinCommand->isEnabled()){
    for (Bet bn : bets) {
        for(int f : bn.nums){
            if(int n; (n = num2id(numrun, f))!= -1){LightUp("lbl"+QString::number(n)+"_2");}
        }
    }}
}

Roulette::~Roulette()
{
    delete ui;
}

void Roulette::on_selAnte_valueChanged(int value)
{
    char str[3];
    sprintf(str, "%03d", value);

    ui->disAnte->setText(str);
}


void Roulette::LightUpDown(QString name, int spinspeed, bool last){
    QPalette lu;
    QPalette lu2;
    QLabel* templ = this->findChild<QLabel*>(name);
    lu = templ->palette();
    lu2 = lu;
    lu.setColor(QPalette::Window, QColorConstants::Svg::orange);
    templ->setPalette(lu);
    delay3(1500/spinspeed);
    lu2.setColor(QPalette::Window, QColorConstants::Black);
    if(!last){
        templ->setPalette(lu2);
    } else {
        for (int var = 0; var < 3; ++var) {
            templ->setPalette(lu);
            delay3(300/spinspeed);
            templ->setPalette(lu2);
            delay3(300/spinspeed);
        }
        templ->setPalette(lu);
    }
}

int Roulette::DefaultSpin(){
    srand (time (0));
    int jumpnum = rand()%100;
    int spinnum = rand()%15;
    int initspinspeed = rand()%100+50;
    int nextid;
    bool last = false;
    for (int i = 0; i < jumpnum; ++i) {
        nextid = rand()%37;
        LightUpDown("lbl"+QString::number(nextid), initspinspeed, last);
    }
    for (int var = 0; var < spinnum; ++var) {
        for (; nextid <= 38; ++nextid) {
            if(nextid ==38){
                nextid = 0;
            }
            if(nextid ==19){
                nextid = 20;
            }
            if(initspinspeed==1){
                last = true;
                LightUpDown("lbl"+QString::number(nextid), 5, last);
                break;
            } else if(rand()%5==1||initspinspeed<15){
                initspinspeed--;
            }
            LightUpDown("lbl"+QString::number(nextid), initspinspeed, last);
        }
        if(initspinspeed==1){
            break;
        }
    }
    ui->SelRouSlot->setText(this->findChild<QLabel*>("lbl"+QString::number(nextid))->text());
    return nextid;
}

void Roulette::Win(QFuture<int> spinres, std::vector<Bet> sortedbets){
    spinres.waitForFinished();
    int winnumid = spinres.result();
    int winnings = 0;
    std::vector<Bet> wonbets;
    for (Bet bet : sortedbets) {
        for (int num : bet.nums) {
            if(num2id(numrun, num) == winnumid){
                wonbets.push_back(bet);
            }
        }
    }
    if(wonbets.empty()){
        ui->winlbl->setText("");
        delay3(500);
        for (int var = 0; var < 3; ++var) {
            ui->winlbl->setText("~~ You  lost ~~");
            delay3(500);
            ui->winlbl->setText("");
            delay3(500);
        }
        ui->winlbl->setText("~~~ Spin it ~~~");
    } else {
        ui->winlbl->setText("");
        delay3(500);
        for (Bet wb : wonbets) {
            double mult = 36/wb.nums.size();
            winnings+=wb.amount*mult;
        }
        ui->winlbl->setText("");
        delay3(500);
        for (int var = 0; var < 3; ++var) {
            ui->winlbl->setText("You won ▲"+ QString::number(winnings));
            delay3(500);
            ui->winlbl->setText("");
            delay3(500);
        }
        ui->winlbl->setText("~~~ Spin it ~~~");
        QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
        settings.setValue("Balance", settings.value("Balance").toInt()+winnings);
        BLNS2->setText(settings.value("Balance").toString());
    }
    ui->SpinCommand->setEnabled(true);
    ui->selAnte->setEnabled(true);
    ui->betSelRouSlot->setEnabled(true);
    ui->betRouSlot->setEnabled(true);
    ui->selRouSlot->setEnabled(true);
}

void Roulette::on_SpinCommand_clicked(){
    if(ui->betSelRouSlot->count() <1){
    for (int var = 0; var < 3; ++var) {
        ui->winlbl->setText("~~~ No bets ~~~");
        delay3(500);
        ui->winlbl->setText("");
        delay3(500);
        }
    ui->winlbl->setText("~~~ Spin it ~~~");
    return;
    }
    ui->winlbl->setText("~ Spinning ~");
    for (int var = 0; var <= 16; ++var) {
        if (var == 1){continue;}
        QPushButton* tempbtn = this ->findChild<QPushButton*>("pushButton_"+QString::number(var));
        tempbtn->setChecked(false);
    }
    std::vector<Bet> sortedbets;
    int minnum = 0;
    for (Bet bn : bets) {
        minnum+=bn.amount;
        for(int f : bn.nums){
            if(int n; (n = num2id(numrun, f))!= -1){LightUp("lbl"+QString::number(n)+"_2");}
        }
    }
    sortedbets = bets;
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    if(settings.value("Balance").toInt()<minnum){
        ui->winlbl->setText("");
        delay3(500);
        for (int var = 0; var < 3; ++var) {
            ui->winlbl->setText("~~ No  money ~~");
            delay3(500);
            ui->winlbl->setText("");
            delay3(500);
        }
        ui->winlbl->setText("~~~ Spin it ~~~");
        return;
    }
    settings.setValue("Balance", settings.value("Balance").toInt() - minnum);
    BLNS2->setText(settings.value("Balance").toString());
    ui->SpinCommand->setEnabled(false);
    ui->selAnte->setEnabled(false);
    ui->betSelRouSlot->setEnabled(false);
    ui->betRouSlot->setEnabled(false);
    ui->selRouSlot->setEnabled(false);
    QFuture<int> spinres = QtConcurrent::run(&Roulette::DefaultSpin, this);
    QtConcurrent::run(&Roulette::Win, this, spinres, sortedbets);
}



void Roulette::LightUp(QString name){
    QPalette lu;
    QLabel* templ = this->findChild<QLabel*>(name);
    lu = templ->palette();
    lu.setColor(QPalette::Window, QColorConstants::Svg::darkgreen);
    templ->setPalette(lu);
}
void Roulette::LightDown(QString name){
    QPalette lu;
    QLabel* templ = this->findChild<QLabel*>(name);
    lu = templ->palette();
    lu.setColor(QPalette::Window, QColorConstants::Svg::black);
    templ->setPalette(lu);
}


void Roulette::on_pushButton_4_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(1):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_7_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(2):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_2_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(12):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_0_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(13):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_3_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(14):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_5_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(3):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_6_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(4):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_8_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(5):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_9_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(7):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_10_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(8):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_11_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(9):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_12_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(10):ui->betRouSlot->setCurrentIndex(0);
}


void Roulette::on_pushButton_13_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(16):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_15_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(17):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_14_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(18):ui->betRouSlot->setCurrentIndex(0);

}


void Roulette::on_pushButton_16_toggled(bool checked)
{
    if(ic){return;}
    checked?ui->betRouSlot->setCurrentIndex(19):ui->betRouSlot->setCurrentIndex(0);

}





void Roulette::on_selRouSlot_clicked()
{
    int i = ui->betRouSlot->currentIndex();
    if(i == 0 || i ==6|| i==11 || i==15){
        return;
    }
    ui->betSelRouSlot->addItem(ui->betRouSlot->itemText(i));
    Bet addthisbet;
    addthisbet.amount = ui->selAnte->value();
    addthisbet.betname = ui->selRouSlot->text();
    addthisbet.nums = numsrn;
    bets.push_back(addthisbet);
}



void Roulette::on_betRouSlot_currentIndexChanged(int index)
{
    ic = true;
    numsrn.clear();
    for (int var = 0; var <= 37; ++var) {
        LightDown("lbl"+QString::number(var)+"_2");
    }
    for (int var = 0; var <= 16; ++var) {
        if (var == 1){continue;}
        QPushButton* tempbtn = this ->findChild<QPushButton*>("pushButton_"+QString::number(var));
        tempbtn->setChecked(false);
    }

    //remove
    //endremove
    switch (index) {
    case 0:
        break;
    case 1:
        ui->pushButton_4->setChecked(true);
        for (int var = 1; var <= 12; ++var){if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 2:
        ui->pushButton_7->setChecked(true);
        for (int var = 1; var <= 18; ++var){if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 3:
        ui->pushButton_5->setChecked(true);
        for (int var = 13; var <= 24; ++var){if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 4:
        ui->pushButton_6->setChecked(true);
        for (int var = 25; var <= 36; ++var){if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 5:
        ui->pushButton_8->setChecked(true);
        for (int var = 19; var <= 36; ++var){if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;



    case 6:
        break;



    case 7:
        ui->pushButton_9->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
            if (var%2 == 0){
        if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        }
        break;
    case 8:
        ui->pushButton_10->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
        if(int n; (n = num2id(redrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 9:
        ui->pushButton_11->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
        if(int n; (n = num2id(blackrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        break;
    case 10:
        ui->pushButton_12->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
            if (var%2 == 1){
        if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        }
        break;

    case 11:
        break;

    case 12:
        ui->pushButton_2->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
            if (var%3 == 1){
        if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        }
        break;
    case 13:
        ui->pushButton_0->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
            if (var%3 == 2){
        if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        }
        break;
    case 14:
        ui->pushButton_3->setChecked(true);
        for (int var = 1; var <= 36; ++var) {
            if (var%3 == 0){
        if(int n; (n = num2id(numrun, var)) != -1){LightUp("lbl"+QString::number(n)+"_2");numsrn.push_back(var);}}
        }
        break;

    case 15:
        break;
/*(27->33)
 (17->6, 1->9)
(19->25, 22->28)
(15->12)*/
        /*The numbers run -
         * 0-2
         * 0, 32, 15,
         * 3-7
         * 19, 4, 21, 2, 25,
         * 8-10
         * 17, 34, 6,
         * 11-23 !19
         * 27, 13, 36, 11, 30, 8, 23, 10, 0, 5, 24, 16, 33,
         * 24-28
         * 1, 20, 14, 31, 9,
         * 29-33
         *  22, 18, 29, 7, 28,
         *  34-37
         *  12, 35, 3 and 26.*/
    case 16:
        ui->pushButton_13->setChecked(true);
        for (int var = 11; var <= 23; ++var) {
            if(var==19){continue;}
            LightUp("lbl"+QString::number(var)+"_2");
        }
        break;

    case 17:
        ui->pushButton_15->setChecked(true);
        for (int var = 24; var <= 28; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }
        for (int var = 8; var <= 10; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }
        break;
    case 18:
        ui->pushButton_14->setChecked(true);
        for (int var = 29; var <= 33; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }
        for (int var = 3; var <= 7; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }
        break;

    case 19:
        ui->pushButton_16->setChecked(true);
        for (int var = 34; var <= 37; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }        for (int var = 0; var <= 2; ++var) {
            LightUp("lbl"+QString::number(var)+"_2");
        }
        break;

    default:
        QString selnumrn = ui->betRouSlot->itemText(index).removeAt(0);
        int selnumrnint = selnumrn.split(" ")[0].toInt();
        if(int n; (n = num2id(numrun, selnumrnint))!= -1){LightUp("lbl"+QString::number(n)+"_2"); numsrn.push_back(selnumrnint);}
        break;
    }
    ic = false;
}


void Roulette::on_pushButton_clicked()
{
    if(bets.empty()){return;}
    int i = ui->betSelRouSlot->currentIndex();
    ui->betSelRouSlot->removeItem(i);
    bets.erase(bets.begin()+i);
}

