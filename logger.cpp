#include "logger.h"
#include "QDateTime"
#include <QSettings>


bool Logger::exists = 0;
Logger* Logger::instance = 0;


Logger::Logger()
{
    this->exists = 1;

    QSettings ustawienia("config.ini",QSettings::IniFormat);
    log_ = ustawienia.value("Opcje/logger").toBool();
    if(log_)
    {
        fileName_ = "log_";
        fileName_.append(QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss"));
        fileName_.append(".log");
        loggFile_ = new QFile(fileName_);
        loggFile_->open(QIODevice::WriteOnly | QIODevice::Text);
    }
    //textStream = new QTextStream(loggFile);
}



Logger* Logger::getInstance()
{
    if(Logger::exists)
    {
        return instance;
    }
    else
    {
        instance = new Logger();
        return instance;
    }
}


void Logger::logguj(QString s)
{
    if(log_)
    {
        QTextStream stream(loggFile_);
        stream << QDateTime::currentDateTime().toString("hh:mm:ss")+" - "+ s << endl;
    }
}
