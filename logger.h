/*****************************************************************************
** "logger.h"                                                               **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.1 11/12/07 Utworzono klase                                          PK **
** 0.5 11/12/22 Zmieniono format logowania zdarzeñ                       PS **
** 0.7 11/12/29 Poprawiono konstruktor klasy                             PS **
*****************************************************************************/

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
    QFile* loggFile_;
    QTextStream* textStream_;
    QString fileName_;
    bool log_;

public:
    static Logger* getInstance();
    void logguj(QString);
};

#endif // LOGGER_H
