#ifndef QREADFILE_H
#define QREADFILE_H
#include <QString>

class Qtransformfile
{
public:
    Qtransformfile();
    QList<QString> read(QString filePath);
    QVector<QVector<int>> buildmatrix(QList<QString>);
    int pointsCount(QList<QString> strArray);
    QVector<int> strToInt(QString row);
};

#endif // QREADFILE_H
