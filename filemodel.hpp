#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QDir>
#include <QString>
#include <QList>
#include <QAbstractListModel>
#include <QUrl>
#include <QDesktopServices>

class FileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FileModel(QObject *parent = nullptr);
    Q_INVOKABLE void fileViewer();
    enum Roles{
        NameRole = Qt::UserRole,
        FileSizeRole

    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void openDir(QString fileName);
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    struct Item{
        QString fileName;
        QString fileSize;
    };
    QList<Item> collectedData;
};

#endif // FILEMODEL_H
