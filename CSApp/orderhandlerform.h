#ifndef ORDERHANDLERFORM_H
#define ORDERHANDLERFORM_H

#include <QWidget>
#include "clientinformaiton.h"
#include "productinformaiton.h"

namespace Ui {
class OrderHandlerForm;
}
class OrderInformaiton;

class OrderHandlerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderHandlerForm(QWidget *parent = nullptr);
    ~OrderHandlerForm();

public slots:
    void clientAdded(int);
    void productAdded(int);

private slots:
    void on_enrollPushButton_clicked();

signals:
    void orderAdded();

private:
    Ui::OrderHandlerForm *Oui;
    QMap<int, OrderInformaiton*> orderInfo;
    int makeoid();
};

#endif // ORDERHANDLERFORM_H
