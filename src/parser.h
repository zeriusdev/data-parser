#ifndef PARSER_H
#define PARSER_H

#include <QString>

struct Record {
    QString id;
    QString timestamp;
    QString level;
    QString message;
};

bool parseCsvLine(const QString& line, Record& record);

#endif // PARSER_H
