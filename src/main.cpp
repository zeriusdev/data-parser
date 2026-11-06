#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../data/sample.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return 1;
    }

    QTextStream in(&file);
    int totalLines = 0;

    while (!in.atEnd()) {
        in.readLine();
        ++totalLines;
    }

    qDebug() << "total Lines:" << totalLines;

    // MainWindow w;
    // w.show();
    // return QApplication::exec();

    return 0;
}
