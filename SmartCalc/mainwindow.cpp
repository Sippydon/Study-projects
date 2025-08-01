#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);

  ui->month_choose_label->setVisible(false);
  ui->month_choose->setVisible(false);
  connect(ui->btn_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_min, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_mul, SIGNAL(clicked()), this, SLOT(mult_and_div_sign()));
  connect(ui->btn_div, SIGNAL(clicked()), this, SLOT(mult_and_div_sign()));

  connect(ui->btn_sin, SIGNAL(clicked()), this, SLOT(function_with_brackets()));
  connect(ui->btn_cos, SIGNAL(clicked()), this, SLOT(function_with_brackets()));
  connect(ui->btn_tan, SIGNAL(clicked()), this, SLOT(function_with_brackets()));
  connect(ui->btn_atan, SIGNAL(clicked()), this,
          SLOT(function_with_brackets()));
  connect(ui->btn_acos, SIGNAL(clicked()), this,
          SLOT(function_with_brackets()));
  connect(ui->btn_asin, SIGNAL(clicked()), this,
          SLOT(function_with_brackets()));
  connect(ui->btn_log, SIGNAL(clicked()), this, SLOT(function_with_brackets()));
  connect(ui->btn_ln, SIGNAL(clicked()), this, SLOT(function_with_brackets()));
  //
  connect(ui->btn_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_sqrt, SIGNAL(clicked()), this,
          SLOT(function_with_brackets()));
  connect(ui->btn_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->btn_lb, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->btn_rb, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() {
  delete graph;
  delete ui;
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + button->text();
  ui->result->setText(newlabel);
}

void MainWindow::function_with_brackets() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText;
  if (button) {
    buttonText = button->text();
    if (buttonText == "√") buttonText = "sqrt";
  }
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + buttonText + "(";
  ui->result->setText(newlabel);
}

void MainWindow::mult_and_div_sign() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText;
  if (button) {
    buttonText = button->text();
    if (buttonText == "÷") {
      buttonText = "/";
    } else if (buttonText == "×") {
      buttonText = "*";
    }
  }
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + buttonText;
  ui->result->setText(newlabel);
}
void MainWindow::on_btn_dot_clicked() {
  if (!(ui->result->text().endsWith('.')))
    ui->result->setText(ui->result->text() + ".");
}

void MainWindow::on_btn_ac_clicked() {
  ui->result->setText("0");
}

void MainWindow::on_btn_clear_clicked() {
  QString currentText = ui->result->text();
  if (!currentText.isEmpty() && currentText != "0") {
    currentText = currentText.left(currentText.length() - 1);
    ui->result->setText(currentText);
  } else {
    ui->result->setText("0");
  }
}

void MainWindow::on_btn_res_clicked() {
  QString str = ui->result->text();
  QByteArray byte_string = str.toLocal8Bit();
  char *equation = byte_string.data();
  double res = 0;
  double entered_x = 0;
  double *X = &entered_x;
  if (str.contains('x')) {
    bool ok;
    entered_x = QInputDialog::getDouble(
        this, "Enter value", "Enter value of X:", 0, -100000, 100000, 7, &ok);
    if (!ok) return;
  } else
    X = NULL;
  if (SmartCalc(equation, &res, X)) {
    QString numberResult = QString::number(res, 'g', 15);
    ui->result->setText(numberResult);
  } else {
    ui->result->setText("ERROR");
  }
}

void MainWindow::on_btn_plot_clicked() {
  QString str = ui->result->text();
  QByteArray byte_string = str.toLocal8Bit();
  char *equation = byte_string.data();
  if (isValid(equation)) {
    graph = new Graph;
    graph->setFixedSize(graph->geometry().width(), graph->geometry().height());

    graph->show();
    graph->graphics(equation);
  } else {
    ui->result->setText("ERROR");
  }
}

void MainWindow::on_btn_credit_calc_clicked() {
  QString inputSum = ui->credit_sum->text();
  QString inputTerm = ui->credit_term->text();
  QString inputRate = ui->interest_rate->text();
  QString timeMeasure = ui->comboBox->currentText();

  int isMonth = (timeMeasure == "месяцев") ? 1 : 0;
  int isAnnyity = -1;  // 1 - ann, 0 - diff

  if (ui->btn_annyity->isChecked())
    isAnnyity = 1;
  else if (ui->btn_diff->isChecked())
    isAnnyity = 0;

  if (inputRate.isEmpty() || inputSum.isEmpty() || inputTerm.isEmpty() ||
      isAnnyity == -1) {
    QMessageBox::information(nullptr, "Ошибка",
                             "Не введены все необходимые параметры для "
                             "рассчета кредита.");
    return;
  }
  bool okSum, okTerm, okRate;
  double valSum = inputSum.toDouble(&okSum);
  int valTerm = inputTerm.toInt(&okTerm);
  double valRate = inputRate.toDouble(&okRate);

  if (!(okSum && okTerm && okRate) || !valRate || !valSum || !valTerm) {
    QMessageBox::information(nullptr, "Ошибка", "Неправильный ввод");
    return;
  }

  valRate /= 1200; // процентная ставка в месяц
  valTerm = isMonth ? valTerm : valTerm * 12;

  double monthPayment = 0, creditPayment = 0, sumPayment = 0;
  if (isAnnyity) {
    double annyity_pay = valRate * pow((1 + valRate), valTerm) /
                      (pow((1 + valRate), valTerm) - 1);
    monthPayment = valSum * annyity_pay;
    sumPayment = monthPayment * valTerm;
    creditPayment = sumPayment - valSum;
  } else {
    double mPay = valSum / valTerm;
    bool ok;
    int currentMonth = ui->month_choose->currentText().toInt(&ok);
    if (ok) {
      sumPayment = 0;
      for (int i = 1; i < valTerm; ++i) {
        sumPayment += (valSum - mPay * (i - 1)) * valRate + mPay;
        if (i == currentMonth)
          monthPayment = (valSum - mPay * (i - 1)) * valRate + mPay;
      }

      creditPayment = sumPayment - valSum;
    } else
      return;
  }

  ui->month_payment->setText(QString::number(monthPayment, 'f', 2));
  ui->credit_payment->setText(QString::number(creditPayment, 'f', 2));
  ui->sum_payment->setText(QString::number(sumPayment, 'f', 2));
}

void MainWindow::on_btn_diff_clicked(bool checked) {
  if (checked == true) {
    ui->month_choose_label->setVisible(true);
    ui->month_choose->setVisible(true);
    QString inputTerm = ui->credit_term->text();
    QString timeMeasure = ui->comboBox->currentText();
    int isMonth = (timeMeasure == "месяцев") ? 1 : 0;

    bool okTerm;
    int valTerm = inputTerm.toInt(&okTerm);

    valTerm = isMonth ? valTerm : valTerm * 12;

    if (okTerm) {
      for (int i = 1; i <= valTerm; ++i) {
        ui->month_choose->addItem(QString::number(i));
      }
    }
  }
}

void MainWindow::on_btn_annyity_clicked(bool checked) {
  if (checked) {
    ui->month_choose_label->setVisible(false);
    ui->month_choose->setVisible(false);
  }
}
