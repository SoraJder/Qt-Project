#ifndef GRAF_H
#define GRAF_H
#include "node.h"
#include "arc.h"
class Graf
{
    std::vector<Node> nodes;
    std::vector<Arc> arcs;
    std::vector<std::vector<int>> matriceAdiacenta;

public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();
    std::vector<Arc> GetArcs();
    std::vector<Node> GetNodes();
    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    Node GetLastNode();
    int getNumberofNodes();
};
#endif // GRAF_H
