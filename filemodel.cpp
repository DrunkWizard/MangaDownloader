#include "filemodel.hpp"

FileModel::FileModel(QObject *parent) : QAbstractListModel(parent)
{
    fileViewer();
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return collectedData.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    const Item item = collectedData.at(index.row());
    switch (role) {
    case NameRole:
        return QVariant(item.fileName);
    case FileSizeRole:
        return  QVariant(item.fileSize);
    }
}

QHash<int, QByteArray> FileModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "fileName";
    names[FileSizeRole] = "fileSize";
    return names;
}

void FileModel::fileViewer()
{
    const QString librarySource = QDir::currentPath() + R"(/Library/)";
    QDir libraryDir(librarySource);
    QStringList filesList = libraryDir.entryList(QDir::Dirs);
    QString fileName;
    QFileInfo fileInfo(librarySource);
    beginResetModel();
    collectedData.clear();
    foreach(fileName, filesList)
    {
        const QString srcFilePath = librarySource + "/" + fileName;
        fileInfo.setFile(srcFilePath);
        if(fileInfo.fileName() != "." && fileInfo.fileName() != "..")
            collectedData.append( {fileInfo.fileName(), QString::number(fileInfo.size()) });
    }
    endResetModel();
}
void FileModel::openDir(QString fileName){
    QString Path (QDir::currentPath() + R"(/Library/)" + fileName);
    QDir Dir(Path);
    QDesktopServices::openUrl(QUrl::fromLocalFile(Dir.absolutePath()));
}
