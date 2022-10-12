#include "clientinformaiton.h"

ClientInformaiton::ClientInformaiton
(int id, QString name, QString birthday, QString phoneNumber, QString address, QString email)
    : m_id(id), m_name(name), m_birthday(birthday), m_phoneNumber(phoneNumber), m_address(address), m_email(email)
{}    //생성자

QString ClientInformaiton::getName() const { return m_name; } //고객 성명 반환
void ClientInformaiton::setName(QString& name) //고객 성명 입력
{
    m_name = name;
}

QString ClientInformaiton::getBirthday() const { return m_birthday; } //고객 생년월일 반환
void ClientInformaiton::setBirthday(QString& birthday) //고객 생년월일 입력
{
    m_birthday = birthday;
}

QString ClientInformaiton::getPhoneNumber() const { return m_phoneNumber; } //고객 전화번호 반환
void ClientInformaiton::setPhoneNumber(QString& phoneNumber) //고객 전화번호 입력
{
    m_phoneNumber = phoneNumber;
}

QString ClientInformaiton::getAddress() const { return m_address; } //고객 주소 반환
void ClientInformaiton::setAddress(QString& address) //고객 주소 입력
{
    m_address = address;
}

QString ClientInformaiton::getEmail() const { return m_email; } //고객 이메일주소 반환
void ClientInformaiton::setEmail(QString& email) //고객 이메일주소 입력
{
    m_email = email;
}
