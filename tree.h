#include <iostream>
#include <vector>
#include <map>

class tree
{
    int deepestLevel; //заданный самый глубокий уровень
    std::map <int, std::vector<int>> levels; //карта вершин по уровням
    std::vector <int> nodes; //вектор значений вершин
    std::vector <bool> minormax; //вектор минимаксных значений для каждого уровня
    bool direction;
    int result;
    struct node //структура узла
    {
        int data;
        int amount;
        int level;
        bool minmax;
        node* parent;
        std::vector <node*> children;
    } *pn = nullptr; //узел дерева

    node* newNode(int lev, node* par) //создание узла
    {
        node *ptr;
        ptr = new node;
        ptr->level = lev+1;
        ptr->amount = 0;
        ptr->data = 0;
        if (lev)
            ptr->parent = par;
        else
            ptr->parent = nullptr;

        std::cout << "Node: level " << ptr->level << std::endl;
        if (ptr->level==deepestLevel) //если достигнут глубочайший уровень, потомки не нужны
        {
            std::cout << "Enter the node value: ";
            std::cin >> ptr->data;
            return ptr;
        }
        std::cout << "How many children for this node? ";
        std::cin >> ptr->amount;
        std::cout << std::endl;

        ptr->children.resize(ptr->amount);
        for (int i = 0; i < ptr->amount; i++)
            ptr->children.at(i) = nullptr;
        
        return ptr;
    }
    node* addNodes(int lev, node* pn, node* par) //функция рекурсивного создания дерева
    {
        node *ptr = pn;
        if (!pn)
        {
            ptr = newNode(lev, par);
            nodes.push_back(ptr->data); //запись узлов в конкретный уровень
            levels[ptr->level] = nodes; //занесение вектора в соответствие уровню
            return ptr;
        }
        ptr->level = lev;
        for (int i = 0; i < ptr->amount; i++)
            ptr->children.at(i) = addNodes(lev, ptr->children.at(i), ptr);
        return ptr;
    }
    // void setMinmax(node* pn, bool n)
    // {
    //     pn->minmax = n;
    //     if (pn == NULL)
    //         return;
    //     for (int i = 0; i < pn->amount; i++)
    //         setMinmax(pn->children.at(i), !n);
    // }
    void printLevel(void)
    {
        for (auto p : levels)
        {
            std::cout << "Level: " << p.first << "; ";
            std::cout << "Nodes: ";
            for (auto i : p.second)
                std::cout << i << "; ";
            std::cout << (minormax.at(p.first - 1) ? "MAX" : "MIN");
            std::cout << std::endl; 
        }
    }
    void makeMinmax(node* pn)
    {
        node* ptr;
        int value;
        if (!pn->amount)
        {
            ptr = pn->parent;
            if (direction)
                for (int i = 0, val = ptr->children.at(0)->data; i < ptr->amount-1; i++)
                {
                    switch (minormax.at(pn->level-1))
                    {
                    case true:
                        if (ptr->children.at(i+1)->data > val)
                            val = ptr->children.at(i+1)->data;
                        break;
                    case false:
                        if (ptr->children.at(i+1)->data < val)
                            val = ptr->children.at(i+1)->data;
                    }
                    value = val;    
                }
            else
                for (int i = ptr->amount, val = ptr->children.back()->data; i > 0; i--)
                {
                    switch (minormax.at(pn->level-1))
                    {
                    case true:
                        if (ptr->children.at(i-1)->data > val)
                            val = ptr->children.at(i-1)->data;
                        break;
                    case false:
                        if (ptr->children.at(i-1)->data < val)
                            val = ptr->children.at(i-1)->data;
                    }
                    value = val; 
                }
            std::cout << "Returned value from level " << pn->level << " is " << value << std::endl;
            ptr->data = value;
            result = value;
            ptr->amount = 0;
            return;
        }
        if (direction)
            for (int i = 0; i < pn->amount; i++)
                makeMinmax(pn->children.at(i));
        else
            for (int i = pn->amount - 1; i >= 0; i--)
                makeMinmax(pn->children.at(i));
    }
    void delTree(node* pn)
    {
        for (int i = 0; i < pn->amount; i++)
            if(pn->children.at(i))
                delTree(pn->children.at(i));
        delete pn;
    }
public:
    tree(int N)
    {
        deepestLevel = N + 1;
        minormax.resize(N + 1);
        pn = nullptr;
    }	
    ~tree()
    {
        delTree(pn); 
    }
    void addLevel(int x)
    {
        pn = addNodes(x, pn, pn);
        pn->level++;
        nodes.clear(); //очищение вектора узлов уровня
    }
    void levelMinmaxAndDirection(short minmax, short dir)
    {
        direction = dir;
        for (int i = 0; i < deepestLevel; i++)
        {
            minormax.at(i) = minmax;
            minmax = !minmax;
        }
        //setMinmax(pn, minmax);
    }
    void runMinmax()
    {
        while (pn->amount)
            makeMinmax(pn);
        std::cout << "Result (root value): " << result << std::endl;
    }
    void printTree()
    {
        printLevel();
    }
    void printLeaves()
    {
        std::cout << "Leaves: ";
        for (auto i : levels[deepestLevel])
            std::cout << i << "; ";
        std::cout << std::endl;
    }
};
