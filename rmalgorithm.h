#ifndef RMALGORITHM_H
#define RMALGORITHM_H

#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <queue>
#include <iostream>
#include "qcustomplot.h"
#include "lib_flot.h"

struct Task {
  QString name;
  int graph_pos;
  int timeTask;
  int period;
  int deadline;
  int remaining_time;
  int last_entry_point;
  int exec_num;
  bool just_arrived;
  QColor color;
};

class RMAlgorithm {
 public:
  RMAlgorithm(QTableWidget* tableTasks = NULL);

  QString rateMonotonic(QCustomPlot*, int = 120);
  int garantyTest(void);

 private:
  QVector<Task> tasks_;
};

#endif // RMALGORITHM_H
