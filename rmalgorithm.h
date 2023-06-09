#ifndef RMALGORITHM_H
#define RMALGORITHM_H

#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <queue>
#include <iostream>

struct Task {
  QString name;
  int timeTask;
  int period;
  int deadline;
  int remaining_time;
  int last_exec_point;
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
