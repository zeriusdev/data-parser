#include "mainwindow.h"

#include <QApplication>
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../data/sample.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return 1;
    }

    Stats stats;

    processFile(file, stats);

    file.close();

    qDebug() << "records:" << stats.records;
    qDebug() << "totalLines:" << stats.total;
    qDebug() << "emptyLines:" << stats.empty;
    qDebug() << "badLines:" << stats.bad;
    qDebug() << "INFO:" << stats.info;
    qDebug() << "WARN:" << stats.warn;
    qDebug() << "ERROR:" << stats.error;

    // MainWindow w;
    // w.show();
    // return QApplication::exec();

    return 0;
}