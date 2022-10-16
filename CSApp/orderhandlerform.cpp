#include "orderinformaiton.h"
#include "orderhandlerform.h"
#include "ui_orderhandlerform.h"
#include <QTableWidgetItem>
#include <QList>
#include <QFile>
#include <QComboBox>

OrderHandlerForm::OrderHandlerForm(QWidget *parent) :
    QWidget(parent),
    Oui(new Ui::OrderHandlerForm)
{
    Oui->setupUi(this);

    QFile file("orderinfo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QVector<QTableWidget*> w;
    w << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    Oui->clientIDComboBox1->addItem(tr("select item"));
    Oui->clientInfoComboBox->addItem(tr("select item"));
    Oui->productIDComboBox1->addItem(tr("select item"));
    Oui->productInfoComboBox->addItem(tr("select item"));

    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size())
        {
            int oid = row[0].toInt();
            QString date = row[1];
            int quantity = row[2].toInt();
            int cid = row[3].toInt();
            int pid = row[4].toInt();
            OrderInformaiton* o = new OrderInformaiton(oid, date, quantity, cid, pid);

            int itemRow = Oui->tableWidget1->rowCount();
            Oui->tableWidget1->setRowCount(itemRow + 1);
            Oui->tableWidget1->setItem(itemRow, 0, new QTableWidgetItem(QString::number(oid)));

            for (int i = 0 ; i < 4; i++)
            {
                Oui->tableWidget1->setItem(itemRow, i + 1, new QTableWidgetItem(row[i+1]));
            }

            for(int x = 0; x < 3; x++)
            {
                w[x]->setRowCount(w[x]->rowCount()+1);
                w[x]->setItem(itemRow, 0, new QTableWidgetItem(QString::number(oid)));
                w[x]->setItem(itemRow, 1, new QTableWidgetItem(date));
                w[x]->setItem(itemRow, 8, new QTableWidgetItem(QString::number(quantity)));
            }

            orderInfo.insert(oid, o);
        }
    }
    file.close( );
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

void OrderHandlerForm::dataload()
{
    Q_FOREACH(const auto& v, orderInfo)
    {
        OrderInformaiton* o = v;
        int cid = o->getCID();
        int pid = o->getPID();
        emit orderAddedClient(cid);
        emit orderAddedProduct(pid);
    }
    emit clientComboBox(Oui->clientIDComboBox1, Oui->clientInfoComboBox);
    emit productComboBox(Oui->productIDComboBox1, Oui->productInfoComboBox);
}


int OrderHandlerForm::makeoid()
{
    if(orderInfo.isEmpty())    return 100001;
    else    return orderInfo.size() + 100001;
}

void OrderHandlerForm::clientAdded()
{
    emit clientComboBox(Oui->clientIDComboBox1, Oui->clientInfoComboBox);
}

void OrderHandlerForm::productAdded()
{
    emit productComboBox(Oui->productIDComboBox1, Oui->productInfoComboBox);
}

void OrderHandlerForm::on_enrollPushButton_clicked()
{
    int key = makeoid();
    QString date = Oui->orderDateLineEdit1->text();
    int quantity = Oui->orderQuantityLineEdit1->text().toInt();
    int cid = Oui->clientIDComboBox1->currentText().toInt();
    int pid = Oui->productIDComboBox1->currentText().toInt();

    int row = Oui->tableWidget1->rowCount();
    Oui->tableWidget1->setRowCount(Oui->tableWidget1->rowCount()+1);
    Oui->tableWidget1->setItem(row, 0, new QTableWidgetItem(QString::number(key)));
    Oui->tableWidget1->setItem(row, 1, new QTableWidgetItem(date));
    Oui->tableWidget1->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
    Oui->tableWidget1->setItem(row, 3, new QTableWidgetItem(QString::number(cid)));
    Oui->tableWidget1->setItem(row, 4, new QTableWidgetItem(QString::number(pid)));

    QVector<QTableWidget*> w;
    w << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    for(int x = 0; x < 3; x++)
    {
        w[x]->setRowCount(w[x]->rowCount()+1);
        w[x]->setItem(row, 0, new QTableWidgetItem(QString::number(key)));
        w[x]->setItem(row, 1, new QTableWidgetItem(date));
        w[x]->setItem(row, 8, new QTableWidgetItem(QString::number(quantity)));
    }

    OrderInformaiton *o = new OrderInformaiton(key, date, quantity, cid, pid);

    orderInfo.insert(key, o);

    emit orderAddedClient(cid);
    emit orderAddedProduct(pid);

    update();
}

