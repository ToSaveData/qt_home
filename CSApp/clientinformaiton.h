#ifndef CLIENTINFORMAITON_H
#define CLIENTINFORMAITON_H
#include <iostream>
#include <QString>
#include <QTableWidgetItem>
using namespace std;

class ClientInformaiton : public QTableWidgetItem
{
public:
    ClientInformaiton(int, QString, QString, QString, QString, QString); // 생성자
    QString getName() const; //고객 성명 반환
    void setName(QString&); //고객 성명 입력
    QString getBirthday() const; //고객 생년월일 반환
    void setBirthday(QString&); //고객 생년월일 입력
    QString getPhoneNumber() const; //고객 전화번호 반환
    void setPhoneNumber(QString&); //고객 전화번호 입력
    QString getAddress() const; //고객 주소 반환
    void setAddress(QString&); //고객 주소 입력
    QString getEmail() const; //고객 이메일주소 반환
    void setEmail(QString&); //고객 이메일주소 입력
private:
    int m_id; //고객 ID, PK
    QString m_name; //고객 성명
    QString m_birthday; //고객 생년월일
    QString m_phoneNumber; //고객 전화번호
    QString m_address; //고객 주소
    QString m_email; //고객 이메일주소

};

#endif // CLIENTINFORMAITON_H
