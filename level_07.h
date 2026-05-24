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

    QLabel          *background = nullptr;          // Фон
    QMediaPlayer    *sound = nullptr;               // Звуки
    QAudioOutput    *output = nullptr;              // Аудиовыход
    PicObject       *Myschka = nullptr;             // Мышка на фоне
    PicObject       *Mysl = nullptr;                // Мысль мышки

    int rnd(int a, int b);                          // Случайные числа в диапазоне от a до b

signals:
    void next_level(int lev);                       // Сигнал переход на следующий уровень
};

#endif // LEVEL__7_H
