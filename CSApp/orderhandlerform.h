#ifndef ORDERHANDLERFORM_H
#define ORDERHANDLERFORM_H

#include <QWidget>

namespace Ui {
class OrderHandlerForm;
}
class OrderInformaiton;
class QTableWidgetItem;
class QComboBox;
class OrderHandlerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderHandlerForm(QWidget *parent = nullptr);
    ~OrderHandlerForm();
    void dataload();
    int cnt = 0;

public slots:
    void clientAdded();
    void productAdded();
    void clientRemoved(int);
    void productRemoved(int);
    void clientModified(int);
    void productModified(int);

private slots:
    void on_enrollPushButton_clicked();
    void orderReturnClient(QList<QString>);
    void orderReturnProduct(QList<QString>);

    void on_tableWidget5_itemClicked(QTableWidgetItem *item);

signals:
    void orderAddedClient(int);
    void orderAddedProduct(int);
    void clientComboBox(QComboBox*, QComboBox*);
    void productComboBox(QComboBox*, QComboBox*);

private:
    Ui::OrderHandlerForm *Oui;
    QMap<int, OrderInformaiton*> orderInfo;
    int makeoid();
};

#endif // ORDERHANDLERFORM_H
