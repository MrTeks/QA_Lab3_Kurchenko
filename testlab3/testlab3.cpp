#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

/**
 * @class spice
 * @brief Класс для представления специи/добавки к блюду
 *
 * Класс spice хранит информацию о стоимости специи и её количестве.
 * Позволяет рассчитать общую стоимость специи для блюда.
 *
 * Формула расчета стоимости специи:
 * \f[
 * C_{spice} = p \times n
 * \f]
 * где:
 * - p - стоимость за грамм
 * - n - количество грамм на кг
 *
 */
class spice
{
public:
    /**
     * @brief Инициализация специи с заданными параметрами
     * @param cost Стоимость за грамм
     * @param grams Количество грамм на кг
     */
    void init(double cost, int grams);

    /**
     * @brief Ввод данных о специи с клавиатуры
     */
    void read();

    /**
     * @brief Вывод информации о специи на экран
     */
    void display();

    /**
     * @brief Расчет общей стоимости специи
     * @return Стоимость специи
     *
     * Рассчитывает стоимость по формуле: cost_per_gram * grams_per_kg
     */
    double calculate_cost();

private:
    double cost_per_gram;  ///< Стоимость за грамм в рублях
    int grams_per_kg;      ///< Количество грамм на 1 кг блюда
};

/**
 * @class dish
 * @brief Класс для представления блюда с добавками
 *
 * Класс dish содержит основную информацию о блюде и трех добавках.
 * Позволяет рассчитать общую стоимость блюда с учетом всех компонентов.
 *
 * Общая стоимость рассчитывается по формуле:
 * \f[
 * C_{total} = W \times C_{base} + W \times \sum_{i=1}^{3} C_{spice_i}
 * \f]
 *
 * @dot
 * digraph Hierarchy {
 *   node [shape=box];
 *   dish -> spice [label="содержит"];
 *   spice [label="spice\n(базовый класс)"];
 * }
 * @enddot
 */
class dish
{
public:
    /**
     * @brief Инициализация блюда с заданными параметрами
     * @param name Название блюда
     * @param w Вес блюда в кг
     * @param cost Стоимость основы (руб/кг)
     * @param s1 Первая добавка
     * @param s2 Вторая добавка
     * @param s3 Третья добавка
     */
    void init(char* name, double w, double cost, spice s1, spice s2, spice s3);

    /**
     * @brief Ввод данных о блюде с клавиатуры
     */
    void read();

    /**
     * @brief Вывод информации о блюде на экран
     */
    void display();

    /**
     * @brief Расчет общей стоимости блюда
     * @return Полная стоимость блюда
     *
     * Суммирует стоимость основы и всех добавок
     */
    double calculate_total_cost();

    /**
     * @brief Нахождение самой дешевой добавки
     * @return Объект spice с наименьшей стоимостью
     */
    spice get_cheapest_spice();

private:
    char name[50];     ///< Название блюда
    double weight;      ///< Вес блюда в кг
    double base_cost;   ///< Стоимость основы (руб/кг)
    spice spice1;       ///< Первая добавка
    spice spice2;       ///< Вторая добавка
    spice spice3;       ///< Третья добавка
};

void spice::init(double cost, int grams)
{
    cost_per_gram = cost;
    grams_per_kg = grams;
}

void spice::read()
{
    cout << "Стоимость 1 грамма: ";
    cin >> cost_per_gram;

    cout << "Грамм на 1 кг: ";
    cin >> grams_per_kg;
}

void spice::display()
{
    cout << cost_per_gram << " руб/гр, " << grams_per_kg << " гр/кг" << endl;
    cout << "Стоимость: " << calculate_cost() << " руб" << endl;
}

double spice::calculate_cost()
{
    // Проверка на отрицательные значения
    if (cost_per_gram < 0 || grams_per_kg < 0)
        return 0;
    return cost_per_gram * grams_per_kg;
}

void dish::init(char* dish_name, double w, double cost, spice s1, spice s2, spice s3)
{
    strcpy_s(name, dish_name);
    weight = w;
    base_cost = cost;
    spice1 = s1;
    spice2 = s2;
    spice3 = s3;
}

void dish::read()
{
    cout << "Название блюда: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Вес (кг): ";
    cin >> weight;

    cout << "Стоимость основы (руб/кг): ";
    cin >> base_cost;

    cout << "Добавка 1:" << endl;
    spice1.read();

    cout << "Добавка 2:" << endl;
    spice2.read();

    cout << "Добавка 3:" << endl;
    spice3.read();
}

void dish::display()
{
    cout << "Блюдо: " << name << endl;
    cout << "Вес: " << weight << " кг" << endl;
    cout << "Основа: " << base_cost << " руб/кг" << endl;

    cout << "Добавка 1: ";
    spice1.display();

    cout << "Добавка 2: ";
    spice2.display();

    cout << "Добавка 3: ";
    spice3.display();

    cout << "Общая стоимость: " << calculate_total_cost() << " руб" << endl;

    spice cheap = get_cheapest_spice();
    cout << "Самая дешевая добавка: " << cheap.calculate_cost() << " руб" << endl;
}

double dish::calculate_total_cost()
{
    double spices_cost = (spice1.calculate_cost() + spice2.calculate_cost() + spice3.calculate_cost()) * weight;
    double main_cost = base_cost * weight;
    return spices_cost + main_cost;
}

spice dish::get_cheapest_spice()
{
    double cost1 = spice1.calculate_cost();
    double cost2 = spice2.calculate_cost();
    double cost3 = spice3.calculate_cost();

    if (cost1 <= cost2 && cost1 <= cost3)
        return spice1;
    else if (cost2 <= cost1 && cost2 <= cost3)
        return spice2;
    else
        return spice3;
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Расчет стоимости блюда" << endl;
    dish my_dish;
    my_dish.read();

    cout << endl << "Результаты:" << endl;
    my_dish.display();
}