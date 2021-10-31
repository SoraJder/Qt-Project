
#include "node.h"


Node::Node()
{
    number=-1;
}

Node::Node(QPoint p)
{
    point=p;
}

QPoint Node::getPoint()
{
    return point;
}

int Node::getNumber()
{
    return number;
}

void Node::setNumber(int number)
{
    this->number=number;
}

void Node::setPoint(QPoint point)
{
    this->point=point;
}


