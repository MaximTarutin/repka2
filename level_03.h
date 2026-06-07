#ifndef LEVEL__3_H
#define LEVEL__3_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include "picobject.h"

class Level_03 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_03(QWidget *parent = nullptr);
    ~Level_03();

    QPushButton     *button_back = nullptr;     // Кнопка назад

private:
    int WIDTH_SCREEN = 0;                       // Ширина экрана
    int HEIGHT_SCREEN = 0;                      // Высота экрана
    int CURRENT_OBJECT = 100;                   // Перемещаемый объект
    int STATUS_LEVEL = 0;                       // 0    - Перемещаем корзину на стол
                                                // 1-6  - Перемещаем продукты в корзину
                                                // 7    - Перемещаем тазик в печку

    int NUMBER_PRODUKT = 0;                     // Номер ингридиента в мыслях бабки

    int  rnd(int a, int b);                     // Случайные числа в диапазоне от a до b
    void set_mysl();                           // показываем о чем думает бабка
    void set_object();                          // Создаем объекты для игры
    void mix_coordinates();                     // Перемешиваем координаты в списке
    void return_object(QMouseEvent *pe);        // Возвращаем объект на место

    QLabel          *background = nullptr;      // Фон уровня
    QMediaPlayer    *sound = nullptr;           // Проигрыватель
    QAudioOutput    *output = nullptr;          // Аудиовыход

    QTimer          *timer_show_kolobok;        // Таймер появления колобка
    QTimer          *timer_victory;             // Таймер анимации при победе
    PicObject       *table = nullptr;           // Стол
    PicObject       *babka = nullptr;           // Бабка
    PicObject       *mysl = nullptr;            // Мысль бабки
    PicObject       *tazik[7] = {};             // Состояния тазика по мере наполняемости продуктами
    PicObject       *kolobok = nullptr;         // Колобок
    PicObject       *produkt[6] = {};           // Продукты
    PicObject       *hand = nullptr;            // Рука - подсказка
    PicObject       *produkt_mysl[8] = {};      // Продукты в мысли:
                                                // 0 - тазик
                                                // 1 - молоко
                                                // 2 - масло
                                                // 3 - яйца
                                                // 4 - мука
                                                // 5 - соль
                                                // 6 - венчик
                                                // 7 - колобок
    PicObject       *prosrach = nullptr;        // позрачный объект
    PicObject       *animate_persone = nullptr; // персонаж для анимации

    QString         name_active_object;         // имя объекта по которому кликнули мышкой
    QList<QList<int>>  coordinates = {};        // Список координаты продуктов (список в списке - [[a,b],[a,b],...,[a,b]])

protected:
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);

public slots:
    void initial();                             // Инициализация уровня
    void get_width(int w);                      // Получаем WIDTH_SCREEN
    void get_height(int h);                     // Получаем HEIGHT_SCREEN
    void back_level();                          // Закрываем окно текущего уровня

private slots:
    void show_kolobok();                        // Колобок появляется на столе
    void animate();                             // анимация на уровне
    void victory();                             // Победа
    void help();                                // Подсказка

signals:
    void next_level(int lev);                   // Сигнал переход на следующий уровень
};

#endif // LEVEL__3_H
