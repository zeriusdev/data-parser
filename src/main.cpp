#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../data/sample.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return 1;
    }

    QTextStream stream(&file);
    int lineNumber = 0;

    Stats stats;
    Record record;

    while (!stream.atEnd()) {
        ++lineNumber;

        QString line = stream.readLine();
        QString cleanLine = line.trimmed();

        if (lineNumber == 1) {
            continue;
        }

        bool isOk = parseCsvLine(cleanLine, record);
        accumulateStats(cleanLine, isOk, record, stats);

        if (!isOk) {
            qDebug() << "bad line:" << lineNumber << "text:" << cleanLine;
        }
    }

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