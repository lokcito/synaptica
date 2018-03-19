#ifndef CLIPBOARDMANAGE_H
#define CLIPBOARDMANAGE_H

#include <QObject>
#include <QString>


class ClipboardManage : public QObject{
    Q_OBJECT
public:
    explicit ClipboardManage(QObject *parent = 0);
public slots:
    void toClipboard(const QString _text);
};

#endif // CLIPBOARDMANAGE_H
