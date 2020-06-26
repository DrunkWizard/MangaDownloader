#include "fileviewer.hpp"
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileInfo>

FileViewer::FileViewer(QObject *parent) : QObject(parent)
{

}

void FileViewer::fileViewer(const QString librarySource)
{
    fileNumbers = 0;
    QDir libraryDir(librarySource);
    QStringList filesList = libraryDir.entryList(QDir::Dirs);
    QString fileName;
    QFileInfo fileInfo(librarySource);
    foreach(fileName, filesList)
    {
        const QString srcFilePath = librarySource + "/" + fileName;
        fileNumbers++;
        fileInfo.setFile(srcFilePath);
        qDebug() << fileInfo.fileName();
    }
    qDebug() << fileNumbers;
}
