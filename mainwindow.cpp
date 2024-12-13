#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include "transformfile.h"
#include "drawer.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    transformFile tf;
    Drawer dr;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QString filePath = ":/new//files//qtgraph.txt";
    QList<QString> strArray = tf.read(filePath);
    QVector<QVector<int>> adjancyMatrix = tf.buildMatrix(strArray);

    dr.drawEdges(scene,filePath,dr.drawPoints(scene,filePath));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(400, 400);
    ui->graphicsView->setSceneRect(0, 0, 400, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
