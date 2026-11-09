#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <vector>
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

    std::vector<Record> records;
    Record record;
    int totalLines = 0;
    int emptyLines = 0;
    int badLines = 0;
    int countInfo = 0;
    int countWarn = 0;
    int countError = 0;

    while (!stream.atEnd()) {
        ++lineNumber;
        ++totalLines;

        QString line = stream.readLine();
        QString cleanLine = line.trimmed();

        if (lineNumber == 1) {
            continue;
        }

        if (cleanLine.isEmpty()) {
            ++emptyLines;
            continue;
        }

        if (!parseCsvLine(cleanLine, record)) {
            ++badLines;
            qDebug() << "bad line:" << lineNumber << "text:" << cleanLine;
            continue;
        }

        if (record.level == "INFO") {
            ++countInfo;
        } else if (record.level == "WARN") {
            ++countWarn;
        } else if (record.level == "ERROR") {
            ++countError;
        } else {
            ++badLines;
            continue;
        }
        records.push_back(record);
    }

    file.close();

    qDebug() << "records:" << records.size();
    qDebug() << "totalLines:" << totalLines;
    qDebug() << "emptyLines:" << emptyLines;
    qDebug() << "badLines:" << badLines;
    qDebug() << "INFO:" << countInfo;
    qDebug() << "WARN:" << countWarn;
    qDebug() << "ERROR:" << countError;

    // MainWindow w;
    // w.show();
    // return QApplication::exec();

    return 0;
}