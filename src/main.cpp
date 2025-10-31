#include "array.h"
#include "figure.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"

int main() {
    Array<std::shared_ptr<Figure<int>>> figures;

    auto tri = std::make_shared<Triangle<int>>();
    std::cin >> *tri;
    figures.PushItem(tri);

    auto sq = std::make_shared<Square<int>>();
    std::cin >> *sq;
    figures.PushItem(sq);

    auto rect = std::make_shared<Rectangle<int>>();
    std::cin >> *rect;
    figures.PushItem(rect);

    std::cout << "Все фигуры:" << std::endl;
    figures.PrintFigures();

    std::cout << "Общая площадь: " << figures.TotalArea() << std::endl;

    figures.DeleteFigure(0);

    std::cout << "После удаления:" << std::endl;
    figures.PrintFigures();

   
    Array<Square<int>> squares;

    Square<int> sq1;
    std::cin >> sq1;
    squares.PushItem(sq1);

    Square<int> sq2;
    std::cin >> sq2;
    squares.PushItem(std::move(sq2));

    std::cout << "Квадраты:" << std::endl;
    squares.PrintFigures();

    std::cout << "Общая площадь квадратов: " << squares.TotalArea() << std::endl;

    squares.DeleteFigure(0);

    std::cout << "После удаления квадрата:" << std::endl;
    squares.PrintFigures();

    return 0;
}