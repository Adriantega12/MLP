#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "trainingmodule.h"

namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void plotClick(QMouseEvent*);

    private slots:
        void on_layerNumSB_valueChanged(int arg1);

    private:
        Ui::MainWindow *ui;

        TrainingModule* trainingModule;
    };

#endif // MAINWINDOW_H
