#ifndef SLOTS_H
#define SLOTS_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Slots;
}

class Slots : public QWidget
{
    Q_OBJECT

public:
    explicit Slots(QWidget *parent = nullptr, QLabel* BLNS = new QLabel);

    int globali1 = 5;
    int globali2 = 5;
    int globali3 = 5;
    int ante;
    int win = 0;
    double globalspeed1 = 4;
    double globalspeed2 = 4;
    double globalspeed3 = 4;
    bool brsp1 = false;
    bool brsp2 = false;
    bool brsp3 = false;
    bool fs = false;
    void SlowSpin1();
    void SlowSpin2();
    void SlowSpin3();
    void Win();
    int l = 0;
    void resizeEvent(QResizeEvent* event);
    QWidget *parent2;
    QLabel* BLNS2;
    ~Slots();

private slots:
    void on_Spin_clicked();

    void on_Stop1_clicked();

    void on_Stop2_clicked();

    void on_Stop3_clicked();

    void on_pushButton_2_clicked();

    void on_Take_clicked();

    void on_Keep1_toggled(bool checked);

    void on_Keep3_toggled(bool checked);

    void on_Keep2_toggled(bool checked);

private:
    Ui::Slots *ui;

    const QString symbols[30] {"X  ", "≡≡≡", "▲", "≡≡≡", "  X", "XXX", "X  ","x2 ","x3 ", "x4 ",  "???", "888", " /1",  " /2", " /2", " /2", " /3", " /3", " /3", " x3", " x3", " x3", " x2", " x2", " x2", " x1", " x1", " x1", " XX", "XXX"};
};

#endif // SLOTS_H
