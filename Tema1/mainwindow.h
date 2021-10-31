#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graf.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void mousePressEvent(QMouseEvent* e) override; //selecteaza punctul
    //mouse move - muta daca pozitia e in regula
   virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void paintEvent(QPaintEvent *event) override;

    ~MainWindow();

private slots:

    void on_Orientat_clicked();

    void on_Neoriented_clicked();

private:
    Ui::MainWindow *ui;
    Graf g;
    Node firstNode, secondNode;
    Node *move;
    bool drawNode, drawArc, isOriented,pushedButton;
    bool selectNode;

};
#endif // MAINWINDOW_H
