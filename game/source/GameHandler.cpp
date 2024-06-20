#include <stdlib.h>

#include "../includ/GameHandler.hpp"



/**
 * @brief Проверяет, столкнулась ли змея сама с собой.
 *
 * Эта функция определяет, столкнулась ли указанная змея сама с собой,
 * проверяя, совпадает ли позиция головы змеи с любой позицией её тела.
 *
 * @param s Указатель на объект Snake, который нужно проверить на столкновение с собой.
 * @return true если змея столкнулась сама с собой, иначе false.
 */
bool GameHandler::IsSnake(Snake *s)
{
    if (s->GetLen() == 1)
        return false; // Змея не может столкнуться сама с собой, если её длина 1
    Snake::item *head = s->last; // Голова змеи
    Snake::item *p;
    for (p = s->first; p != head; p = p->next)
    {
        if (head->pos == p->pos) // Проверка на совпадение позиции головы с телом
            return true; // Столкновение произошло
    }
    return false; // Столкновения нет
}

/**
 * @brief Проверяет, съела ли змея еду.
 *
 * Эта функция определяет, съела ли указанная змея еду, проверяя, совпадает ли позиция головы змеи с любой позицией еды.
 * Если змея съела еду, функция удаляет её из списка еды, добавляет новую еду и возвращает true.
 *
 * @param s Указатель на объект Snake, который нужно проверить на поедание еды.
 * @return true если змея съела еду, иначе false.
 */
bool GameHandler::IsFood(Snake *s)
{
    List<Food>::Iterator *it = foods->Iterate(); // Итератор по списку еды
    while (it->More())
    {
        ListCursor<Food> cr(it->Next());
        if (*cr == s->last->pos) // Проверка на совпадение позиции головы змеи с едой
        {
            s->Eat(&(*cr)); // Змея съедает еду
            foods->Remove(&cr); // Удаление еды из списка
            AddFood(); // Добавление новой еды
            delete it;
            return true; // Еда была съедена
        }
    }
    delete it;
    return false; // Еда не найдена
}


/**
 * @brief Обрабатывает ситуацию выхода змеи за пределы поля.
 *
 * Эта функция проверяет, вышла ли голова змеи за пределы игрового поля,
 * и при необходимости перемещает её на противоположную сторону поля.
 *
 * @param s Указатель на объект Snake, который нужно проверить и обработать.
 */
void GameHandler::HandleOutOfField(Snake *s)
{
    int max_x = field->GetSizeX(); // Максимальный размер поля по X
    int max_y = field->GetSizeY(); // Максимальный размер поля по Y
    if (s->last->pos.GetX() >= max_x)
        s->last->pos.SetX(0); // Перенос головы змеи на противоположную сторону по X
    if (s->last->pos.GetY() >= max_y)
        s->last->pos.SetY(0); // Перенос головы змеи на противоположную сторону по Y
    if (s->last->pos.GetX() < 0)
        s->last->pos.SetX(max_x - 1); // Перенос головы змеи на противоположную сторону по X
    if (s->last->pos.GetY() < 0)
        s->last->pos.SetY(max_y - 1); // Перенос головы змеи на противоположную сторону по Y
}

/**
 * @brief Добавляет новую еду на поле.
 *
 * Эта функция добавляет новую еду в случайной позиции на игровом поле.
 */
void GameHandler::AddFood()
{
    int x = field->GetSizeX(); // Получение размеров поля по X
    int y = field->GetSizeY(); // Получение размеров поля по Y
    foods->Push(new Food(rand() % x, rand() % y)); // Добавление новой еды в случайной позиции
}

/**
 * @brief Проверяет, столкнулась ли змея с другой змеёй.
 *
 * Эта функция проверяет, столкнулась ли указанная змея с любой другой змеёй на поле.
 * В случае столкновения возвращает указатель на другую змею.
 *
 * @param s Указатель на объект Snake, который нужно проверить на столкновение.
 * @param other_snake Указатель на указатель другой змеи, с которой произошло столкновение.
 * @return true если произошло столкновение с другой змеёй, иначе false.
 */
