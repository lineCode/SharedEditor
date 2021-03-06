#ifndef LOGIN_H
#define LOGIN_H

#include "appMainWindow.h"
#include "client.h"
#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class Login;
}

class Login : public QWidget {
  Q_OBJECT

public:
  Login(QWidget *parent = nullptr, Client *client = nullptr);
  ~Login();
  void enableAllButtons();
  void correctlySignedup();


private slots:
  void try_to_log();
  void on_t_pushButtonNewAccount_clicked();
  void loggedIn();
  void loginFailed(const QString &reason);
  void on_lineEditUsername_textChanged(const QString &arg);


public slots:
  void disconnect();

signals:
  void changeWidget(int i);

private:
  Ui::Login *ui;
  Client *client;
  void clearLabel();
  void clearLineEdit();
  void addError(QString error);
  void clearError();

};

#endif // LOGIN_H
