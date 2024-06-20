#ifndef SERVER_HPP_SENTRY
#define SERVER_HPP_SENTRY

#include "Snake.hpp"
#include "List.hpp"
#include "Field.hpp"
#include "Food.hpp"
#include "GameHandler.hpp"

/**
 * @brief Enum для определения размеров массивов.
 */
enum
{
    fd_array_len_start = 16, /**< Начальный размер массива дескрипторов. */
    buffersize = 64 /**< Размер буфера для приема и отправки данных. */
};

/**
 * @brief Абстрактный класс для обработки дескрипторов.
 * 
 * Этот класс предназначен для обработки дескрипторов файлов, таких как сокеты.
 */
class FdHandler
{
    int fd; /**< Дескриптор файла. */
    bool want_read; /**< Флаг, указывающий на необходимость чтения из файла. */
    bool want_write; /**< Флаг, указывающий на необходимость записи в файл. */

public:
    /**
     * @brief Конструктор для обработчика дескриптора.
     * 
     * @param _fd Дескриптор файла.
     * @param _want_read Флаг, указывающий на необходимость чтения из файла (по умолчанию true).
     * @param _want_write Флаг, указывающий на необходимость записи в файл (по умолчанию false).
     */
    FdHandler(int _fd, bool _want_read = true, bool _want_write = false)
        : fd(_fd), want_read(_want_read), want_write(_want_write) {}

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~FdHandler();

    /**
     * @brief Получает дескриптор файла.
     * 
     * @return Дескриптор файла.
     */
    int GetFd() { return fd; }

    /**
     * @brief Проверяет, нужно ли читать из файла.
     * 
     * @return true, если нужно читать, false - в противном случае.
     */
    bool WantRead() { return want_read; }

    /**
     * @brief Проверяет, нужно ли писать в файл.
     * 
     * @return true, если нужно писать, false - в противном случае.
     */
    bool WantWrite() { return want_write; }

    /**
     * @brief Устанавливает флаг чтения из файла.
     * 
     * @param _want_read Новое значение флага чтения.
     */
    void SetRead(bool _want_read) { want_read = _want_read; }

    /**
     * @brief Устанавливает флаг записи в файл.
     * 
     * @param _want_write Новое значение флага записи.
     */
    void SetWrite(bool _want_write) { want_write = _want_write; }

    /**
     * @brief Абстрактный метод для обработки событий.
     * 
     * @param r Флаг, указывающий на готовность к чтению.
     * @param w Флаг, указывающий на готовность к записи.
     */
    virtual void Handle(bool r, bool w) = 0;
};

/**
 * @brief Класс для управления событиями.
 * 
 * Этот класс предназначен для управления событиями, связанными с дескрипторами файлов.
 */
class EventSelector
{
    FdHandler **fd_array; /**< Массив дескрипторов файлов. */
    int fd_array_len; /**< Размер массива дескрипторов файлов. */
    int max_fd; /**< Максимальный дескриптор файла. */
    FdHandler *server_fd; /**< Дескриптор файла сервера. */

public:
    /**
     * @brief Конструктор для селектора событий.
     */
    EventSelector()
        : fd_array(0), fd_array_len(0), max_fd(-1), server_fd(0) {}

    /**
     * @brief Деструктор для селектора событий.
     */
    ~EventSelector();

    /**
     * @brief Добавляет дескриптор файла в массив.
     * 
     * @param h Дескриптор файла.
     */
    void Add(FdHandler *h);

    /**
     * @brief Удаляет дескриптор файла из массива.
     * 
     * @param h Дескриптор файла.
     */
    void Remove(FdHandler *h);

    /**
     * @brief Устанавливает дескриптор файла сервера.
     * 
     * @param h Дескриптор файла сервера.
     */
    void SetServerFd(FdHandler *h);

    /**
     * @brief Запускает цикл обработки событий.
     */
    void Run();
};

////////////////////////////////////////

class Client;

/**
 * @brief Класс для управления сервером.
 * 
 * Этот класс предназначен для управления сервером, включая управление клиентами и игровым процессом.
 */
class Server : public FdHandler
{
    
