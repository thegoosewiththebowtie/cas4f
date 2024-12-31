#ifndef PAYMENTFORM_H
#define PAYMENTFORM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class PaymentForm;
}

class PaymentForm : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentForm(QWidget *parent = nullptr, QLabel *BLNS = new QLabel);
    ~PaymentForm();
    QLabel* BLNS2;

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::PaymentForm *ui;
};

#endif // PAYMENTFORM_H
