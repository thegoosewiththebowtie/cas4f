#include "mainwindow.h"
#include "about.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    slotswindow = new Slots(ui->centralwidget, BalanceLabel);
    roulettewindow = new Roulette(ui->centralwidget, BalanceLabel);
    paymentformwindow = new PaymentForm(ui->centralwidget, BalanceLabel);
    paymentformwindow->hide();
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    QActionGroup* modeswitchers = new QActionGroup(this);
    modeswitchers->setExclusive(true);
    modeswitchers->addAction(ui->actionToTWAlwaysWins);
    modeswitchers->addAction(ui->actionFairRandom);
    modeswitchers->addAction(ui->actionUserHasAnAdvantage);
    switch (settings.value("Mode").toInt()) {
    case 1:
        ui->actionUserHasAnAdvantage->setChecked(true);
        break;
    case 2:
        ui->actionFairRandom->setChecked(true);
        break;
    case 3:
        ui->actionToTWAlwaysWins->setChecked(true);
        break;
    }
    QActionGroup* gameswitchers = new QActionGroup(this);
    gameswitchers->addAction(ui->actionSlots);
    gameswitchers->addAction(ui->actionRoulett);
    modeswitchers->setExclusive(true);
    switch (settings.value("Game").toInt()) {
    case 1:
        ui->actionSlots->setChecked(true);
        break;
    case 2:
        ui->actionRoulett->setChecked(true);
        break;
    }
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(QuitAction()));
    connect(ui->actionToTWAlwaysWins, SIGNAL(triggered(bool)), this, SLOT(HardAction()));
    connect(ui->actionFairRandom, SIGNAL(triggered(bool)), this, SLOT(NormalAction()));
    connect(ui->actionUserHasAnAdvantage, SIGNAL(triggered(bool)), this, SLOT(EasyAction()));
    connect(ui->actionRoulett, SIGNAL(triggered(bool)), this, SLOT(RouletteAction()));
    connect(ui->actionSlots, SIGNAL(triggered(bool)), this, SLOT(SlotsAction()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(AboutAction()));
    QLabel* txt1 = new QLabel();
    txt1->setText("Balance: ▲");
    BalanceLabel->setText(settings.value("Balance").toString());
    AddBalanceButton->setText("Add");
    connect(AddBalanceButton, SIGNAL(clicked(bool)), this, SLOT(AddMoneyAction()));
    statusBar()->addPermanentWidget(txt1);
    statusBar()->addPermanentWidget(BalanceLabel);
    statusBar()->addPermanentWidget(AddBalanceButton);
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    paymentformwindow->setGeometry(ui->cwc->geometry());
    roulettewindow->setGeometry(ui->cwc->geometry());
    slotswindow->setGeometry(ui->cwc->geometry());
}
void MainWindow::QuitAction(){
    this->close();
}
void MainWindow::HardAction(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Mode", 3);
}
void MainWindow::NormalAction(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Mode", 2);
}
void MainWindow::EasyAction(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Mode", 1);
}
void MainWindow::SlotsAction(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Game", 1);
    OpenGame();
}
void MainWindow::RouletteAction(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    settings.setValue("Game", 2);
    OpenGame();
}
void MainWindow::AboutAction(){
    About aboutwindow;
    aboutwindow.show();
}
/*void MainWindow::HideAll(){
    for(QObject *qo :ui->centralwidget->children()){
        qo -> hide();
    }
}*/
void MainWindow::AddMoneyAction(){
    if (!paymentformwindow->isVisible()){
        paymentformwindow -> show();
        roulettewindow->hide();
        slotswindow->hide();
        AddBalanceButton->setText("Back");
    } else {
        paymentformwindow -> hide();
        OpenGame();
        AddBalanceButton->setText("Add");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::OpenGame(){
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    int game = settings.value("Game").toInt();
    switch (game) {
    case 1:
        slotswindow->show();
        roulettewindow->hide();
        break;
    case 2:
        slotswindow->hide();
        roulettewindow->show();
        break;
    default:
        this->close();
        break;
    }
}

