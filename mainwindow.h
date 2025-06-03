#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>
#include <QCursor>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "level_01.h"
#include "level_02.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void width_scr(int);                                            // Сигнал ширина экрана
    void height_scr(int);                                           // Сигнал высота экрана

private:
    QLabel              *background_logo = nullptr;                 // Фон
    QPushButton         *button_start = nullptr;                    // Кнопка старт
    QPushButton         *button_exit = nullptr;                     // Кнопка выход
    QMediaPlayer        *music = nullptr;                           // фоновая музыка
    QAudioOutput        *audiooutput = nullptr;                     // аудиовыход

    Level_01            *lev_01 = nullptr;                          // первый уровень
    Level_02            *lev_02 = nullptr;                          // второй уровень

    int WIDTH_SCREEN = 0;                                           // Ширина экрана
    int HEIGHT_SCREEN = 0;                                          // Высота экрана
    int CURRENT_LEVEL = 1;                                          // Текущий уровень

    void screen_size();                                             // Получаем разрешение экрана и
                                                                    // определяем результаты в переменные
                                                                    // WIDTH_SCREEN и SCREEN_HEIGHT
    void initial();                                                 // Инициализация

private slots:
    void exit_of_game();                                            // Выход из игры
    void start_level();

};
#endif // MAINWINDOW_H
