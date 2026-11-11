#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QFile>

struct Record {
    QString id;
    QString timestamp;
    QString level;
    QString message;
};

struct Stats {
    int records = 0;
    int total = 0;
    int empty = 0;
    int bad = 0;
    int info = 0;
    int warn = 0;
    int error = 0;
};

bool parseCsvLine(const QString& line, Record& record);
void accumulateStats(const QString& line, bool parseOk, const Record& record, Stats& stats);
void processFile(QFile& file, Stats& stats);

#endif // PARSER_H
