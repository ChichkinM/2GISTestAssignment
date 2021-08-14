/*
 * \file WordsPrimaryModel.h
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#pragma once

#include <QAbstractListModel>
#include <parser/Types.h>

namespace doublegis {
namespace model {

class WordsPrimaryModel : public QAbstractListModel
{
Q_OBJECT
    Q_PROPERTY(quint64 maxCount READ getMaxCount NOTIFY maxCountChanged)
public:
    enum Role
    {
        Word = Qt::UserRole + 1,
        Count
    };

public:
    explicit WordsPrimaryModel(QObject *parent) noexcept;

    void update(parser::MostCommonWordsStorage newStorage) noexcept;
    void clear() noexcept;

    quint64 getMaxCount() const noexcept;

signals:
    void maxCountChanged();

protected:
    int rowCount(const QModelIndex &parent) const noexcept override;
    QVariant data(const QModelIndex &index, int role) const noexcept override;
    QHash<int, QByteArray> roleNames() const noexcept override;

private:
    void setMaxCount(quint64 newMaxCount) noexcept;

private:
    struct Entry
    {
        QString word;
        quint64 count;
    };

    std::vector<Entry> storage;
    quint64 maxCount;
};

}
}
