#ifndef DRAWER_H
#define DRAWER_H
#include <QGraphicsScene>

class QGraphicsScene;
class Drawer
{
public:
    Drawer();
    QVector<QGraphicsEllipseItem*> drawPoints(QGraphicsScene *scene, QString filePath);
    void pointsMemory(QString filePath);
    void drawEdges(QGraphicsScene *scene,QString filePath,QVector<QGraphicsEllipseItem*> pointsArray);
    void drawEdges(QGraphicsScene *scene,QVector<QVector<int>>edgeArray,QVector<QGraphicsEllipseItem*> pointsArray);
    void drawAStar(QGraphicsScene *scene,QString filePath,QVector<QGraphicsEllipseItem*> pointsArray);
};

#endif // DRAWER_H
