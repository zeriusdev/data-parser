#include "mainwindow.h"

#include <QApplication>
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList args = a.arguments();
    if (args.size() != 2) {
        qWarning() << "Usage:" << args[0] << "../../data/sample.csv";
        return 1;
    }

    Stats stats;
    QString path = args[1];
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