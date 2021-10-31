#ifndef NODE_H
#define NODE_H

#include <QPainter>

class Node
{
    QPoint point;
    int number;

public:
    Node();
    Node(QPoint p);
    QPoint getPoint();
    int getNumber();
    void setNumber(int number);
    void setPoint(QPoint point);


};

#endif // NODE_H
