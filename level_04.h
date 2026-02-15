#ifndef LEVEL__4_H
#define LEVEL__4_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include "picobject.h"

class Level_04 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_04(QWidget *parent = nullptr);
    ~Level_04();

    void initial();                             // Инициализация уровня
    QPushButton     *button_back = nullptr;     // Кнопка назад

private:
    int WIDTH_SCREEN = 0;                       // Ширина экрана
    int HEIGHT_SCREEN = 0;                      // Высота экрана
    int STEP = 0;                               // Шаг выполнения (всего 7)
    int ACTIVE_PEN = 7;                         // Активный карандаш, 10 - нет активных
    int old_x = 0;                              // координаты объекта до перемещения
    int old_y = 0;

    QLabel      *background = nullptr;          // Фон
    PicObject   *vnuchka = nullptr;             // Внучка
    PicObject   *mysl = nullptr;                // Мысль внучки
    PicObject   *holst = nullptr;               // Холст
    PicObject   *vnuchka_holst[8] = {};         // Внучка на холсте
    PicObject   *container = nullptr;           // Карандашница
    PicObject   *mysl_obj[8] = {};              // Объекты в мысли
    PicObject   *pens[8] = {};                  // Карандаши
    PicObject   *bubbles = nullptr;             // Анимация шариков
    PicObject   *guk = nullptr;                 // Анимация жук
    PicObject   *bab = nullptr;                 // Анимация бабочки
    PicObject   *muh = nullptr;                 // Анимация муха
    QString     name_active_object;             // имя объекта по которому кликнули мышкой
    QMediaPlayer    *sound = nullptr;           // Проигрыватель
    QAudioOutput    *output = nullptr;          // Аудиовыход
    QTimer          *victory_timer = nullptr;   // Таймер анимации победы

    QList<int> value_p = {};                    // Список нумерации карандашей
    QList<int> value_m = {};                    // Список предметов в мысли
    QList<QList<int>>  coordinates = {};        // Список координат карандашей в карандашнице

    int rnd(int a, int b);                      // Случайное число в диапазоне от a до b
    void mix_pens();                            // Перемешиваем список карандашей
    void mix_mysl();                            // Перемешиваем список предметов в мысли
    void delete_pen();                          // Удаляем использованный правильно карандаш
    void victory();                             // Победа


protected:
    virtual void mousePressEvent(QMouseEvent *pe);      // Нажатие кнопки мышки
    virtual void mouseReleaseEvent(QMouseEvent *pe);    // Отпускание кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent *pe);       // Перемещение мышки

public slots:
    void get_width(int w);                      // Получаем ширину экрана
    void get_height(int h);                     // Получаем высоту экрана
    void back_level();                          // Закрываем окно текущего уровня

signals:
        void next_level();                      // Сигнал переход на следующий уровень
};

#endif // LEVEL__4_H
