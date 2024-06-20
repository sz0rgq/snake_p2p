#ifndef POINT_HPP_SENTRY
#define POINT_HPP_SENTRY

/**
 * @brief Класс точки на плоскости.
 *
 * Этот класс представляет собой точку на плоскости с координатами x и y.
 */
class Point
{
    int pos_x; /**< Координата x точки. */
    int pos_y; /**< Координата y точки. */

public:
    /**
     * @brief Конструктор точки.
     *
     * @param _pos_x Координата x точки (по умолчанию 0).
     * @param _pos_y Координата y точки (по умолчанию 0).
     */
    Point(int _pos_x = 0, int _pos_y = 0) : pos_x(_pos_x), pos_y(_pos_y) {}

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Point() {}

    /**
     * @brief Получает координату x точки.
     *
     * @return Координата x точки.
     */
    int GetX() {
        if (pos_x < 0) {
            return 0;
        }
        return pos_x;
    }

    /**
     * @brief Получает координату y точки.
     *
     * @return Координата y точки.
     */
    int GetY() {
        if (pos_y < 0) {
            return 0;
        }
        return pos_y;
    }

    /**
     * @brief Устанавливает координату x точки.
     *
     * @param _pos_x Новая координата x точки.
     */
    void SetX(int _pos_x) {
        if (_pos_x > 0) {
            pos_x = _pos_x;
        }
        }

    /**
     * @brief Устанавливает координату y точки.
     *
     * @param _pos_y Новая координата y точки.
     */
    void SetY(int _pos_y) {
        if (_pos_y > 0) {
            pos_y = _pos_y;
        }
        }

    /**
     * @brief Оператор присваивания.
     *
     * @param a Точка, которая копируется.
     * @return Ссылка на текущую точку.
     */
    Point &operator=(const Point &a)
    {
        if (this != &a)
        {
            pos_x = a.pos_x;
            pos_y = a.pos_y;
        }
        return *this;
    }

    /**
     * @brief Оператор сравнения на равенство.
     *
     * @param a Точка, с которой сравнивается.
     * @return true, если точки равны, false - в противном случае.
     */
    bool operator==(const Point &a)
    {
        return pos_x == a.pos_x && pos_y == a.pos_y;
    }

    /**
     * @brief Оператор сложения с присваиванием.
     *
     * @param a Точка, которая добавляется к текущей.
     * @return Ссылка на текущую точку.
     */
    const Point &operator+=(const Point &a)
    {
        pos_x += a.pos_x;
        pos_y += a.pos_y;
        return *this;
    }

    /**
     * @brief Оператор вычитания с присваиванием.
     *
     * @param a Точка, которая вычитается из текущей.
     * @return Ссылка на текущую точку.
     */
    const Point &operator-=(const Point &a)
    {
        pos_x -= a.pos_x;
        pos_y -= a.pos_y;
        return *this;
    }

    /**
     * @brief Оператор сложения.
     *
     * @param a Точка, которая добавляется к текущей.
     * @return Новая точка, равная сумме текущей и добавляемой.
     */
    Point operator+(const Point &a)
    {
        return Point(a.pos_x + pos_x, a.pos_y + pos_y);
    }
};

#endif
