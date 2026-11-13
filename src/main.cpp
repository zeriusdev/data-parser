#include "mainwindow.h"

#include <QApplication>
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    Stats stats;
    QString path = "missing.csv";
    processFile(path, stats);

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