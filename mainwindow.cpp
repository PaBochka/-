#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <map>
#include <iostream>
#include <time.h>
#include <stdlib.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
double MainWindow::random(double min, double max)
{
    return static_cast<double>(rand())/RAND_MAX * (max - min) + min;
}
void MainWindow::on_pushButton_clicked()
{
    QString num_exp = ui->lineEdit->text();
    QString par = ui->lineEdit_2->text();
    auto n = num_exp.split(" ")[0].toInt();
    double p = par.split(" ")[0].toDouble();
    std::default_random_engine generator{static_cast<long unsigned int>(time(nullptr))};
    std::uniform_real_distribution<double> distribution(0, 1);
    //srand(static_cast<unsigned int>(time(nullptr)));
    int numCycles = 0;
    std::map<int, int> cycles;
    for(int i = 0; i < n; i++)
    {
        numCycles = 0;//зависит ли алогритм от того что равномерное распределение
        while(distribution(generator) < p)
        {
            numCycles++;
        }
        if (cycles.empty())
        {
            cycles.insert(std::pair<int, int>(numCycles, 1));
        }
        else
        {
            bool flag = false;
            for(auto it = cycles.begin(); it != cycles.end();  ++it)
            {
                if(it->first == numCycles)
                {
                    it->second++;
                    flag = true;
                }
            }
            if (flag == false)
            {
                cycles.insert(std::pair<int, int>(numCycles, 1));
            }
        }
    }
    int iter = 0;
    ui->tableWidget->setColumnCount(cycles.size());
    for(auto it = cycles.begin(); it != cycles.end(); ++it)
    {
        double cnt = double(it->second)/ double(n);
        ui->tableWidget->setItem(0, iter, new QTableWidgetItem(QString::number(it->first)));
        ui->tableWidget->setItem(1, iter, new QTableWidgetItem(QString::number(it->second)));
        ui->tableWidget->setItem(2, iter, new QTableWidgetItem(QString::number(cnt, 'f', 5)));
        iter++;
    }

}

