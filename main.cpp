/*
 * Юревич В.Ю. М8О-207Б-19
 * Вариант 13
 * Разработать шаблоны классов согласно варианту задания.
 * Параметром шаблона должен являться скалярный тип данных
 * задающий тип данных для оси координат. Классы должны иметь
 * только публичные поля. В классах не должно быть методов,
 * только поля. Фигуры являются фигурами вращения
 * (равнобедренными), за исключением трапеции и прямоугольника.
 * Для хранения координат фигур необходимо использовать
 * шаблон std::pair.
 * Необходимо реализовать две шаблонные функции:
 * - Функция print печати фигур на экран std::cout (печататься
 *   должны координаты вершин фигур). Функция должна принимать на
 *   вход std::tuple с фигурами, согласно варианту задания(минимум
 *   по одной каждого класса).                                                                           
 * - Функция square вычисления суммарной площади фигур.
 *   Функция должна принимать на вход std::tuple с фигурами,
 *   согласно варианту задания (минимум по одной каждого класса)
 * Создать программу, которая позволяет:
 * - Создает набор фигур согласно варианту задания (как минимум
 *   по одной фигуре каждого типа с координатами типа int
 *   и координатами типа double).
 * - Сохраняет фигуры в std::tuple
 * - Печатает на экран содержимое std::tuple с помощью
 *   шаблонной функции print.
 * - Вычисляет суммарную площадь фигур в std::tuple и
 *   выводит значение на экран.
 * При реализации шаблонных функций допускается использование
 * вспомогательных шаблонов std::enable_if, std::tuple_size,
 * std::is_same.
 * Ромб, пятиугольник, шестиугольник.
 */

#include <iostream>
#include <utility>
#include <cmath>
#include <tuple>

template <class T>
struct TRhombus {
    using type = T;
    T verticalDiag;
    T horisontalDiag;
    std::pair<T, T> center;
};

template <class T>
struct TPentagone {
    using type = T;
    T side;
    std::pair<T, T> center;
};

template <class T>
struct THexagone {
    using type = T;
    T radius;
    std::pair<T, T> center;
};

template <class T, size_t index> 
typename std::enable_if<(index >= std::tuple_size<T>::value), void>::type PrintTuple(T&) {
    std::cout << std::endl;
}

template <class T, size_t index>
typename std::enable_if<(index < std::tuple_size<T>::value), void>::type PrintTuple(T& tuple) {
    auto fig = std::get<index>(tuple);
    Print(fig);
    PrintTuple<T, index+1>(tuple);
}

template <class T>
typename std::enable_if<(sizeof(T::verticalDiag) > 0), void>::type Print(T& rhombus) {
    std::cout << "(" << rhombus.center.first << ";" << (rhombus.center.second + rhombus.verticalDiag / 2) << ") ";
    std::cout << "(" << (rhombus.center.first + rhombus.horisontalDiag / 2)  << ";" << rhombus.center.second << ") ";
    std::cout << "(" << rhombus.center.first << ";" << (rhombus.center.second - rhombus.verticalDiag / 2) << ") ";
    std::cout << "(" << (rhombus.center.first - rhombus.horisontalDiag / 2) << ";" << rhombus.center.second << ")";
    std::cout << std::endl;
}

template <class T>
typename std::enable_if<(sizeof(T::side) > 0), void>::type Print(T& pentagone) {
    auto radius = static_cast<typename T::type>(pentagone.side * sqrt(2) / sqrt(5 - sqrt(5)));
    std::cout << "(" << pentagone.center.first << ";" << (pentagone.center.second + radius) << ") ";
    std::cout << "(" << (pentagone.center.first + radius) << ";" << pentagone.center.second << ") ";
    std::cout << "(" << (pentagone.center.first + pentagone.side / 2) << ";" << (pentagone.center.second - radius) << ") ";
    std::cout << "(" << (pentagone.center.first - pentagone.side / 2) << ";" << (pentagone.center.second - radius) << ") ";
    std::cout << "(" << (pentagone.center.first - radius / 2) << ";" << pentagone.center.second << ") ";
    std::cout << std::endl;
}

template <class T>
typename std::enable_if<(sizeof(T::radius) > 0), void>::type Print(T& hexagone) {
    auto s = static_cast<typename T::type>(sqrt(3) * hexagone.radius / 2);
    std::cout << "(" << (hexagone.center.first - hexagone.radius / 2) << ";" << (hexagone.center.second + s) << ") ";
    std::cout << "(" << (hexagone.center.first + hexagone.radius / 2) << ";" << (hexagone.center.second + s) << ") ";
    std::cout << "(" << (hexagone.center.first + hexagone.radius) << ";" << hexagone.center.second << ") ";
    std::cout << "(" << (hexagone.center.first + hexagone.radius / 2) << ";" << (hexagone.center.second - s) << ") ";
    std::cout << "(" << (hexagone.center.first - hexagone.radius / 2) << ";" << (hexagone.center.second - s) << ") ";
    std::cout << "(" << (hexagone.center.first - hexagone.radius) << ";" << hexagone.center.second << ") ";
    std::cout << std::endl;
}

template <class T>
typename std::enable_if<(sizeof(T::verticalDiag) > 0) , typename T::type>::type Square(T& rhombus){
    return static_cast<typename T::type>(rhombus.verticalDiag * rhombus.horisontalDiag / 2);
}

template <class T>
typename std::enable_if<(sizeof(T::side) > 0) , typename T::type>::type Square(T& pentagone){
    return static_cast<typename T::type>(pow(pentagone.side, 2) * sqrt(5) * sqrt(5 + 2 * sqrt(5)) / 4);
}

template <class T>
typename std::enable_if<(sizeof(T::radius) > 0) , typename T::type>::type Square(T& hexagone){
    return static_cast<typename T::type>(3 * sqrt(3) * pow(hexagone.radius, 2) / 2);
}

template <class T, size_t index>
typename std::enable_if<(index >= std::tuple_size<T>::value), double>::type TupleSquare(T& tuple) {
    return 0.0;
}

template <class T, size_t index>
typename std::enable_if<(index < std::tuple_size<T>::value), double>::type TupleSquare(T& tuple) {
    auto fig = std::get<index>(tuple);
    double value = Square(fig) + TupleSquare<T, index + 1>(tuple);
    return value;
}

int main() {
    TRhombus<int> rhI;
    rhI.center = {4, 8};
    rhI.verticalDiag = 1;
    rhI.horisontalDiag = 3;

    TPentagone<int> pentI;
    pentI.center = {-12, 0};
    pentI.side = 44;

    THexagone<int> hexI;
    hexI.center = {7, 2};
    hexI.radius = 5;

    TRhombus<double> rhD;
    rhD.center = {-1.2, -4.1};
    rhD.verticalDiag = 4.05;
    rhD.horisontalDiag = 8.01;

    TPentagone<double> pentD;
    pentD.center = {0.0 , -1.0};
    pentD.side = 10.345;

    THexagone<double> hexD;
    hexD.center = {-144.078, 48.009};
    hexD.radius = 314.5699;


    std::tuple <decltype(rhI), decltype(pentI), decltype(hexI), decltype(rhD), decltype(pentD), decltype(hexD)> tuple {rhI, pentI, hexI, rhD, pentD, hexD};
    PrintTuple<decltype(tuple), 0>(tuple);

    std::cout << "Площадь: " << TupleSquare<decltype(tuple),0>(tuple) << std::endl;
    return(0);
}