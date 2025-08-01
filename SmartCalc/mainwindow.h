#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graph.h>

#include <QDebug>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QString>

extern "C" {
#include "calculate.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::SmartCalc *ui;
  Graph *graph;

 private slots:
  void on_btn_res_clicked();
  void digits_numbers();
  void function_with_brackets();
  void mult_and_div_sign();
  void on_btn_dot_clicked();
  void on_btn_clear_clicked();
  void on_btn_plot_clicked();
  void on_btn_ac_clicked();
  void on_btn_credit_calc_clicked();
  void on_btn_diff_clicked(bool checked);

  void on_btn_annyity_clicked(bool checked);
};
#endif  // MAINWINDOW_H
