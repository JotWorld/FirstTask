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
QVector<int> transformFile::readPoints(QString filePath){
    QVector<int> points ={};
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return points;
    QTextStream stream(&file);
    QString localLine = stream.readLine();
    QString line = stream.readLine();
    points = strToInt(line);
    qDebug() << line;
    return points;
}
QList<QString> transformFile::read(QString filePath){
    QList<QString> strArray;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return strArray;
    QTextStream stream(&file);
    QString line = stream.readLine();
    QString localLine = stream.readLine();
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
int transformFile::cost(int a, int b){
    return abs(a-b);
}
QVector<QVector<int>> transformFile::aStar(QString filePath){
    QVector<int> pathPoints = readPoints(filePath);
    int start = pathPoints[0];
    qDebug() << "start is " << start;
    int end = pathPoints[1];
    QVector<QVector<int>> resultPath;
    QVector<int> row = {0,0};
    qDebug() << "end is " << end;
    QVector<QVector<int>> matrix = buildMatrix(read(filePath));
    QVector<int> reachablePoints = {};
    QVector<int> exploredPoints = {};
    QVector<int> path(pointsMax((read(filePath))),-1);
    int currentPoint = start;
    while (currentPoint != end){

        exploredPoints.append(currentPoint);

        QVector<int> reachablePointsInMatrix = matrix[currentPoint-1];
        for(int i = 0; i < matrix.size();i++){
            int localCount = 0;
            for(int j = 0; j < matrix.size();j++){
            if(matrix[i][j] == 1){
                localCount++;
            }

        }
            if (localCount == 1){
                if ((i+1 != start) || (i+1 != end)){
                    if (exploredPoints.count(i+1) > 1)
                    exploredPoints.append(i+1);
                }


            }
        }
        for(int i = 0; i < reachablePointsInMatrix.size();i++){
            if(reachablePointsInMatrix[i] == 1){
                if (not (exploredPoints.contains(i+1))){
                    reachablePoints.append(i+1);

                }
            }
        }
        qDebug() << "добавлено";
        for(int i = 0; i < exploredPoints.size();i++){
            qDebug() << exploredPoints[i];
        }
        for (int explored : exploredPoints) {
            reachablePoints.removeAll(explored);
        }

        auto tmp=reachablePoints[qrand()%reachablePoints.size()];
        path[tmp-1]=currentPoint-1;
        currentPoint = tmp;


    }
    qDebug() << "путь";
    for(int i = 0; i < path.size();i++){
        if(path[i] != -1){
        resultPath.append({path[i]+1,i+1});
        qDebug() << path[i]+1 << i+1 << "точка";}

    }
    return resultPath;
}
