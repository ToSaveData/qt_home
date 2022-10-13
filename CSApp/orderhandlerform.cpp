#include "orderinformaiton.h"
#include "orderhandlerform.h"
//#include "clienthandlerform.h"
//#include "producthandlerform.h"
#include "ui_orderhandlerform.h"
#include <QTableWidgetItem>
#include <QList>
#include <QFile>

OrderHandlerForm::OrderHandlerForm(QWidget *parent) :
    QWidget(parent),
    Oui(new Ui::OrderHandlerForm)
{
    Oui->setupUi(this);

    //    QFile file("orderinfo.txt");
    //    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //        return;

    //    QVector<QTableWidget*> w;
    //    w << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    //    QTextStream in(&file);
    //    while (!in.atEnd()) {
    //        QString line = in.readLine();
    //        QList<QString> row = line.split(", ");
    //        if(row.size())
    //        {
    //            int id = row[0].toInt();
    //            int orderNumber = row[2].toInt();
    //            int cid = row[3].toInt();
    //            int pid = row[4].toInt();
    //            OrderInformaiton* o = new OrderInformaiton(id, row[1], orderNumber, cid, pid);
    //            for(int x = 0; x < 4; x++)
    //            {
    //                w[x]->setRowCount(w[x]->rowCount()+1);
    //                w[x]->setItem(w[x]->rowCount()-1, 0, new QTableWidgetItem(QString::number(id)));
    //                for (int i = 0 ; i < 3; i++)
    //                {
    //                    w[x]->setItem(w[x]->rowCount()-1, i+1, new QTableWidgetItem(row[i+1]));
    //                }
    //            }
    //            orderInfo.insert(id, o);
    //        }
    //    }
    //    file.close( );
}

OrderHandlerForm::~OrderHandlerForm()
{
    QFile file("orderinfo.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    Q_FOREACH(const auto& v, orderInfo)
    {
        OrderInformaiton* o = v;
        out << orderInfo.key(o) << ", " << o->getOrderDate() << ", ";
        out << o->getOrderNumber() << ", " << o->getCID() << ", " << o->getPID() << "\n";
    }
    file.close();

    delete Oui;
}

int OrderHandlerForm::makeoid()
{
    if(orderInfo.isEmpty())    return 10000;
    else    return orderInfo.size() + 10000;
}

void OrderHandlerForm::clientAdded(int cid)
{
    Oui->clientIDComboBox1->addItem(QString::number(cid));
}

void OrderHandlerForm::productAdded(int pid)
{
    Oui->productIDComboBox1->addItem(QString::number(pid));
}

void OrderHandlerForm::on_enrollPushButton_clicked()
{
    emit orderAdded();
    int key = makeoid();
    QString date = Oui->orderDateLineEdit1->text();
    int quantity = Oui->orderQuantityLineEdit1->text().toInt();
    int cid = Oui->clientIDComboBox1->currentText().toInt();
    int pid = Oui->productIDComboBox1->currentText().toInt();

    QVector<QTableWidget*> w;
    w << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;


    int row = Oui->tableWidget1->rowCount();
    for(int x = 0; x < 4; x++)
    {
        w[x]->setRowCount(w[x]->rowCount()+1);
        w[x]->setItem(row, 0, new QTableWidgetItem(QString::number(key)));
        w[x]->setItem(row, 1, new QTableWidgetItem(Oui->orderDateLineEdit1->text()));
        w[x]->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
        w[x]->setItem(row, 3, new QTableWidgetItem(QString::number(cid)));
        w[x]->setItem(row, 4, new QTableWidgetItem(QString::number(pid)));
    }

    OrderInformaiton *o = new OrderInformaiton(key, date, quantity, cid, pid);

    orderInfo.insert(key, o);
    update();

}