bool GameHandler::IsOtherSnake(Snake *s, Snake **other_snake)
{
    List<Snake>::Iterator *it = snakes->Iterate(); // Итератор по списку змей
    Snake::item *head = s->last; // Голова змеи

    while (it->More())
    {
        ListCursor<Snake> cr = it->Next();
        if (s != &(*cr)) // Исключаем саму змею s
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

/**
 * @brief Удаляет змею из списка змей.
 *
 * Эта функция удаляет указанную змею из списка змей.
 *
 * @param s Указатель на объект Snake, который нужно удалить.
 */
void GameHandler::RemoveSnake(Snake *s)
{
    List<Snake>::Iterator *it = snakes->Iterate(); // Итератор по списку змей
    ListCursor<Snake> sn_c;
    while (it->More())
    {
        sn_c = it->Next();
        if (&(*sn_c) == s)
        {
            snakes->Remove(&sn_c); // Удаление змеи из списка
            break;
        }
    }
    delete it;
}

/**
 * @brief Добавляет змею в список змей.
 *
 * Эта функция добавляет указанную змею в список змей.
 *
 * @param s Указатель на объект Snake, который нужно добавить.
 */
void GameHandler::AddSnake(Snake *s)
{
    snakes->Push(s); // Добавление змеи в список
}

/**
 * @brief Рисует игровое поле.
 *
 * Эта функция рисует игровое поле, включая границы, еду и змей.
 */
void GameHandler::DrawField()
{
    int x = field->GetSizeX() + 1; // Ширина поля с учетом границы
    int y = field->GetSizeY(); // Высота поля
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
        field->field[i * x + j] = '\n'; // Конец строки
    }

    // Отмечаем конец строки в массиве field
    field->field[field->full_len - 1] = 0;

    // Размещаем еду на поле
    List<Food>::Iterator *it_food = foods->Iterate(); // Итератор по списку еды
    while (it_food->More())
    {
        ListCursor<Food> cr_food = it_food->Next();
        field->field[cr_food->GetX() + cr_food->GetY() * x] = '*'; // Размещение еды

    }
    delete it_food;

    // Размещаем змей на поле
    List<Snake>::Iterator *it_snake = snakes->Iterate(); // Итератор по списку змей
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        Snake::item *p = cr_snake->first;
        while (p)
        {
            field->field[p->pos.GetX() + p->pos.GetY() * x] = '#'; // Размещение змеи
            p = p->next;
        }
    }
    delete it_snake;
}

/**
 * @brief Рисует головы змей на поле.
 *
 * Эта функция рисует головы змей на игровом поле, обозначая текущую змею '@' и других змей '%'.
 *
 * @param s Указатель на текущую змею, для которой нужно нарисовать голову.
 */
void GameHandler::DrawFieldFor(const Snake *s)
{
    int x = field->GetSizeX() + 1;
    List<Snake>::Iterator *it_snake = snakes->Iterate(); // Итератор по списку змей
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        if (&(*cr_snake) == s)
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '@'; // Голова текущей змеи
        else
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '%'; // Голова другой змеи
    }
    delete it_snake;
}


/////////////////////////

// Обертка для использования GameHandler в других классах
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
    return FoodHandler(handler); // Преобразование в FoodHandler
}
GameHandlerGemstone::operator FieldHandler()
{
    return FieldHandler(handler); // Преобразование в FieldHandler
}
GameHandlerGemstone::operator SnakeHandler()
{
    return SnakeHandler(handler); // Преобразование в SnakeHandler
}
GameHandlerGemstone::operator DrawHandler()
{
    return DrawHandler(handler); // Преобразование в DrawHandler
}

/////////////////////////

FoodHandler::FoodHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Добавление еды на поле.
 */
void FoodHandler::AddFood()
{
    handler->AddFood(); // Вызов соответствующего метода GameHandler
}

/////////////////////////

FieldHandler::FieldHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Обработка выхода змеи за пределы поля.
 * @param s Змея.
 */
void FieldHandler::HandleOutOfField(Snake *s)
{
    handler->HandleOutOfField(s); // Вызов соответствующего метода GameHandler
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
    return handler->IsSnake(s); // Вызов соответствующего метода GameHandler
}

/**
 * @brief Проверка на столкновение змеи с едой.
 * @param s Змея.
 * @return true, если столкновение произошло.
 */
bool SnakeHandler::IsFood(Snake *s)
{
    return handler->IsFood(s); // Вызов соответствующего метода GameHandler
}

/**
 * @brief Проверка на столкновение змеи с другой змеей.
 * @param s Змея.
 * @param other_snake Указатель на другую змею.
 * @return true, если столкновение произошло.
 */
bool SnakeHandler::IsOtherSnake(Snake *s, Snake **other_snake)
{
    return handler->IsOtherSnake(s, other_snake); // Вызов соответствующего метода GameHandler
}

/**
 * @brief Удаление змеи из списка змей.
 * @param s Змея.
 */
void SnakeHandler::RemoveSnake(Snake *s)
{
    handler->RemoveSnake(s); // Вызов соответствующего метода GameHandler
}

/**
 * @brief Добавление змеи в список змей.
 * @param s Змея.
 */
void SnakeHandler::AddSnake(Snake *s)
{
    handler->AddSnake(s); // Вызов соответствующего метода GameHandler
}

/////////////////////////

DrawHandler::DrawHandler(GameHandler *_handler) : handler(_handler) {}

/**
 * @brief Отрисовка поля.
 */
void DrawHandler::DrawField()
{
    handler->DrawField(); // Вызов соответствующего метода GameHandler
}

/**
 * @brief Отрисовка поля для конкретной змеи.
 * @param s Змея.
 */
void DrawHandler::DrawFieldFor(const Snake *s)
{
    handler->DrawFieldFor(s); // Вызов соответствующего метода GameHandler
}

/////////////////////////
