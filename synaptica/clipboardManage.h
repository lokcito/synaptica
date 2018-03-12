#ifndef CLIPBOARDMANAGE_H
#define CLIPBOARDMANAGE_H

#include <QObject>
#include <QtGlobal>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QString>


class ClipboardManage : public QObject{
    Q_OBJECT
public:
    explicit ClipboardManage(QObject *parent = 0);
signals:
    void doText();
public slots:
    void toClipboard(const QString _text);
};

#endif // CLIPBOARDMANAGE_H
