#ifndef LEVEL_01_H
#define LEVEL_01_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "picobject.h"

class Level_01 : public QWidget
{
    Q_OBJECT
public:
    explicit Level_01(QWidget *parent = nullptr);
    ~Level_01();

private:
    int WIDTH_SCREEN = 0;                                   // Разрешение экрана
    int HEIGHT_SCREEN = 0;

    QLabel          *background_lev01 = nullptr;            // Фон уровня 1
    PicObject       *repka = nullptr;                       // Цветная репка

public slots:
    void initial();                                         // инициализация
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN

signals:
};

#endif // LEVEL_01_H
