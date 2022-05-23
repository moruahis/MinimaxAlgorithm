#include "tree.h"

main()
{
    int  i, N;

    std::cout << "Enter the amount of levels (except the root): ";
    std::cin >> N;
    tree t(N);
    for (i = 0; i <= N; i++)
        t.addLevel(i);
    std::cout << std::endl;
    //t.printTree(); 
    t.printLeaves();

    /***Ввод данных для минимаксной процедуры: начальный ход и направление проверки***/
    short minmax = 2, direction = 2;
    std::cout << "Choose the direction (1 - left-to-right, 0 - right-to-left): ";
    while (direction != 1 && direction != 0)
    {
        std::cin >> direction;
        if (direction != 1 && direction != 0)
            std::cout << "Try again." << std::endl;
    }
    std::cout << "Chosen one: " << (direction ? "left-to-right" : "right-to-left") << std::endl;

    std::cout << "Choose the first step (1 - MAX, 0 - MIN): ";
    while (minmax != 1 && minmax != 0)
    {
        std::cin >> minmax;
        if (minmax != 1 && minmax != 0)
            std::cout << "Try again." << std::endl;
    }
    std::cout << "Chosen one: " << (minmax ? "MAX" : "MIN") << std::endl;
    
    t.levelMinmaxAndDirection(minmax, direction);
    t.printTree();
    t.runMinmax();

    system("pause");
    return 0;
}
