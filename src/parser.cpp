#include "parser.h"
#include <QStringList>
#include <QTextStream>
#include <QDebug>

bool parseCsvLine(const QString& line, Record& record)
{
    QStringList parts = line.split(',', Qt::KeepEmptyParts);

    if (parts.size() != 4) {
        return false;
    }

    QString id = parts[0].trimmed();
    if (id.isEmpty()) {
        return false;
    }

    QString timestamp = parts[1].trimmed();
    if (timestamp.isEmpty()) {
        return false;
    }

    QString level = parts[2].trimmed();
    if (level.isEmpty()) {
        return false;
    }

    QString message = parts[3].trimmed();
    if (message.isEmpty()) {
        return false;
    }

    record = Record{id, timestamp, level, message};
    return true;
}


void accumulateStats(const QString &line, bool parseOk, const Record &record, Stats &stats)
{
    ++stats.total;
    if (line.trimmed().isEmpty()) {
        ++stats.empty;
        return;
    }
    if (!parseOk) {
        ++stats.bad;
        return;
    }
    ++stats.records;
    if (record.level == "INFO") {
        ++stats.info;
    }
    if (record.level == "WARN") {
        ++stats.warn;
    }
    if (record.level == "ERROR") {
        ++stats.error;
    }
}

void processFile(const QString &filePath, Stats &stats)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return;
    }

    QTextStream in(&file);
    in.readLine();  // skip header line
    int lineNumber = 1;

    Record record;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QString cleanLine = line.trimmed();
        ++lineNumber;

        bool isOk = parseCsvLine(cleanLine, record);
        accumulateStats(cleanLine, isOk, record, stats);

        if (!isOk) {
            qDebug() << "bad line:" << lineNumber << "text:" << cleanLine;
        }
    }
    file.close();
}
