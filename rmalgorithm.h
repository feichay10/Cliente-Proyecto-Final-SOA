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

  bool rateMonotonic(void); ///< true = algorithm success
  bool isSchedulable(void);

 private:
  QVector<Task> tasks_;
  double worst_case_;
  double utilization_;
};

#endif // RMALGORITHM_H
