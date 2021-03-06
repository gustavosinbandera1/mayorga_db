#include "dbmanager.h"

#include <QApplication>
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

  QString mainPath = QApplication::applicationDirPath();

  qDebug() << "Dir: " << mainPath + "/sql/tableStructure.sql";
  ExecuteSqlScriptFile(mainPath + +"/sql/tableStructure.sql");
  ExecuteSqlScriptFile(mainPath + "/sql/initialData.sql");

  addUser("user-1", "3007433537", "g@gmail.com", getHash("1234"),
          "administrator");
  addUser("user-2", "3007433536", "n@gmail.com", getHash("1234"), "customer");

  addUser("user-3", "3007433538", "gustavosinbandera1234@gmail.com",
          getHash("1234"), "administrator");
  removeUser("gustavosinbandera1234@gmail.com");
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
QPair<QString, int> DbManager::getPasswordFromTable(const QString& table,
                                                    const QString& email) {
  QString command =
      QString("SELECT * FROM %1  WHERE email LIKE '%2' ").arg(table, email);
  QSqlQuery qry(m_db);
  qry.prepare(command);
  qry.exec();
  if (qry.first()) {
    qDebug() << "Size: " << qry.size();

    qDebug() << " Good Loogd Customer... " << qry.value("email").toString()
             << " ** " << qry.value("role").toString();
    return QPair<QString, int>(qry.value("password").toString(),
                               qry.value("customer_id").toInt());
  }

  return QPair<QString, int>("", -1);
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
                        const QString& role) {
  bool success = false;

  if (!email.isEmpty() && !password.isEmpty()) {
    QString c = QString("INSERT INTO customer ");

    QSqlQuery query;
    query.prepare(c +
                  " (name, phone,password, email,role)"
                  "VALUES (?, ?, ?, ?, ?) ON CONFLICT (email) DO NOTHING");
    query.bindValue(0, name);
    query.bindValue(1, phone);
    query.bindValue(2, password);
    query.bindValue(3, email);
    query.bindValue(4, role);

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
bool DbManager::removeUser(const QString& email) {
  bool success = false;
  QString command =
      QString("DELETE FROM customer  WHERE email LIKE '%1' ").arg(email);

  if (userExists(email)) {
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
bool DbManager::userExists(const QString& email) const {
  bool exists = false;
  QString command =
      QString("SELECT email FROM customer  WHERE email LIKE '%1' ").arg(email);

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
  (void)email;
  (void)pwd;
  return false;
}
