#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QTextStream>
#include "QDateTime"
class Logger
{
private:
    Logger();
    Logger(const Logger &);
    static bool exists;
    static Logger* instance;
    QFile* loggFile;
    QTextStream* textStream;
    QString fileName;
public:
    static Logger* getInstance();
    void logguj(QString);
};

#endif // LOGGER_H
