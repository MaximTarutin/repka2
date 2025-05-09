#ifndef LEVEL_01_H
#define LEVEL_01_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QMouseEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
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
    int CURRENT_OBJECT = 0;                                 // текущий овощ
    bool CURRENT_OBJECT_ACTIVE = false;                     // текущий овощ активен
                                                            // курсор находится в пределах объекта
    int x[9] = {};                                          // координаты овощей
    int y[9] = {};
    int x1[9] = {};                                         // координаты серых овощей
    int y1[9] = {};
    QList<int> value_i = {};                                // список нумерации овощей
    QList<QList<int>>  coordinates_g = {};                  // координаты серых овощей

    bool LEVEL_FLAG = false;                                // false - уровень еще не запускался
                                                            // true - уровень начали проходить
    bool LEVEL_END = false;                                 // Пройден ли уровень
    bool HELP_FLAG = true;                                  // подсказка: true - активна

    QLabel          *background_lev01 = nullptr;            // Фон уровня 1
    PicObject       *vegetable[9] = {};                     // овощи
    PicObject       *vegetable_gray[9] = {};                // серые овощи
    PicObject       *warehouse = nullptr;                   // синий круг (склад)
    PicObject       *bird = nullptr;                        // летающая птица анимация
    PicObject       *help = nullptr;                        // подсказка
    PicObject       *repka = nullptr;                       // репка
    QTimer          *timer_bird = nullptr;                  // таймер частоты полета птицы
    QMediaPlayer    *sound = nullptr;                       // звук "ага"
    QAudioOutput    *output = nullptr;                      // аудиовыход

    int rnd(int a, int b);                                  // случайное число в диапазоне от a до b
    void mix_vegetables();                                  // перемешать список нумерации овощей
    void animation_level();                                 // анимация уровня

public slots:
    void initial();                                         // инициализация
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // Возврат на главный экран

private slots:
    void help_move_end();                                   // окончание движения подсказки
    void flight_bird();                                     // запускаем птицу
    void victory();                                         // победа

protected:
    virtual void mousePressEvent(QMouseEvent *pe);          // события по нажатию кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent *pe);           // перетаскивание овощей
    virtual void mouseReleaseEvent(QMouseEvent *pe);        // отпускаем кнопку мышки

signals:
    void next_level();                                 // посылает номер следующего уровня
};

#endif // LEVEL_01_H
