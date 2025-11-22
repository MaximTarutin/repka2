#ifndef LEVEL__4_H
#define LEVEL__4_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QLabel>
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

    QLabel      *background = nullptr;          // Фон
    PicObject   *vnuchka = nullptr;             // Внучка
    PicObject   *mysl = nullptr;                // Мысль внучки
    PicObject   *holst = nullptr;               // Холст

public slots:
    void get_width(int w);                      // Получаем ширину экрана
    void get_height(int h);                     // Получаем высоту экрана
    void back_level();                          // Закрываем окно текущего уровня

signals:
        void next_level();                      // Сигнал переход на следующий уровень
};

#endif // LEVEL__4_H
