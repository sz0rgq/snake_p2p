#include <stdio.h>      // Для функций ввода-вывода
#include <time.h>       // Для работы с функцией time() и генерации случайных чисел
#include <stdlib.h>     // Для функций atoi(), srand(), rand()
#include <string.h>     // Для работы с функцией strcmp()

#include "../includ/Point.hpp"       // Включение заголовочного файла Point
#include "../includ/Field.hpp"       // Включение заголовочного файла Field
#include "../includ/Snake.hpp"       // Включение заголовочного файла Snake
#include "../includ/GameHandler.hpp" // Включение заголовочного файла GameHandler
#include "../includ/Server.hpp"      // Включение заголовочного файла Server
#include "../includ/GameInit.hpp"    // Включение заголовочного файла GameInit

// Строка с информацией о помощи, которая будет выведена пользователю при запросе
#define HELP_INFO \
"Usage: ./main [args values]...\n" \
"ARGUMENTS: \n" \
"-w    -> set field width\n" \
"-h    -> set field height\n" \
"-f    -> set number of food\n" \
"-p    -> set server port. the standard port is 8808\n" \
"-i    -> set server ip. the standard ip sets by OS\n" \
"-help -> print help documentation\n"

// Массив строк с допустимыми аргументами командной строки
const char *args[] = {
    "-w",       // Ширина поля
    "-h",       // Высота поля
    "-f",       // Количество еды
    "-p",       // Порт сервера
    "-i",       // IP адрес сервера
    "-help"     // Помощь
};

// Метод для инициализации и запуска игры
int GameInit::Start()
{
    // Проверка на превышение максимального количества аргументов
    if (argc > max_argc)
    {
        printf("too many arguments...\n");
        return 1;
    }

    // Инициализация значений аргументов по умолчанию
    int num_args[] = { std_width, std_height, std_food_count, std_port };
    const char *ip = nullptr; // Инициализация указателя IP адреса нулевым указателем
    int matched_argv_idx = 0;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i += 2)
    {
        // Проверка, является ли текущий аргумент допустимым
        if (IsOneOfArgv(args, argv[i], 6, &matched_argv_idx))
        {
            // Обработка аргумента
            if (HandleArgv(i, matched_argv_idx, num_args, &ip))
                return 0;
        }
    }

    // Инициализация генератора случайных чисел
    srand(time(0));
    
    // Создание игрового поля с заданными размерами
    Field fld(num_args[0], num_args[1]);
    
    // Создание списка еды
    List<Food> fod;
    
    // Создание списка змей
    List<Snake> snakes;
    
    // Создание обработчика игры
    GameHandlerGemstone handler(&fld, &fod, &snakes);
    
    // Создание селектора событий
    EventSelector *sel = new EventSelector;
    
    // Запуск сервера
    Server *serv = Server::Start(sel, &fld, &handler, num_args[2], num_args[3], ip);
    if (!serv)
    {
        perror("server"); // Вывод сообщения об ошибке, если сервер не запустился
        return 1;
    }
    
    // Вывод информации о параметрах игрового поля и количестве еды
    printf("width      -> %d\n"
           "height     -> %d\n"
           "food count -> %d\n", num_args[0], num_args[1], num_args[2]);
    
    // Запуск основного цикла обработки событий
    sel->Run();
    return 0;
}

// Метод для проверки, является ли аргумент одним из допустимых
bool GameInit::IsOneOfArgv(const char *argv[6], const char *arg, 
                           int argc, int *matched_argv_idx)
{
    for (int i = 0; i < argc; i++)
    {
        // Сравнение текущего аргумента с допустимыми значениями
        if (!strcmp(argv[i], arg))
        {
            *matched_argv_idx = i; // Сохранение индекса совпавшего аргумента
            return true;           // Возврат true, если аргумент найден
        }
    }
    return false; // Возврат false, если аргумент не найден
}

// Метод для обработки аргументов командной строки
bool GameInit::HandleArgv(int argv_idx, int matched_argv, 
                          int *num_args, const char **ip)
{
    if (matched_argv < 4)
    {
        // Преобразование значения аргумента в целое число и сохранение его
        num_args[matched_argv] = atoi(argv[argv_idx + 1]);
        if (!num_args[matched_argv]) // Проверка на валидность значения
        {
            printf("Invalid argument. Write -help for more information.\n");
            exit(2); // Завершение программы с ошибкой
        }
        return false;
    }
    if (matched_argv == 4)
    {
        *ip = argv[argv_idx + 1]; // Сохранение IP адреса
        return false;
    }
    if (matched_argv == 5)
        WriteHelp(); // Вывод информации о помощи
    return true;
}

// Метод для вывода справочной информации
void GameInit::WriteHelp()
{
    printf(HELP_INFO); // Вывод строки с информацией о помощи
}
