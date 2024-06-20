#ifndef GAMEHANDLER_HPP_SENTRY
#define GAMEHANDLER_HPP_SENTRY

#include "Snake.hpp"
#include "List.hpp"
#include "Food.hpp"

/**
 * @class GameHandler
 * @brief  GameHandler класс реализует основную логику игры
 */

class GameHandler
{
    Field *field; // Указатель на игровое поле
    List<Food> *foods; // Указатель на список еды
    List<Snake> *snakes; // Указатель на список змей

public:
    /**
     * @brief Конструктор класса GameHandler.
     * @param _field Поле игры.
     * @param _foods Список еды.
     * @param _snakes Список змей.
     */
    GameHandler(Field *_field, List<Food> *_foods, List<Snake> *_snakes)
        : field(_field), foods(_foods), snakes(_snakes) {} // Инициализация полей конструктора

    /**
     * @brief Деструктор класса GameHandler.
     */
    ~GameHandler() {}

    // SnakeHandler
    /**
     * @brief Проверка на столкновение змеи с самой собой.
     * @param s Змея.
     * @return true, если столкновение произошло.
     */
    bool IsSnake(Snake *s);
    /**
     * @brief Проверка на столкновение змеи с едой.
     * @param s Змея.
     * @return true, если столкновение произошло.
     */
    bool IsFood(Snake *s);
    /**
     * @brief Проверка на столкновение змеи с другой змеей.
     * @param s Змея.
     * @param other_snake Указатель на другую змею.
     * @return true, если столкновение произошло.
     */
    bool IsOtherSnake(Snake *s, Snake **other_snake);
    /**
     * @brief Обрезка змеи до указанного элемента.
     * @param s Змея.
     * @param to Элемент, до которого обрезать змею.
     */

    void RemoveSnake(Snake *s);
    /**
     * @brief Добавление змеи в список змей.
     * @param s Змея.
     */
    void AddSnake(Snake *s);

    // FoodHandler
    /**
     * @brief Добавление еды на поле.
     */
    void AddFood();

    // FieldHandler
    /**
     * @brief Обработка выхода змеи за пределы поля.
     * @param s Змея.
     */
    void HandleOutOfField(Snake *s);

    // DrawHandler
    /**
     * @brief Отрисовка поля.
     */
    void DrawField();
    /**
     * @brief Отрисовка поля для конкретной змеи.
     * @param s Змея.
     */
    void DrawFieldFor(const Snake *s);
};
class FoodHandler;
class FieldHandler;
class SnakeHandler;
class DrawHandler;

/**
 * @brief Класс, представляющий обработчик
 */
class GameHandlerGemstone
{
    GameHandler *handler; // Указатель на объект GameHandler

public:
    /**
     * @brief Конструктор класса GameHandlerGemstone.
     * @param _field Поле игры.
     * @param _foods Список еды.
     * @param _snakes Список змей.
     */
    GameHandlerGemstone(Field *_field,
                        List<Food> *_foods, List<Snake> *_snakes);
    /**
     * @brief Деструктор класса GameHandlerGemstone.
     */
    ~GameHandlerGemstone();

    /**
     * @brief Оператор преобразования в GameHandler.
     */
    operator GameHandler();
    /**
     * @brief Оператор преобразования в FoodHandler.
     */
    operator FoodHandler();
    /**
     * @brief Оператор преобразования в FieldHandler.
     */
    operator FieldHandler();
    /**
     * @brief Оператор преобразования в SnakeHandler.
     */
    operator SnakeHandler();
    /**
     * @brief Оператор преобразования в DrawHandler.
     */
    operator DrawHandler();
};

/**
 * @brief Класс, представляющий обработчик еды.
 */
class FoodHandler
{
    GameHandler *handler; // Указатель на объект GameHandler

public:
    /**
     * @brief Конструктор класса FoodHandler.
     * @param _handler Обработчик игры.
     */
    FoodHandler(GameHandler *_handler);
    /**
     * @brief Добавление еды на поле.
     */
    void AddFood();
};

/**
 * @brief Класс, представляющий обработчик поля.
 */
class FieldHandler
{
    GameHandler *handler; // Указатель на объект GameHandler

public:
    /**
     * @brief Конструктор класса FieldHandler.
     * @param _handler Обработчик игры.
     */
    FieldHandler(GameHandler *_handler);
    /**
     * @brief Обработка выхода змеи за пределы поля.
     * @param s Змея.
     */
    void HandleOutOfField(Snake *s);
};

/**
 * @brief Класс, представляющий обработчик змей.
 */
class SnakeHandler
{
    GameHandler *handler; // Указатель на объект GameHandler

public:
    /**
     * @brief Конструктор класса SnakeHandler.
     * @param _handler Обработчик игры.
     */
    SnakeHandler(GameHandler *_handler);
    /**
     * @brief Проверка на столкновение змеи с самой собой.
     * @param s Змея.
     * @return true, если столкновение произошло.
     */
    bool IsSnake(Snake *s);
    /**
     * @brief Проверка на столкновение змеи с едой.
     * @param s Змея.
     * @return true, если столкновение произошло.
     */
    bool IsFood(Snake *s);
    /**
     * @brief Проверка на столкновение змеи с другой змеей.
     * @param s Змея.
     * @param other_snake Указатель на другую змею.
     * @return true, если столкновение произошло.
     */
    bool IsOtherSnake(Snake *s, Snake **other_snake);
    /**
     * @brief Обрезка змеи до указанного элемента.
     * @param s Змея.
     * @param to Элемент, до которого обрезать змею.
     */
    void SnakeTruncate(Snake *s, Snake::item *to);
    /**
     * @brief Удаление змеи из списка змей.
     * @param s Змея.
     */
    void RemoveSnake(Snake *s);
    /**
     * @brief Добавление змеи в список змей.
     * @param s Змея.
     */
    void AddSnake(Snake *s);
};

/**
 * @brief Класс, представляющий обработчик отрисовки.
 */
class DrawHandler
{
    GameHandler *handler; // Указатель на объект GameHandler

public:
    /**
     * @brief Конструктор класса DrawHandler.
     * @param _handler Обработчик игры.
     */
    DrawHandler(GameHandler *_handler);
    /**
     * @brief Отрисовка поля.
     */
    void DrawField();
    /**
     * @brief Отрисовка поля для конкретной змеи.
     * @param s Змея.
     */
    void DrawFieldFor(const Snake *s);
};

#endif
