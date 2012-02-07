#include <QtGui/QApplication>
#include <QtSql>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);


    MainWindow w(a.applicationDirPath());
    w.show();

    return a.exec();
}
