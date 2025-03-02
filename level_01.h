#ifndef LEVEL_01_H
#define LEVEL_01_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "picobject.h"


class Level_01 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_01(QWidget *parent = nullptr);
    ~Level_01();
    QPushButton     *button_next = nullptr;                 // Кнопка следующий уровень
    QPushButton     *button_back = nullptr;                 // Кнопка назад

private:
    int WIDTH_SCREEN = 0;                                   // Разрешение экрана
    int HEIGHT_SCREEN = 0;
    int x[9];                                               // координаты овощей
    int y[9];
    int x1[9];                                              // координаты серых овощей
    int y1[9];

    QLabel          *background_lev01 = nullptr;            // Фон уровня 1
    PicObject       *ovoshi[9];                             // овощи
    PicObject       *ovoshi_gray[9];                        // серые овощи
    PicObject       *sklad;                                 // синий круг

    int rnd(int a, int b);                                  // случайное число в диапазоне от a до b


public slots:
    void initial();                                         // инициализация
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // Возврат на главный экран

signals:
};

#endif // LEVEL_01_H
