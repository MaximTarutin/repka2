#ifndef LEVEL__7_H
#define LEVEL__7_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QTimer>
#include "picobject.h"

class Level_07 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_07(QWidget *parent = nullptr);
    ~Level_07();

    QPushButton *button_back = nullptr;             // Кнопка назад

    void initial();                                 // Инициализация уровня

public slots:
    void get_width(int w);                          // Получаем ширину экрана
    void get_height(int h);                         // Получаем высоту экрана

private:
    int WIDTH_SCREEN = 0;                           // Ширина экрана
    int HEIGHT_SCREEN = 0;                          // Высота экрана
    int position_pusle[17] = {};                    // Положение пазла (0-0, 1-90, 2-180, 3-270)
    int angle_of_rotate[17] = {};                   // Угол поворота

    QLabel          *background = nullptr;          // Фон
    QMediaPlayer    *sound = nullptr;               // Звуки
    QAudioOutput    *output = nullptr;              // Аудиовыход
    PicObject       *myschka = nullptr;             // Мышка на фоне
    PicObject       *chees = nullptr;               // Кусок сыра на фоне
    PicObject       *mysl = nullptr;                // Мысль мышки
    PicObject       *puzle[17] = {};                // Набор пазлов

    int rnd(int a, int b);                          // Случайные числа в диапазоне от a до b
    void create_puzle();                            // Создаем набор пазлов
    void rotate_puzle();                            // Переворачиваем пазлы случайным образом

signals:
    void next_level(int lev);                       // Сигнал переход на следующий уровень
};

#endif // LEVEL__7_H
