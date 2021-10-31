#include "graf.h"
#include <fstream>

void Graf::GenerareMatriceAdiacenta()
{
    std::fstream file;
    std::string path="D:\\AG\\Tema1\\matriceAdiacenta.txt";

    file.open(path, std::ios::out | std::ios::app);
    file<<getNumberofNodes()<<std::endl;

    matriceAdiacenta.resize(getNumberofNodes());
    for(int index=0;index<matriceAdiacenta.size();index++)
    {
        matriceAdiacenta[index].resize(getNumberofNodes());
        std::fill(matriceAdiacenta[index].begin(),matriceAdiacenta[index].end(),0);
    }

    for(auto&index:arcs)
    {
        int coordX=index.getFirstPoint().getNumber();
        int coordY=index.getSecondPoint().getNumber();
        matriceAdiacenta[coordX][coordY]=1;
    }

    for(int index=0;index<matriceAdiacenta.size();index++)
    {
        for(int index2=0;index2<matriceAdiacenta[index].size();index2++)
        {
            file<<matriceAdiacenta[index][index2]<<" ";
        }
        file<<std::endl;
    }
    file.close();
}

std::vector<Arc> Graf::GetArcs()
{
    return arcs;
}

std::vector<Node> Graf::GetNodes()
{
    return nodes;
}

void Graf::AddNod(Node n)
{
    for(auto&index:nodes)
    {
        if(index.getPoint()==n.getPoint() or
                (abs(index.getPoint().x()-n.getPoint().x())<50 and
                   abs(index.getPoint().y()-n.getPoint().y()) <50 ))
            return;
    }//se verifica daca nodul este deja prezent si totodata se verifica ca distanta dintre nodes sa fie rezonabila
    n.setNumber(nodes.size());
    nodes.push_back(n);
}

void Graf::AddArc(Arc n)
{
    int nFirstNumber=n.getFirstPoint().getNumber();
    int nSecondNumber=n.getSecondPoint().getNumber();

    for(auto&index:arcs)
    {
        int firstNumber=index.getFirstPoint().getNumber();
        int secondNumber=index.getSecondPoint().getNumber();
        if(nFirstNumber==firstNumber and nSecondNumber==secondNumber)
            return;
    }

    arcs.push_back(n);
}

Node Graf::GetLastNode()
{
    return nodes[nodes.size()-1];
}

int Graf::getNumberofNodes()
{
    return nodes.size();
}