void OrderHandlerForm::addReturnClient(QList<QString> cinfo)
{
    QVector<QTableWidget*> w;
    w << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    QString name = cinfo[0];
    QString phoneNum = cinfo[1];
    QString address = cinfo[2];

    for(int x = 0; x < 3; x++)
    {
        w[x]->setItem(cnt, 2, new QTableWidgetItem(name));
        w[x]->setItem(cnt, 3, new QTableWidgetItem(phoneNum));
        w[x]->setItem(cnt, 4, new QTableWidgetItem(address));
    }
}

void OrderHandlerForm::addReturnProduct(QList<QString> pinfo)
{
    QVector<QTableWidget*> w;
    w << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    int quantity = w[0]->item(cnt,8)->text().toInt();

    for(int x = 0; x < 3; x++)
    {
        w[x]->setItem(cnt, 5, new QTableWidgetItem(pinfo[0]));
        w[x]->setItem(cnt, 6, new QTableWidgetItem(pinfo[1]));
        w[x]->setItem(cnt, 7, new QTableWidgetItem(pinfo[2]));
        w[x]->setItem(cnt, 9, new QTableWidgetItem(QString::number(pinfo[2].toInt() * quantity)));
    }
    cnt++;
}

void OrderHandlerForm::clientRemoved(int cid)
{
    QVector<QTableWidget*> table;
    table << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;
    QVector<int> keys;

    QVector<QTableWidgetItem*> items = Oui->tableWidget1->findItems(QString::number(cid), Qt::MatchExactly);
    Q_FOREACH(auto v, items)
    {
        int key = table[0]->item(v->row(),0)->text().toInt();
        keys << key;

        table[0]->takeItem(key-100001, 0);
        table[0]->takeItem(key-100001, 1);
        table[0]->takeItem(key-100001, 2);
        table[0]->takeItem(key-100001, 3);
        table[0]->takeItem(key-100001, 4);

        for(int i = 1; i < 4; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                table[i]->takeItem(key-100001, j);
            }
        }
    }

    Q_FOREACH(auto v, keys)
    {
        orderInfo.take(v);
    }
}
void OrderHandlerForm::productRemoved(int pid)
{
    QVector<QTableWidget*> table;
    table << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;
    QVector<int> keys;

    QVector<QTableWidgetItem*> items = Oui->tableWidget1->findItems(QString::number(pid), Qt::MatchExactly);
    Q_FOREACH(auto v, items)
    {
        int key = table[0]->item(v->row(),0)->text().toInt();
        keys << key;

        table[0]->takeItem(key-100001, 0);
        table[0]->takeItem(key-100001, 1);
        table[0]->takeItem(key-100001, 2);
        table[0]->takeItem(key-100001, 3);
        table[0]->takeItem(key-100001, 4);

        for(int i = 1; i < 4; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                table[i]->takeItem(key-100001, j);
            }
        }
    }

    Q_FOREACH(auto v, keys)
    {
        orderInfo.take(v);
    }
}
void OrderHandlerForm::clientModified(int cid, QList<QString> cinfo)
{
    QVector<QTableWidget*> table;
    table << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    QVector<int> keys;
    QVector<int> rows;

    QVector<QTableWidgetItem*> items = Oui->tableWidget1->findItems(QString::number(cid), Qt::MatchExactly);
    Q_FOREACH(auto v, items)
    {
        int key = table[0]->item(v->row(),0)->text().toInt();
        keys << key;
        int row = v->row();
        rows << row;
    }

    for(int x = 0; x < keys.length(); x++)
    {
        int row = rows[x];
        for(int i = 1; i < 4; i++)
        {
            table[i]->setItem(row, 2, new QTableWidgetItem(cinfo[0]));
            table[i]->setItem(row, 3, new QTableWidgetItem(cinfo[1]));
            table[i]->setItem(row, 4, new QTableWidgetItem(cinfo[2]));
        }
    }
    emit clientComboBox(Oui->clientIDComboBox1, Oui->clientInfoComboBox);
}
void OrderHandlerForm::productModified(int pid, QList<QString> pinfo)
{
    QVector<QTableWidget*> table;
    table << Oui->tableWidget1 << Oui->tableWidget2 << Oui->tableWidget4 << Oui->tableWidget5;

    QVector<int> keys;
    QVector<int> rows;

    QVector<QTableWidgetItem*> items = Oui->tableWidget1->findItems(QString::number(pid), Qt::MatchExactly);
    Q_FOREACH(auto v, items)
    {
        int key = table[0]->item(v->row(),0)->text().toInt();
        keys << key;
        int row = v->row();
        rows << row;
    }

    for(int x = 0; x < keys.length(); x++) //변경된 제품의 주문정보와 관련된 모든 데이터에서 정보를 수정
    {
        int row = rows[x];
        for(int i = 1; i < 4; i++) //테이블 위젯 2, 4, 5의 제품 관련 데이터 채우기
        {
            table[i]->setItem(row, 5, new QTableWidgetItem(pinfo[0])); //제품 종류
            table[i]->setItem(row, 6, new QTableWidgetItem(pinfo[1])); //제품명
            table[i]->setItem(row, 7, new QTableWidgetItem(pinfo[2])); //제품 가격
            table[i]->setItem(row, 9, new QTableWidgetItem             //총 가격 = 제품 가격 * 주문수량
                              (QString::number(pinfo[2].toInt() * table[i]->item(row, 8)->text().toInt())));
        }
    }
    emit productComboBox(Oui->productIDComboBox1, Oui->productInfoComboBox);
}

