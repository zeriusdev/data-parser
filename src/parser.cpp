#include "parser.h"
#include <QStringList>

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