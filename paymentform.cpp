#include "paymentform.h"
#include "ui_paymentform.h"
#include <QSettings>
#include <QTime>
#include <ctime>
void delay(int i)
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
PaymentForm::PaymentForm(QWidget *parent, QLabel* BLNS)
    : QWidget(parent)
    , ui(new Ui::PaymentForm)
{
    ui->setupUi(this);
    BLNS2 = BLNS;
}

PaymentForm::~PaymentForm()
{
    delete ui;
}

void PaymentForm::on_commandLinkButton_clicked()
{
    srand (time (0));
    int MCID = ui->lineEdit->text().toInt();
    QString SCv2 = ui->lineEdit->text();
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("MCID", MCID);
    settings.setValue("SCv2", SCv2);
    settings.setValue("Balance", ui->radioButton_2->isChecked()? settings.value("Balance").toInt()+ui->spinBox->value() : settings.value("Balance").toInt()-ui->spinBox->value());
    ui->progressBar->setMaximum(100);
    for (int var = 0; var <= 100; ++var) {
        delay(rand()%100+100);
        ui->progressBar->setValue(var);
    }
    BLNS2->setText(settings.value("Balance").toString());
}

