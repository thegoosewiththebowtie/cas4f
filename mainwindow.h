#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paymentform.h"
#include "roulette.h"
#include "slots.h"
#include <QMainWindow>
#include <QSettings>
#include <QApplication>
#include <QLabel>
#include <qpushbutton.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void OpenGame();
    void resizeEvent(QResizeEvent* event);
    QLabel* BalanceLabel = new QLabel;
    QPushButton* AddBalanceButton = new QPushButton();
    Slots* slotswindow;
    Roulette* roulettewindow;
    PaymentForm* paymentformwindow;

private slots:
    void QuitAction();
    void HardAction();
    void NormalAction();
    void EasyAction();
    void RouletteAction();
    void SlotsAction();
    void AboutAction();
    void AddMoneyAction();
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
