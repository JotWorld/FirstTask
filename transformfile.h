#ifndef QREADFILE_H
#define QREADFILE_H
#include <QString>

class transformFile
{
public:
    transformFile();
    QString readMethod(QString filePath);
    QList<QString> read(QString filePath);
    QVector<QVector<int>> buildMatrix(QList<QString>);
    QVector<QVector<int>> buildArray(QList<QString> strArray);
    int pointsCount(QList<QString> strArray);
    QVector<int> strToInt(QString row);
    int pointsMax(QList<QString> strArray);
    QVector<QVector<int>> aStar(QString pathFile);
    QVector<int> readPoints(QString filePath);
    int cost(int a,int b);
};

#endif // QREADFILE_H
