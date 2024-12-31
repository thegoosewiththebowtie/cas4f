#ifndef ROULETTE_H
#define ROULETTE_H
#include <QFuture>
#include <QWidget>
#include <qlabel.h>
#include<vector>

class Bet{
public:
    int amount;
    QString betname;
    std::vector<int> nums;
};
namespace Ui
{
class Roulette;
}

class Roulette : public QWidget
{
    Q_OBJECT

public:
    explicit Roulette(QWidget *parent = nullptr, QLabel* BLNS = new QLabel);
    void resizeEvent(QResizeEvent* event);
    void LightUpDown(QString name, int spinspeed, bool last);
    void LightUp(QString name);
    void LightDown(QString name);
    bool freedomRoulette = false;
    int DefaultSpin();
    int selSlotRN = 0;
    QLabel* BLNS2;
    void Win(QFuture<int> spinres, std::vector<Bet> sortedbets);
    int numrun[38]{0,32,15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 0, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26};
    int redrun[38]{-1, 32, -1, 19, -1, 21, -1, 25, -1, 34, -1, 27, -1, 36, -1, 30, -1, 23, -1, -1, 5, -1, 16, -1, 1, -1, 14, -1, 9, -1, 18, -1, 7, -1, 12, -1, 3, -1};
    int blackrun[38]{-1, -1, 15, -1, 4, -1, 2, -1, 17, -1, 6, -1, 13, -1, 11, -1, 8, -1, 10, -1, -1, 24, -1, 33, -1, 20, -1, 31, -1, 22, -1, 29, -1, 28, -1, 35, -1, 26};
    std::vector<Bet> bets;
    std::vector<int> numsrn;
    bool ic = false;
    ~Roulette();
private slots:
    void on_SpinCommand_clicked();
    void on_pushButton_4_toggled(bool checked);

    void on_pushButton_7_toggled(bool checked);

    void on_pushButton_2_toggled(bool checked);

    void on_pushButton_0_toggled(bool checked);

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_5_toggled(bool checked);

    void on_pushButton_6_toggled(bool checked);

    void on_pushButton_8_toggled(bool checked);

    void on_pushButton_9_toggled(bool checked);

    void on_pushButton_10_toggled(bool checked);

    void on_pushButton_11_toggled(bool checked);

    void on_pushButton_12_toggled(bool checked);

    void on_pushButton_13_toggled(bool checked);

    void on_pushButton_15_toggled(bool checked);

    void on_pushButton_14_toggled(bool checked);

    void on_pushButton_16_toggled(bool checked);

    void on_selAnte_valueChanged(int value);

    void on_selRouSlot_clicked();

    void on_betRouSlot_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::Roulette *ui;
};

#endif // ROULETTE_H
