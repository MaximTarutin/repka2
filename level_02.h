#ifndef LEVEL_02_H
#define LEVEL_02_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QPushButton>

class Level_02 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_02(QWidget *parent = nullptr);
    ~Level_02();

    QPushButton     *button_next = nullptr;                 // Кнопка следующий уровень
    QPushButton     *button_back = nullptr;                 // Кнопка назад

public slots:
    void initial();             // Инициализация уровня
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // возвращаемся на 1 уровень

private:
    int WIDTH_SCREEN = 0;                                   // Разрешение экрана
    int HEIGHT_SCREEN = 0;

    QLabel      *background_lev02 = nullptr;                // Фон уровня

signals:
};

#endif // LEVEL_02_H