    enum game_step
    {
        not_started, /**< Игра не началась. */
        started /**< Игра началась. */
    };
    struct item
    {
        Client *cl; /**< Клиент. */
        item *next; /**< Следующий элемент в списке. */
    };
    item *first; /**< Первый элемент в списке клиентов. */
    item *delete_list; /**< Список клиентов для удаления. */
    EventSelector *the_selector; /**< Селектор событий. */
    Field *field; /**< Игровое поле. */
    GameHandlerGemstone *handler; /**< Обработчик игры. */
    int snakes_count; /**< Количество змей. */
    game_step st; /**< Текущий шаг игры. */
    int food_count; /**< Количество еды на поле. */

    /**
     * @brief Конструктор для сервера.
     * 
     * @param _fd Дескриптор файла сервера.
     * @param _the_selector Селектор событий.
     * @param _field Игровое поле.
     * @param _handler Обработчик игры.
     * @param _food_count Количество еды на поле.
     */
    Server(int _fd, EventSelector *_the_selector,
           Field *_field,
           GameHandlerGemstone *_handler, int _food_count);

public:
    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Server();

    /**
     * @brief Статический метод для запуска сервера.
     * 
     * @param _the_selector Селектор событий.
     * @param _field Игровое поле.
     * @param _handler Обработчик игры.
     * @param _food_count Количество еды на поле.
     * @param port Порт для подключения.
     * @param ip Адрес для подключения.
     * @return Указатель на запущенный сервер.
     */
    static Server *Start(EventSelector *_the_selector, Field *_field,
                         GameHandlerGemstone *_handler, int _food_count,
						 int port, const char *ip);

    /**
     * @brief Удаляет клиента из списка.
     * 
     * @param cl Клиент для удаления.
     */
    void RemoveClient(Client *cl);

    /**
     * @brief Абстрактный метод для обработки событий.
     * 
     * @param r Флаг, указывающий на готовность к чтению.
     * @param w Флаг, указывающий на готовность к записи.
     */
    virtual void Handle(bool r, bool w);

    /**
     * @brief Отправляет сообщение клиенту.
     * 
     * @param fd Дескриптор файла клиента.
     * @param msg Сообщение для отправки.
     * @param len Длина сообщения.
     */
    void SendTo(int fd, const char *msg, int len);

    /**
     * @brief Начинает игру.
     */
    void StartGame();

private:
    /**
     * @brief Отрисовывает все элементы на поле.
     */
    void DrawAll();

    /**
     * @brief Находит клиента по змее.
     * 
     * @param s Змей для поиска.
     * @return Клиент, соответствующий змее.
     */
    Client *FindClientBySnake(Snake *s);

    /**
     * @brief Добавляет клиента в список для удаления.
     * 
     * @param cl Клиент для удаления.
     */
    void AddToDeleteList(Client *cl);

    /**
     * @brief Удаляет всех клиентов из списка.
     */
    void DeleteAllFromList();

    /**
     * @brief Обрабатывает события записи.
     */
    void WriteHandle();
};

/**
 * @brief Класс для управления клиентом.
 * 
 * Этот класс предназначен для управления клиентом, включая обработку сообщений и управления змеей.
 */
class Client : public FdHandler
{
    friend class Server;
    char buf[buffersize]; /**< Буфер для приема и отправки данных. */
    int buf_used; /**< Количество используемых байтов в буфере. */
    Snake *sn; /**< Змей клиента. */

    Server *the_master; /**< Указатель на сервер. */

public:
    /**
     * @brief Конструктор для клиента.
     * 
     * @param _fd Дескриптор файла клиента.
     * @param _the_master Указатель на сервер.
     * @param _sn Змей клиента.
     */
    Client(int _fd, Server *_the_master, Snake *_sn);

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Client();

    /**
     * @brief Абстрактный метод для обработки событий.
     * 
     * @param r Флаг, указывающий на готовность к чтению.
     * @param w Флаг, указывающий на готовность к записи.
     */
    virtual void Handle(bool r, bool w);

    /**
     * @brief Обрабатывает строку, полученную от клиента.
     * 
     * @param msg Строка для обработки.
     */
    void StringHandle(const char *msg);

private:
    /**
     * @brief Получает змей клиента.
     * 
     * @return Змей клиента.
     */
    Snake *GetSnake() { return sn; }
};

#endif
