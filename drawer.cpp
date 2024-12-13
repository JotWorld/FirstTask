#include "drawer.h"
#include "Qtransformfile.h"
#include <QList>
#include <QGraphicsEllipseItem>
#include <QBrush>
Drawer::Drawer()
{

}
QVector<QGraphicsEllipseItem*> Drawer::drawPoints(QGraphicsScene *scene, QString filePath){
    Qtransformfile qtf;
    int pointsCount = qtf.pointsCount(qtf.read(filePath));
    QVector<QGraphicsEllipseItem*> pointsArray;

    for (int i = 0;i<pointsCount;i++){
        qreal x = qrand() % 400;
        qreal y = qrand() % 400;
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(x - 2, y - 2, 4, 4);
        pointsArray.append(ellipse);
        ellipse->setBrush(Qt::black);
        scene -> addItem(ellipse);
        QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::number(i + 1));
        textItem->setPos(x + 5, y - 10);
        scene->addItem(textItem);
    }
    return pointsArray;
}
void Drawer::drawEdges(QGraphicsScene *scene,QString filePath,QVector<QGraphicsEllipseItem*> pointsArray){
    Qtransformfile qtf;
    QVector<QVector<int>> matrix = qtf.buildmatrix(qtf.read(filePath));
    int len = qtf.pointsCount(qtf.read(filePath));
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
