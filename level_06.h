#ifndef LEVEL__6_H
#define LEVEL__6_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include <QMouseEvent>
#include <QTimer>
#include "picobject.h"

class Level_06 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_06(QWidget *parent = nullptr);
    ~Level_06();

    void initial();                                 // Инициализация
    QPushButton *button_back = nullptr;             // Кнопка назад
    QList<QList<int>> coordinates_card = {};       // Координаты карт

public slots:
    void get_width(int w);                          // Получаем ширину экрана
    void get_height(int h);                         // Получаем высоту экрана

private slots:
    void help();                                    // Подсказка
    void checking_for_math();                       // Проверяем совпали ли карты
    void victory();                                 // Победа

private:
    int WIDTH_SCREEN = 0;                           // Ширина экрана
    int HEIGHT_SCREEN = 0;                          // Высота экрана
    int HELP_CARD = 0;                              // Карта подсказка
    int CLICKED_CARD = 100;                         // Номер карты по которой кликнули
    int OPEN_CARD[2] = {100, 100};                  // Номера открытых карт на поле (100 - все закрыты)
    int COUNTER = 0;                                // Счетчик совпавших пар

    QLabel          *background = nullptr;          // Фон
    QMediaPlayer    *sound = nullptr;               // Звуки
    QAudioOutput    *output = nullptr;              // Аудиовыход
    PicObject       *cat = nullptr;                 // Кот на фоне
    PicObject       *card[30] = {};                 // Карточки
    PicObject       *inv_card[30] = {};             // Перевернутые карты
    PicObject       *hand[2] = {};                  // Рука подсказка
    PicObject       *anime_cat_1 = nullptr;         // анимация 1
    PicObject       *anime_cat_2 = nullptr;         // анимация 2
    QTimer          *timer_show = nullptr;          // Время показывания карт
    QTimer          *timer_victory = nullptr;       // Таймер победной анимации

    int rnd(int a, int b);                          // Случайные числа в диапазоне от a до b
    void create_cards();                            // Создаем карты и их рубашки
    void create_rubaha();
    void create_coordinates_list();                 // Создаем список координат карт
    void mix_coordinates();                         // Перемешиваем координаты карточек
    void arrange_card();                            // Расставляем карты на поле


protected:
    virtual void mousePressEvent(QMouseEvent *pe);  // события по нажатию кнопки мышки

signals:
    void next_level(int lev);                       // Сигнал переход на следующий уровень
};

#endif // LEVEL__6_H
