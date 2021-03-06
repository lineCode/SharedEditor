#ifndef CLIENT_H
#define CLIENT_H

#include "../Utility/byte_reader.h"
#include "../Utility/serializesize.h"
#include "../Utility/symbol.h"
#include "remotecursor.h"
#include <QBuffer>
#include <QObject>
#include <QProgressDialog>
#include <QSslSocket>
#include <QTcpSocket>

class QHostAddress;
class QJsonDocument;

class Client : public QObject, ByteReader {
  Q_OBJECT
  Q_DISABLE_COPY(Client)

public:
  explicit Client(QObject *parent = nullptr, QString addr = nullptr,
                  quint16 port = 0);
  QString getNickname();
  QString getUsername();
  void setNickname(const QString &nickname);
  QPixmap *getProfile();
  void sendProfileImage();
  void sendProfileImage(const QString &name, QPixmap *pixmap);
  void overrideProfileImage(const QPixmap &pixmap);
  void getFiles(bool shared);
  void getFilenameFromLink(const QString &sharedLink);
  QList<QPair<QString, QString>> getActiveFiles();
  void sendJson(const QJsonObject &message);
  QByteArray createByteArrayFileContent(QJsonObject message,
                                        QVector<Symbol> vector);
  void createNewFile(QString filename);
  void closeFile();
  void sendByteArray(const QByteArray &byteArray);
  QString getSharedLink();
  QString getOpenedFile();
  void setOpenedFile(const QString &name);
  int getColor();
  void checkOldPassword(const QString &old_password);
  void checkExistingOrNotUsername(const QString &username);

public slots:
  void connectToServer(const QHostAddress &address, quint16 port);
  void login(const QString &username, const QString &password);
  void signup(const QString &username, const QString &password,
              QPixmap *pixmap);
  void updateNickname(const QString &nickname);
  void updatePassword(const QString &oldpassword, const QString &newpassword);

  void disconnectFromHost();
  void openFile(const QString &filename);

private slots:
  void onReadyRead();
  void on_byteArrayReceived(const QByteArray &doc);
  void on_jsonReceived(const QJsonObject &doc);

signals:
  void connected();
  void loggedIn();
  void signedUp();
  void signupError(const QString &reason);
  void loginError(const QString &reason);
  void disconnected();
  void error(QAbstractSocket::SocketError socketError);

  void wrongOldPassword(const QString &reason);
  void correctOldPassword();
  void successUpdatePassword();
  void failedUpdatePassword(const QString &reason);

  void filesReceived(bool shared);
  void openFilesError(const QString &reason);

  void remoteInsert(Symbol s);
  void remotePaste(QVector<Symbol> s);
  void remoteErase(QVector<Symbol> s);
  void remoteChange(QVector<Symbol> s);
  void remoteAlignChange(Symbol s);
  void correctNewFile();
  void correctOpenedFile();
  void wrongNewFile(const QString &reason);
  void wrongListFiles(const QString &reason);
  void usersConnectedReceived(QList<QPair<QPair<QString, QString>, QPixmap>>);
  void contentReceived(const QString text);
  void userDisconnected(const QString &username, const QString &nickname);
  void wrongSharedLink(const QString &filename);
  void addCRDTterminator();
  void remoteCursor(int editor_id, Symbol s);
  void existingUsername(const QString &username);
  void successUsernameCheck(const QString &username);

  void byteArrayReceived(const QByteArray &doc);
  void jsonReceived(const QJsonObject &doc);

  void openedFile();

private:
  QString addr;
  quint16 port;
  QSslSocket *m_clientSocket;
  bool m_loggedIn;
  QString username;
  QString nickname;
  QPixmap *profile;
  QList<QPair<QString, QString>> files;
  QString openfile;
  QString sharedLink;
  quint64 m_exptected_json_size = 0;
  QByteArray m_received_data;
  QBuffer m_buffer;
  QProgressDialog *progress;
  int progress_counter = 0;
  QMap<int, QJsonArray> tmp_map;
  int tmp_symbols_counter = 0;
  int tmp_num_chunk = 0;
};

#endif // CLIENT_H
