#include <QtDebug>
#include <QFileInfo>
#include <QClipboard>
#include <QApplication>
#include <QDateTime>
#include <stdexcept>

#include "clipboardManage.h"


ClipboardManage::ClipboardManage(QObject *parent) :QObject(parent){

}

void ClipboardManage::toClipboard(const QString _text){
    QApplication::clipboard()->setText(_text);
}