void OrderHandlerForm::on_tableWidget5_itemClicked(QTableWidgetItem *item)
{
    QVector<QLineEdit*> v;
    v << Oui->orderIDLineEdit << Oui->orderDateLineEdit2 << Oui->orderQuantityLineEdit2;
    item = Oui->tableWidget5->currentItem();

    for(int i = 0; i < 3; i++)
        v[i]->setText(Oui->tableWidget5->item(item->row(),i)->text());
    update();
}


void OrderHandlerForm::on_searchPushButton_clicked()
{
    QTableWidget *table = Oui->tableWidget3;
    table->update();
    table->setRowCount(0); //이전 검색결과 초기화
    int key = Oui->searchLineEdit->text().toInt(); //입력된 키 값 저장

    if(orderInfo[key]) //입력된 키가 저장된 정보에 있으면
    {
        QVector<QString> v;
        v << orderInfo[key]->getOrderDate() << QString::number(orderInfo[key]->getOrderNumber());

        int row = table->rowCount();
        table->setRowCount(table->rowCount()+1); //테이블에 데이터가 들어갈 행 생성
        table->setItem(row, 0, new QTableWidgetItem(QString::number(key))); //주문id를 테이블에 삽입
        table->setItem(row, 1, new QTableWidgetItem(v[0])); //주문 일자를 테이블에 삽입
        table->setItem(row, 8, new QTableWidgetItem(v[1])); //주문 수량을 테이블에 삽입
        emit orderSearchedClient(orderInfo[key]->getCID());
        emit orderSearchedProduct(orderInfo[key]->getPID());
    }
    update();
    Oui->searchLineEdit->clear();
}

void OrderHandlerForm::searchReturnClient(QList<QString> cinfo)
{
//여기부터 해야 함
}
void OrderHandlerForm::searchReturnProduct(QList<QString> pinfo)
{

}

void OrderHandlerForm::on_removePushButton_clicked()
{

}


void OrderHandlerForm::on_modifyPushButton_clicked()
{

}

