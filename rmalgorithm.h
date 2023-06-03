#ifndef RMALGORITHM_H
#define RMALGORITHM_H

#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <iostream>

struct Task {
  QString name;
  int timeTask;
  int period;
  int deadline;
};

class RMAlgorithm {
 public:
  RMAlgorithm(QTableWidget* tableTasks = NULL);

  void rateMonotonic(void);
  int garantyTest(void);

 private:
  QVector<Task> tasks_;
};

#endif // RMALGORITHM_H
