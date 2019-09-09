#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QVector>
#include "database.h"
class QThread;
class ServerWorker;
class QJsonObject;


class Server : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    Server(QObject *parent = nullptr,Database* db=0);
    ~Server() override;
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    const int m_idealThreadCount;
    QVector<QThread *> m_availableThreads;
    QVector<int> m_threadsLoad;
    QVector<ServerWorker *> m_clients;
    Database* db;
private slots:
//    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender, int threadIdx);
    void userError(ServerWorker *sender);
public slots:
    void stopServer();
private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    QJsonObject signup(const QJsonObject &doc);
    QJsonObject login(const QJsonObject &doc);
//    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
signals:
    void logMessage(const QString &msg);
    void stopAllClients();
};

#endif // SERVER_H