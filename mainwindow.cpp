#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include "transformfile.h"
#include "drawer.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    transformFile tf;
    Drawer dr;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QString filePath = ":/new/files/qtgraph.txt";
    if (tf.readMethod(filePath) == "adjancyMatrix"){
        dr.drawEdges(scene,filePath,dr.drawPoints(scene,filePath));
    }
    else if (tf.readMethod(filePath) == "edgeArray"){
        QVector<QVector<int>> edgeArray = tf.buildArray(tf.read(filePath));
        dr.drawEdges(scene,edgeArray,dr.drawPoints(scene,filePath));
    }
    else{
        qDebug() << "некорретный ввод данных";
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(400, 400);
    ui->graphicsView->setSceneRect(0, 0, 400, 400);

}

MainWindow::~MainWindow()
{
    delete ui;
}
