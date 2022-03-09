/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "browser.h"

#include <QtSql>
#include <QtWidgets>

#include "qsqlconnectiondialog.h"

Browser::Browser(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  if (QSqlDatabase::drivers().isEmpty())
    QMessageBox::information(
        this, tr("No database drivers found"),
        tr("This app requires at least one Qt database driver. "));

  emit statusMessage(tr("Ready."));
}

Browser::~Browser() {}

void Browser::exec() {
  QSqlQueryModel *model = new QSqlQueryModel(table);
  model->setQuery(
      QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase()));
  table->setModel(model);

  if (model->lastError().type() != QSqlError::NoError)
    emit statusMessage(model->lastError().text());
}

QSqlError Browser::addConnection(const QString &driver, const QString &dbName,
                                 const QString &host, const QString &user,
                                 const QString &passwd, int port) {
  static int cCount = 0;

  QSqlError err;
  QSqlDatabase db;
  db = QSqlDatabase::addDatabase(driver, QString("Browser%1").arg(++cCount));
  db.setDatabaseName(dbName);
  db.setHostName(host);
  db.setPort(port);
  if (!db.open(user, passwd)) {
    err = db.lastError();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(QString("Browser%1").arg(cCount));
  }

  qDebug() << "refreshing widget .........";
  connectionWidget->refresh();
  return err;
}

void Browser::refreshConnection() { connectionWidget->refresh(); }

void Browser::addConnection() {
  QSqlConnectionDialog dialog(this);
  if (dialog.exec() != QDialog::Accepted) return;

  QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(),
                                dialog.hostName(), dialog.userName(),
                                dialog.password(), dialog.port());
  if (err.type() != QSqlError::NoError)
    QMessageBox::warning(this, tr("Unable to open database"),
                         tr("An error occurred while "
                            "opening the connection: ") +
                             err.text());
}

void Browser::showTable(const QString &t) {
  QSqlTableModel *model =
      new CustomModel(table, connectionWidget->currentDatabase());
  model->setEditStrategy(QSqlTableModel::OnRowChange);
  model->setTable(
      connectionWidget->currentDatabase().driver()->escapeIdentifier(
          t, QSqlDriver::TableName));
  model->select();
  if (model->lastError().type() != QSqlError::NoError)
    emit statusMessage(model->lastError().text());

  table->setModel(model);
  table->setEditTriggers(QAbstractItemView::DoubleClicked |
                         QAbstractItemView::EditKeyPressed);
}

void Browser::showMetaData(const QString &t) {
  QSqlRecord rec = connectionWidget->currentDatabase().record(t);
  QStandardItemModel *model = new QStandardItemModel(table);

  model->insertRows(0, rec.count());
  model->insertColumns(0, 7);

  model->setHeaderData(0, Qt::Horizontal, "Fieldname");
  model->setHeaderData(1, Qt::Horizontal, "Type");
  model->setHeaderData(2, Qt::Horizontal, "Length");
  model->setHeaderData(3, Qt::Horizontal, "Precision");
  model->setHeaderData(4, Qt::Horizontal, "Required");
  model->setHeaderData(5, Qt::Horizontal, "AutoValue");
  model->setHeaderData(6, Qt::Horizontal, "DefaultValue");

  for (int i = 0; i < rec.count(); ++i) {
    QSqlField fld = rec.field(i);
    model->setData(model->index(i, 0), fld.name());
    model->setData(model->index(i, 1),
                   fld.typeID() == -1
                       ? QString(QMetaType::typeName(fld.type()))
                       : QString("%1 (%2)")
                             .arg(QMetaType::typeName(fld.type()))
                             .arg(fld.typeID()));
    model->setData(model->index(i, 2), fld.length());
    model->setData(model->index(i, 3), fld.precision());
    model->setData(model->index(i, 4),
                   fld.requiredStatus() == -1
                       ? QVariant("?")
                       : QVariant(bool(fld.requiredStatus())));
    model->setData(model->index(i, 5), fld.isAutoValue());
    model->setData(model->index(i, 6), fld.defaultValue());
  }

  table->setModel(model);
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Browser::about() {
  QMessageBox::about(
      this, tr("About"),
      tr("The SQL Browser demonstration "
         "shows how a data browser can be used to visualize the results of SQL"
         "statements on a live database"));
}
