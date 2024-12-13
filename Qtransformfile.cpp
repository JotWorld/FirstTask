#include "Qtransformfile.h"
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
Qtransformfile::Qtransformfile(){

}
QList<QString> Qtransformfile::read(QString filePath){
    QList<QString> strArray;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return strArray;
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        strArray.append(stream.readLine());
    }
    foreach(QString str, strArray)
    {
        qDebug() << str;
    }
    return strArray;
}
QVector<int> Qtransformfile::strToInt(QString row){
    QVector<int> result;
    QList<QString> strNumbers = row.split(' ');
    int number1 = strNumbers[0].toInt();
    result.append(number1);
    int number2 = strNumbers[1].toInt();
    result.append(number2);
    return result;
}
QVector<QVector<int>> Qtransformfile::buildmatrix(QList<QString> strArray){
    int matrixLength = this->pointsCount(strArray);
    QVector<QVector<int>> adjancyMatrix(matrixLength, QVector<int>(matrixLength));
    for (int i = 0; i< matrixLength; i++){
        for(int j = 0; j< matrixLength; j++){
            adjancyMatrix[i][j] = 0;
        }
    }
    QVector<int> row;
    foreach(QString str, strArray){
        row = strToInt(str);
        int i = row[0];
        int j = row[1];
        adjancyMatrix[i-1][j-1] = 1;
        adjancyMatrix[j-1][i-1] = 1;
    }
    for (int i = 0; i< matrixLength; i++){
        for(int j = 0; j< matrixLength; j++){
            qDebug().noquote() << adjancyMatrix[i][j];

        }
        qDebug() << "";
    }
    return adjancyMatrix;
}
int Qtransformfile::pointsCount(QList<QString> strArray){
    QList<int> uniqueVertexes;
    QVector<int> row;
    foreach(QString str, strArray){
        row = strToInt(str);
        if (uniqueVertexes.count(row[0]) == 0){
            uniqueVertexes.append(row[0]);
        }
        if (uniqueVertexes.count(row[1]) == 0){
            uniqueVertexes.append(row[1]);
        }
    }
    return uniqueVertexes.length();
}
