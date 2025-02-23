#ifndef LEVEL_01_H
#define LEVEL_01_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
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

    QLabel          *background_lev01 = nullptr;            // Фон уровня 1
    PicObject       *repka = nullptr;                       // Цветная репка

public slots:
    void initial();                                         // инициализация
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // Возврат на главный экран

signals:
};

#endif // LEVEL_01_H
