#ifndef LEVEL_02_H
#define LEVEL_02_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include "picobject.h"

class Level_02 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_02(QWidget *parent = nullptr);
    ~Level_02();

    QPushButton     *button_back = nullptr;                 // Кнопка назад

public slots:
    void initial();             // Инициализация уровня
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // возвращаемся на 1 уровень

private:
    int WIDTH_SCREEN = 0;                                   // Разрешение экрана
    int HEIGHT_SCREEN = 0;
    int x[8] = {};                                          // Координаты инструментов
    int y[8] = {};
    int STEP_NUMBER = 0;                                    // номер хода игрока

    int rnd(int a, int b);                                  // случайное число в диапазоне от a до b
    void mix_instruments();                                 // перемешать список нумерации инструмента
    void mysl_deda(int step);                               // О чем думает дед, отображаем в мысли
    void victory();                                         // Победа
    void animation_level();                                 // Анимация на уровне
    void run_tarakan();                                     // бег таракана

    QLabel      *background_lev02 = nullptr;                // Фон уровня    
    PicObject   *instruments[8] = {};                       // Инструменты
    PicObject   *instruments_mysl[8] = {};                  // Инструменты в мысли
    PicObject   *dedka = nullptr;                           // Дедка
    PicObject   *mysl = nullptr;                            // Мысль дедки
    PicObject   *cell = nullptr;                            // Ячейка, куда складывается инструмент
    PicObject   *firework = nullptr;                        // Анимация феерверка при победе
    PicObject   *spider = nullptr;                          // Анимация паука
    PicObject   *tarakan = nullptr;                         // Анимация таракана
    QList<QList<int>>  coordinates = {};                    // Координаты инструмента
    QList<int> value_i = {};                                // список нумерации инструмента
    QList<int> value_m = {};                                // список нумерации инструмента в мысли
    QMediaPlayer    *sound = nullptr;                       // звуки
    QAudioOutput    *output = nullptr;                      // аудиовыход
    QTimer       *timer_firework = nullptr;                 // Таймер салюта
    QTimer       *timer_spider = nullptr;                   // Таймер паука
    QTimer       *timer_tarakan = nullptr;                  // Таймер таракана

protected:
    virtual void mousePressEvent(QMouseEvent *pe);          // события по нажатию кнопки мышки

signals:
    void next_level();                                      // сигнал следующий уровень
};

#endif // LEVEL_02_H
