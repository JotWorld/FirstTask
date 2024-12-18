#include "transformfile.h"
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
transformFile::transformFile(){

}
QString transformFile::readMethod(QString filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return " ";
    QTextStream stream(&file);
    QString line = stream.readLine();
    qDebug() << line;
    return line;
}
QList<QString> transformFile::read(QString filePath){
    QList<QString> strArray;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return strArray;
    QTextStream stream(&file);
    QString line = stream.readLine();
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
QVector<int> transformFile::strToInt(QString row){
    QVector<int> result;
    QList<QString> strNumbers = row.split(' ');
    int number1 = strNumbers[0].toInt();
    result.append(number1);
    int number2 = strNumbers[1].toInt();
    result.append(number2);
    return result;
}
QVector<QVector<int>> transformFile::buildMatrix(QList<QString> strArray){
    int matrixLength = this->pointsMax(strArray);
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
        if ((i <= matrixLength) && (j <= matrixLength)){
        adjancyMatrix[i-1][j-1] = 1;
        adjancyMatrix[j-1][i-1] = 1;}
        else{
            qDebug() << "Неправильный формат данных";
        }
    }
    return adjancyMatrix;
}
QVector<QVector<int>> transformFile::buildArray(QList<QString> strArray){

    int arrayLength = strArray.length();
    QVector<QVector<int>> edgeArray(arrayLength, QVector<int>());
    QVector<int> row;
    int i = 0;
    foreach(QString str, strArray){
        row = strToInt(str);
        edgeArray[i] = row;
        i++;
}
    for(int i =0; i<arrayLength;i++){
        int local1 = edgeArray[i][0];
        int local2 = edgeArray[i][1];
        qDebug() << i+1 << "строка" << local1 << " " << local2;
    }
    return edgeArray;
}
int transformFile::pointsCount(QList<QString> strArray){
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
int transformFile::pointsMax(QList<QString> strArray){
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
    int max = 0;
    for (int i = 0;i<uniqueVertexes.length();i++){
        if(uniqueVertexes[i] > max){
            max = uniqueVertexes[i];
        }
    }
    return max;
}
