#include <iostream>
#include "DynamicArray.h"

int main() {
    DynamicArray da1(3, 0, 10);
    std::cin >> da1;
    std::cout << "da1: " << da1 << "\n";

    // копируем
    DynamicArray da2(da1);
    std::cout << "da2: " << da2 << "\n";

    // проверяем ==
    if (!(da1 == da2 && da1 <= da2 && da2 >= da1)) {
        std::cout << "Error1 - da1 == da2" << "\n";
    }
    // проверяем !=
    if (da1 != da2) std::cout << "Error2 - da1 != da2" << "\n";

    // увеличиваем размерность da2
    da2.resize(da2.getSize() + 2);
    std::cout << "da2: " << da2 << "\n";
    // размер матриц разный - ожидаем прерывание
    try {
        (da1 == da2);
        std::cout << "Error3 - da1 == da2 ???";
    } catch (int e) {
        //
    }
    if (da1 > da2) {
        std::cout << "Error4 - da1 > da2" << "\n";
    }

    // возвращаем размерность
    da2.resize(da1.getSize());
    // объекты опять равны
    if (!(da1 == da2)) std::cout << "Error5 - da1 == da2" << "\n";

    // увеличиваем размерность da1, da2
    da1.pushBack(24);
    da2.pushBack(22);
    if (da1 > da2) {
        std::cout << "Error6 - da1 > da2" << "\n";
    }
    if (da2.popBack() != 22) std::cout << "Error7\n";
    if (da1.getSize() != da2.getSize() + 1) std::cout << "Error8\n";
    if (da1.popBack() != 24) std::cout << "Error9\n";

	std::cin.get();
	return 0;
}
