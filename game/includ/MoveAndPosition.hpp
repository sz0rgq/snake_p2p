#ifndef MOVEANDPOSITION_HPP_SENTRY
#define MOVEANDPOSITION_HPP_SENTRY

#include "Point.hpp"

/**
 * @brief Класс вектора движения.
 * 
 * Этот класс наследуется от класса Point и добавляет функциональность для представления вектора движения.
 */
class MoveVector : public Point
{
public:
    /**
     * @brief Конструктор вектора движения.
     * 
     * @param x Координата x вектора движения.
     * @param y Координата y вектора движения.
     */
    MoveVector(int x, int y) : Point(x, y) {}

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~MoveVector() {}
};

/**
 * @brief Класс позиции.
 * 
 * Этот класс наследуется от класса Point и добавляет функциональность для представления позиции.
 */
class Position : public Point
{
public:
    /**
     * @brief Конструктор позиции.
     * 
     * @param x Координата x позиции.
     * @param y Координата y позиции.
     */
    Position(int x, int y) : Point(x, y) {}

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Position() {}
};

#endif
