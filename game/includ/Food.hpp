#ifndef FOOD_HPP_SENTRY
#define FOOD_HPP_SENTRY

#include "MoveAndPosition.hpp"

/**
 * @brief Класс, представляющий еду на игровом поле.
 */
class Food : public Position
{
public:
    /**
     * @brief Конструктор класса Food.
     * @param x Координата x еды.
     * @param y Координата y еды.
     */
    Food(int x, int y) : Position(x, y) {}
    /**
     * @brief Виртуальный деструктор класса Food.
     */
    virtual ~Food() {}
};

#endif
