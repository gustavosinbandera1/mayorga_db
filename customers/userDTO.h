#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User(int id = -1, const QString& name = "", const QString& phone = "", const QString email = "", const QString& password = "");
    int id() const { return mId; }
    QString name() const { return mName; }
    QString phone() const { return mPhone; }
    QString email() const { return mEmail; }
    QString password() const { return mPassword; }

    void setId(int id) {mId = id;}
    void setName(const QString& name) { mName = name; }
    void setPhone(const QString& phone) { mPhone = phone; }
    void setEmail(const QString& email) { mEmail = email;}
    void setPassword(const QString& password)  { mPassword = password; }


private:
    int mId;
    QString mName;
    QString mPhone;
    QString mEmail;
    QString mPassword;
};

#endif // USER_H
