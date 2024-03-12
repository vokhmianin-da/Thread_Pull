#ifndef PULLMESSAGES_H
#define PULLMESSAGES_H

#include <QObject>
#include <QString>

class PullMessages : public QObject
{
    Q_OBJECT
public:
    explicit PullMessages(QObject *parent = nullptr);

signals:
    void SendMessage(QString);
};

#endif // PULLMESSAGES_H
