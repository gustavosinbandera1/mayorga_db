#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "db_config.h"

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with postgres
 */
class DbManager {
 public:
  /**
   * @brief Constructor
   *
   * Constructor sets up connection with db and opens it
   */
  DbManager(const QString& host, const QString& username,
            const QString& password, const QString& database);
  QSqlDatabase& db() { return m_db; }
  /**
   * @brief Destructor
   *
   * Close the db connection
   */
  ~DbManager();

  bool isOpen() const;

  /**
   * @brief Add person data to db
   * @param name - name of person to add
   * @return true - person added successfully, false - person not added
   */
  bool addUser(const QString& name, const QString& phone, const QString& email,
               const QString& password, const QString& rol);
  /**
   * @brief Remove person data from db
   * @param name - name of person to remove.
   * @return true - person removed successfully, false - person not removed
   */
  bool removeUser(const QString& username, const QString& rol);

  /**
   * @brief Check if person of name "name" exists in db
   * @param name - name of person to check.
   * @return true - person exists, false - person does not exist
   */
  bool userExists(const QString& email, const QString& rol) const;

  /**
   * @brief Remove all persons from db
   * @return true - all persons removed successfully, false - not removed
   */
  bool removeAllUsers();

  /**
   * @brief ExecuteSqlScriptFile
   * @param db
   * @param fileName
   * @return
   */
  int ExecuteSqlScriptFile(const QString& fileName);

  int createInitialStructure(QSqlDatabase& db, const QString& fileName);
  /**
   * @brief getHash convert passowrd string to hash 32 bits string
   * @param data
   * @return hash string
   */
  QString getHash(QString data);

  bool checkUserCredentials(QString email, QString pwd);

  QString getPasswordFromTable(const QString& table, const QString& email);

 private:
  QSqlDatabase m_db;
  QString _host, _port, _user, _password, _database;
};

#endif  // DBMANAGER_H
