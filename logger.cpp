#include "logger.h"
#include "QDateTime"
bool Logger::exists = 0;
Logger* Logger::instance = 0;
Logger::Logger()
{
    this->exists = 1;


    fileName = "log_";
    fileName.append(QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss"));
    fileName.append(".log");
    loggFile = new QFile(fileName);
    loggFile->open(QIODevice::WriteOnly | QIODevice::Text);
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
    QTextStream stream(loggFile);
    stream << s << endl;
}
