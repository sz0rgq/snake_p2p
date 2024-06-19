#include <stdlib.h>

#include "../includ/GameHandler.hpp"

/**
 * @class GameHandler
 * @brief  GameHandler класс реализует основную логику игры
 */

class GameHandler
{
    Field *field;
    List<Food> *foods;
    List<Snake> *snakes;

public:
    /**
     * @brief Конструктор класса GameHandler.
     * @param _field Поле игры.
     * @param _foods Список еды.
     * @param _snakes Список змей.
     */
    GameHandler(Field *_field, List<Food> *_foods, List<Snake> *_snakes)
        : field(_field), foods(_foods), snakes(_snakes) {}
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
     * @param to Элемент, до которого обреза змею.
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

bool GameHandler::IsSnake(Snake *s)
{
    if (s->GetLen() == 1)
        return false;
    Snake::item *head = s->last;
    Snake::item *p;
    for (p = s->first; p != head; p = p->next)
    {
        if (head->pos == p->pos)
            return true;
    }
    return false;
}

bool GameHandler::IsFood(Snake *s)
{
    List<Food>::Iterator *it = foods->Iterate();
    while (it->More())
    {
        ListCursor<Food> cr(it->Next());
        if (*cr == s->last->pos)
        {
            s->Eat(&(*cr));
            foods->Remove(&cr);
            AddFood();
            delete it;
            return true;
        }
    }
    delete it;
    return false;
}

void GameHandler::HandleOutOfField(Snake *s)
{
    int max_x = field->GetSizeX();
    int max_y = field->GetSizeY();
    if (s->last->pos.GetX() >= max_x)
        s->last->pos.SetX(0);
    if (s->last->pos.GetY() >= max_y)
        s->last->pos.SetY(0);
    if (s->last->pos.GetX() < 0)
        s->last->pos.SetX(max_x - 1);
    if (s->last->pos.GetY() < 0)
        s->last->pos.SetY(max_y - 1);
}

void GameHandler::AddFood()
{
    int x = field->GetSizeX();
    int y = field->GetSizeY();
    foods->Push(new Food(rand() % x, rand() % y));
}

bool GameHandler::IsOtherSnake(Snake *s, Snake **other_snake)
{
    List<Snake>::Iterator *it = snakes->Iterate();
    Snake::item *head = s->last;

    while (it->More())
    {
        ListCursor<Snake> cr(it->Next());
        if (s != &(*cr))
        {
            if (cr->last->pos == head->pos)
            {
                // Столкновение голов
                if (s->GetLen() < cr->GetLen())
                {
                    // Змея s проигрывает
                    *other_snake = &(*cr);
                    delete it;
                    return true;
                }
                else
                {
                    // Змея cr проигрывает
                    *other_snake = &(*cr);
                    delete it;
                    return true;
                }
            }
            Snake::item *second_snake_start = cr->first;
            while (second_snake_start != cr->last)
            {
                if (head->pos == second_snake_start->pos)
                {
                    // Змея s врезалась в тело змеи cr
                    *other_snake = 0;
                    delete it;
                    return true;
                }
                second_snake_start = second_snake_start->next;
            }
        }
    }

    delete it;
    *other_snake = 0;
    return false;
}


void GameHandler::SnakeTruncate(Snake *s, Snake::item *to)
{
    Snake::item *p = s->first;
    while (p != to)
    {
        Snake::item *tmp = p->next;
        delete p;
        s->len--;
        p = tmp;
    }
    s->first = p;
}

void GameHandler::RemoveSnake(Snake *s)
{
    List<Snake>::Iterator *it = snakes->Iterate();
    ListCursor<Snake> sn_c;
    while (it->More())
    {
        sn_c = it->Next();
        if (&(*sn_c) == s)
        {
            snakes->Remove(&sn_c);
            break;
        }
    }
    delete it;
}

void GameHandler::AddSnake(Snake *s)
{
    snakes->Push(s);
}

void GameHandler::DrawField()
{

    int x = field->GetSizeX() + 1;
    int y = field->GetSizeY();
    int i, j;

    // Рисуем поле с рамкой
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x - 1; j++)
        {
            // Рисуем рамку
            if (i == 0 || i == y - 1) // Верхняя и нижняя границы
            {
                field->field[i * x + j] = '=';
            }
            else if (j == 0 || j == x - 2) // Левая и правая границы
            {
                field->field[i * x + j] = '|';
            }
            else
            {
                field->field[i * x + j] = ' ';
            }
        }
        field->field[i * x + j] = '\n';
    }

    // Отмечаем конец строки в массиве field
    field->field[field->full_len - 1] = 0;

    // Размещаем еду на поле
    List<Food>::Iterator *it_food = foods->Iterate();
    while (it_food->More())
    {
        ListCursor<Food> cr_food = it_food->Next();
        field->field[cr_food->GetX() + cr_food->GetY() * x] = '*';

    }
    delete it_food;

    // Размещаем змей на поле
    List<Snake>::Iterator *it_snake = snakes->Iterate();
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        Snake::item *p = cr_snake->first;
        while (p)
        {
            field->field[p->pos.GetX() + p->pos.GetY() * x] = '#';
            p = p->next;
        }
    }
    delete it_snake;
}


