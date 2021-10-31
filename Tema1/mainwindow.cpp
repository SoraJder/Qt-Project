#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include <QMouseEvent>
#include <QPainter>
#include <fstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawNode = false;
    drawArc = false;
    selectNode=false;
    isOriented = false;
    pushedButton=false;
    ui->setupUi(this);
    ui->label->setText("Choose an option!\n");
    QObject::connect(ui->btnOrientat,&QPushButton::clicked,this,&MainWindow::on_Orientat_clicked);
    QObject::connect(ui->btnNeorientat,&QPushButton::clicked,this,&MainWindow::on_Neoriented_clicked);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    drawNode = false;
    drawArc = false;

    if(pushedButton==true)
    {if(e->button() == Qt::RightButton)//adding a node in the graph
    {
        Node n(e->pos());
        g.AddNod(n);
        drawNode = true;
        update();

        std::fstream out;
        std::string path="D:\\AG\\Tema1\\matriceAdiacenta.txt";
        out.open(path, std::ios::out | std::ios::trunc); //sterge continutul din fisierul text
        out.close();

        g.GenerareMatriceAdiacenta();
        firstNode = Node();
    }
    else if(e->button()==Qt::LeftButton)
    {
        QPointF p = e->pos();
        std::vector<Node> nodes = g.GetNodes();
        Node foundNode;
        for (auto& n : nodes)
        {
            if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
            {
                foundNode = n;
                break;
            }
        }
        if (foundNode.getNumber() == -1)
            return;
        if (firstNode.getNumber() == -1)
        {
            firstNode = foundNode;
        }
        else
        {
            secondNode = foundNode; //add an arc/edge in the graph
            g.AddArc(Arc(firstNode, secondNode));
            if(isOriented==false) //in cazul in care e graf neorientat sa nu se poate adauga ulterior arcul invers
            {
              g.AddArc(Arc(secondNode,firstNode));
            }
            firstNode = Node();
            secondNode = Node();
            drawArc = true;
            update();
            std::fstream out;
            std::string path="D:\\AG\\Tema1\\matriceAdiacenta.txt";
            out.open(path, std::ios::out | std::ios::trunc); //clear the txt file
            out.close();

            g.GenerareMatriceAdiacenta();
        }
    }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *e) //find the coordinates of the node we want to move
{

    if(e->button()==Qt::MiddleButton)
    {
        QPointF p(e->pos());
        std::vector<Node> nodes = g.GetNodes();
        for(auto&n:nodes)
        {

            float fabsX=fabs(n.getPoint().x()-p.x());
            float fabsY=fabs(n.getPoint().y()-p.y());
            if(fabsX<20 and fabsY<20)
             {
                selectNode=true;
                move->setPoint(n.getPoint());
                move->setNumber(n.getNumber());
                break;
            }
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    while (e->button()==Qt::MiddleButton)
    {
        move->setPoint(e->pos());
        std::vector<Node> nodes = g.GetNodes();
        for(auto&n:nodes)
        {
            if(n.getNumber()==move->getNumber())
            {
                n.setPoint(move->getPoint());
                update();
            }
        }
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{

    if(pushedButton==true)
   { if (g.getNumberofNodes())
    {
        QPainter p(this);
        std::vector<Node> nodes = g.GetNodes();
        for(auto& nod: nodes)
        {
            QRect r(nod.getPoint().x()-10,nod.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            QString text=QString::number(nod.getNumber());
            p.drawText(nod.getPoint(),text);
        }
        std::vector<Arc> arce = g.GetArcs();
        for(auto& arc: arce)
        {
            p.drawLine(arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());
            //drawing an arrow
            if(isOriented)
           {
                p.setRenderHint(QPainter::Antialiasing, true);
                qreal arrowsize=8;
                p.setBrush(Qt::black);

                QLine line(arc.getSecondPoint().getPoint(),arc.getFirstPoint().getPoint());
                double angle=std::atan2(-line.dy(),line.dx());
                QPointF arrowP1=line.p1()+QPointF(sin(angle+M_PI/3)*arrowsize,cos(angle+M_PI/3)*arrowsize);
                QPointF arrowP2=line.p1()+QPointF(sin(angle+M_PI-M_PI/3)*arrowsize,cos(angle+M_PI-M_PI/3)*arrowsize);
                QPolygonF arrowhead;
                arrowhead.clear();
                arrowhead<<line.p1()<<arrowP1<<arrowP2;
                p.drawLine(line);
                p.drawPolygon(arrowhead);

            }


        }
        if (drawNode)
        {
            Node n = g.GetLastNode();
            p.setPen(QPen(Qt::blue));
            p.setBrush(Qt::white);
            QRect r(n.getPoint().x()-10,n.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            QString text=QString::number(n.getNumber());
            p.setFont(QFont("Arial",5));
            p.drawText(n.getPoint(), text);
        }
        else if (drawArc)
        {
            p.setPen(QPen(Qt::red));
            p.drawLine(QLine(arce[arce.size()-1].getFirstPoint().getPoint(), arce[arce.size()-1].getSecondPoint().getPoint()));
        }
    }
    }
    update();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Orientat_clicked()
{
    isOriented = true;
    ui->label->setText("Oriented graph!");
    ui->btnOrientat->hide();
    ui->btnNeorientat->hide();
    pushedButton=true;
    update();


}


void MainWindow::on_Neoriented_clicked()
{
    isOriented = false;
    ui->label->setText("Neoriented graph!");
    ui->btnOrientat->hide();
    ui->btnNeorientat->hide();
    pushedButton=true;
       update();
}

