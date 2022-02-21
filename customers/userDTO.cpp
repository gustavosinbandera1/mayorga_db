#include "userDTO.h"

User::User(int id, const QString& name, const QString& phone, const QString email, const QString& password)
    : mId(id), mName(name), mPhone(phone),mEmail(email), mPassword(password) {

}
