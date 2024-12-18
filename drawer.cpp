#include "drawer.h"
#include "transformfile.h"
#include <QList>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QDebug>
Drawer::Drawer()
{

}
QVector<QGraphicsEllipseItem*> Drawer::drawPoints(QGraphicsScene *scene, QString filePath){
    transformFile tf;
    int pointsCount = tf.pointsMax(tf.read(filePath));
    QVector<QGraphicsEllipseItem*> pointsArray;

    for (int i = 0;i<pointsCount;i++){
        qreal x = qrand() % 400;
        qreal y = qrand() % 400;
        QGraphicsEllipseItem* point = new QGraphicsEllipseItem(x - 2, y - 2, 4, 4);
        pointsArray.append(point);
        point->setBrush(Qt::black);
        scene -> addItem(point);
        QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::number(i + 1));
        textItem->setPos(x + 5, y - 10);
        scene->addItem(textItem);
    }
    return pointsArray;
}

void Drawer::drawEdges(QGraphicsScene *scene,QString filePath,QVector<QGraphicsEllipseItem*> pointsArray){
    transformFile tf;
    QVector<QVector<int>> matrix = tf.buildMatrix(tf.read(filePath));
    int len = tf.pointsMax(tf.read(filePath));
    for (int i = 0; i< len;i++){
        for (int j=0;j<len;j++){
            if (matrix[i][j] == 1){
                QGraphicsEllipseItem *point1 = pointsArray[i];
                int p1x = point1->rect().center().x();
                int p1y = point1->rect().center().y();
                QGraphicsEllipseItem *point2 = pointsArray[j];
                int p2x = point2->rect().center().x();
                int p2y = point2->rect().center().y();
                QGraphicsLineItem* line = new QGraphicsLineItem(p1x,p1y,p2x,p2y);
                line -> setPen(QPen(Qt::black));
                scene ->addItem(line);
            }
        }
    }
}
void Drawer::drawEdges(QGraphicsScene *scene,QVector<QVector<int>> edgeArray,QVector<QGraphicsEllipseItem*> pointsArray){
    int len = edgeArray.size();
    qDebug() << len << " длина";
    for (int i = 0; i< len;i++){
                int local1 = edgeArray[i][0];
                int local2 = edgeArray[i][1];
                qDebug() << "создание локалки  " << local1 << " " << local2;
                QGraphicsEllipseItem *point1 = pointsArray[local1-1];
                int p1x = point1->rect().center().x();
                int p1y = point1->rect().center().y();
                QGraphicsEllipseItem *point2 = pointsArray[local2-1];
                int p2x = point2->rect().center().x();
                int p2y = point2->rect().center().y();
                QGraphicsLineItem* line = new QGraphicsLineItem(p1x,p1y,p2x,p2y);
                line -> setPen(QPen(Qt::black));
                scene ->addItem(line);

    }
}
