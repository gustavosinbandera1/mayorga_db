#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User(int id = -1, const QString& getName = "", const QString& getPhone = "", const QString getEmail = "", const QString& getPassword = "");
    int id() const { return mId; }
    QString getName() const { return mName; }
    QString getPhone() const { return mPhone; }
    QString getEmail() const { return mEmail; }
    QString getPassword() const { return mPassword; }

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
