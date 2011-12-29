#include "logger.h"
#include "QDateTime"
#include <QSettings>
bool Logger::exists = 0;
Logger* Logger::instance = 0;
Logger::Logger()
{
    this->exists = 1;

    QSettings settings("config.ini",QSettings::IniFormat);
    log = settings.value("Opcje/logger").toBool();
    if(log)
    {
        fileName = "log_";
        fileName.append(QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss"));
        fileName.append(".log");
        loggFile = new QFile(fileName);
        loggFile->open(QIODevice::WriteOnly | QIODevice::Text);
    }
    //textStream = new QTextStream(loggFile);



}

Logger* Logger::getInstance()
{
    if(Logger::exists)
        return instance;
    else
    {
        instance = new Logger();
        return instance;
    }
}
void Logger::logguj(QString s)
{
    if(log)
    {
        QTextStream stream(loggFile);
        stream << QDateTime::currentDateTime().toString("hh:mm:ss")+" - "+ s << endl;
    }

}
