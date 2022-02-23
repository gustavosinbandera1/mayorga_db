#include "dbmanager.h"

#include <QCryptographicHash>

#define DRIVER "QPSQL"
/**
 * @brief DbManager::DbManager
 * @param host
 * @param username
 * @param password
 * @param database
 */
DbManager::DbManager(const QString& host, const QString& username,
                     const QString& password, const QString& database)
    : _host(host), _user(username), _password(password), _database(database) {
  if (!QSqlDatabase::isDriverAvailable(DRIVER)) {
    qDebug() << "Not driver available ";
    return;
  }
  m_db = QSqlDatabase::addDatabase(DRIVER);
  m_db.setHostName(_host);
  m_db.setUserName(_user);
  m_db.setPassword(_password);
  m_db.setDatabaseName(_database);

  if (m_db.open()) {
    qDebug() << "conection success" << m_db.lastError().text();
  } else {
    qDebug() << "fails to connect";
    return;
  }

  ExecuteSqlScriptFile(
      "/home/gustavo/QT-PROJECTS/dbApplication/tableStructure.sql");
  ExecuteSqlScriptFile(
      "/home/gustavo/QT-PROJECTS/dbApplication/initialData.sql");
  addUser("user-1", "3007433507", "g@gmail.com", getHash("1234"),
          "administrator");
  addUser("user-1", "3007433507", "n@gmail.com", getHash("1234"), "customer");
  // removeUser("gustavosinbandera123@gmail.com","administrator");
}
//---------------------
/**
 * @brief DbManager::getHash
 * @param data
 * @return
 */
QString DbManager::getHash(QString data) {
  QByteArray hash =
      QCryptographicHash::hash(QString(data).toUtf8(), QCryptographicHash::Md5);
  QString stringHash(hash.toHex());
  return stringHash;
}
//---------------------
/**
 * @brief DbManager::selectFromTable
 * @param table
 * @param email
 * @return
 */
QString DbManager::selectFromTable(const QString& table, const QString& email) {
  QString command =
      QString("SELECT * FROM %1  WHERE email LIKE '%2' ").arg(table, email);
  QSqlQuery qry(m_db);
  qry.prepare(command);
  qry.exec();
  if (qry.first()) {
    qDebug() << "Size: " << qry.size();
    qDebug() << " Good Loogd Customer... " << qry.value("email").toString();
    qDebug() << "salida de pass " << qry.value("password").toString();
    return qry.value("password").toString();
  }

  return "";
}
//---------------------
/**
 * @brief DbManager::~DbManager
 */
DbManager::~DbManager() {
  if (m_db.isOpen()) {
    m_db.close();
  }
}

/**
 * @brief DbManager::addUser
 * @param name
 * @param phone
 * @param email
 * @param password
 * @param rol
 * @return
 */
bool DbManager::addUser(const QString& name, const QString& phone,
                        const QString& email, const QString& password,
                        const QString& rol) {
  bool success = false;

  if (!email.isEmpty() && !password.isEmpty()) {
    QString c = QString("INSERT INTO %1 ").arg(rol);

    QSqlQuery query;
    query.prepare(c +
                  " (name, phone,password, email)"
                  "VALUES (?, ?, ?, ?) ON CONFLICT (email) DO NOTHING");
    query.bindValue(0, name);
    query.bindValue(1, phone);
    query.bindValue(2, password);
    query.bindValue(3, email);

    if (query.exec())
      success = true;
    else
      qDebug() << "Error adding user:" << query.lastError();
  } else
    qDebug() << "Error adding user: name cannot be empty";

  return success;
}
//---------------------
/**
 * @brief DbManager::removeUser
 * @param email
 * @return
 */
bool DbManager::removeUser(const QString& email, const QString& rol) {
  bool success = false;
  QString command =
      QString("DELETE FROM %1  WHERE email LIKE '%2' ").arg(rol, email);

  if (userExists(email, rol)) {
    QSqlQuery query;
    query.prepare(command);
    success = query.exec();

    if (!success)
      qDebug() << "Delete user failure:" << query.lastError();
    else
      qDebug() << "User successfully deleted" << email;
  } else
    qDebug() << "Error deleting user: user does not exist";

  return success;
}
//---------------------
/**
 * @brief DbManager::userExists
 * @param username
 * @return
 */
bool DbManager::userExists(const QString& email, const QString& rol) const {
  bool exists = false;
  QString command =
      QString("SELECT email FROM %1  WHERE email LIKE '%2' ").arg(rol, email);

  QSqlQuery query(m_db);
  query.prepare(command);
  if (query.exec()) {
    if (query.next()) exists = true;
  } else
    qDebug() << "User not found:" << query.lastError();

  return exists;
}
//---------------------
/**
 * @brief DbManager::removeAllUsers
 * @return
 */
bool DbManager::removeAllUsers() {
  bool success = false;

  QSqlQuery removeQuery;
  removeQuery.prepare("DELETE FROM login");

  if (removeQuery.exec())
    success = true;
  else
    qDebug() << "Delete all users failed:" << removeQuery.lastError();

  return success;
}
//---------------------
/**
 * @brief DbManager::ExecuteSqlScriptFile
 * @param fileName
 * @return
 */
int DbManager::ExecuteSqlScriptFile(const QString& fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return 0;
  qDebug() << "file opened";
  QTextStream in(&file);
  QString sql = in.readAll();
  QStringList sqlStatements = sql.split(';', QString::SkipEmptyParts);
  int successCount = 0;

  foreach (const QString& statement, sqlStatements) {
    if (statement.trimmed() != "") {
      QSqlQuery query(m_db);
      if (query.exec(statement.trimmed()))
        successCount++;
      else
        qDebug() << "Failed:" << statement << "\nReason:" << query.lastError();
    }
  }
  return successCount;
}
//---------------------
/**
 * @brief DbManager::checkUserCredentials
 * @param email
 * @param pwd
 * @return
 */
bool DbManager::checkUserCredentials(QString email, QString pwd) {
  return false;
}