void GameHandler::DrawFieldFor(const Snake *s)
{
    int x = field->GetSizeX() + 1;
    List<Snake>::Iterator *it_snake = snakes->Iterate();
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        if (&(*cr_snake) == s)
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '@';
        else
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '%';
    }
    delete it_snake;
}

/////////////////////////

GameHandlerGemstone::
    GameHandlerGemstone(Field *_field,
                        List<Food> *_foods, List<Snake> *_snakes)
    : handler(new GameHandler(_field, _foods, _snakes)) {}
/**
 * @brief Деструктор класса GameHandlerGemstone.
 */
GameHandlerGemstone::~GameHandlerGemstone() { delete handler; }

GameHandlerGemstone::operator FoodHandler()
{
    return FoodHandler(handler);
}
GameHandlerGemstone::operator FieldHandler()
{
    return FieldHandler(handler);
}
GameHandlerGemstone::operator SnakeHandler()
{
    return SnakeHandler(handler);
}
GameHandlerGemstone::operator DrawHandler()
{
    return DrawHandler(handler);
}

/////////////////////////

FoodHandler::FoodHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Добавление еды на поле.
 */
void FoodHandler::AddFood()
{
    handler->AddFood();
}

/////////////////////////

FieldHandler::FieldHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Обработка выхода змеи за пределы поля.
 * @param s Змея.
 */
void FieldHandler::HandleOutOfField(Snake *s)
{
    handler->HandleOutOfField(s);
}

/////////////////////////

SnakeHandler::SnakeHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Проверка на столкновение змеи с самой собой.
 * @param s Змея.
 * @return true, если столкновение произошло.
 */
bool SnakeHandler::IsSnake(Snake *s)
{
    return handler->IsSnake(s);
}

/**
 * @brief Проверка на столкновение змеи с едой.
 * @param s Змея.
 * @return true, если столкновение произошло.
 */
bool SnakeHandler::IsFood(Snake *s)
{
    return handler->IsFood(s);
}

/**
 * @brief Проверка на столкновение змеи с другой змеей.
 * @param s Змея.
 * @param other_snake Указатель на другую змею.
 * @return true, если столкновение произошло.
 */
bool SnakeHandler::IsOtherSnake(Snake *s, Snake **other_snake)
{
    return handler->IsOtherSnake(s, other_snake);
}

/**
 * @brief Обрезка змеи до указанного элемента.
 * @param s Змея.
 * @param to Элемент, до которого обрезать змею.
 */
void SnakeHandler::SnakeTruncate(Snake *s, Snake::item *to)
{
    handler->SnakeTruncate(s, to);
}

/**
 * @brief Удаление змеи из списка змей.
 * @param s Змея.
 */
void SnakeHandler::RemoveSnake(Snake *s)
{
    handler->RemoveSnake(s);
}

/**
 * @brief Добавление змеи в список змей.
 * @param s Змея.
 */
void SnakeHandler::AddSnake(Snake *s)
{
    handler->AddSnake(s);
}

/////////////////////////

DrawHandler::DrawHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Отрисовка поля.
 */
void DrawHandler::DrawField()
{
    handler->DrawField();
}

/**
 * @brief Отрисовка поля для конкретной змеи.
 * @param s Змея.
 */
void DrawHandler::DrawFieldFor(const Snake *s)
{
    handler->DrawFieldFor(s);
}

/////////////////////////
