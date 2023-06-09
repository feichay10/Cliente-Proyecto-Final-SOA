#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
  if (tableTasks != NULL) {
    for(int i{0}; i < tableTasks->rowCount(); ++i) {
      Task current_task{tableTasks->item(i, 0)->text(), std::stoi(tableTasks->item(i, 1)->text().toStdString()), std::stoi(tableTasks->item(i, 2)->text().toStdString()), std::stoi(tableTasks->item(i, 3)->text().toStdString())};
      tasks_.push_back(current_task);
    }

    std::sort(tasks_.begin(), tasks_.end(), [] (const Task & task_a, const Task & task_b) {
      return task_a.period < task_b.period;
    });
  }
}

void RMAlgorithm::rateMonotonic() {
  const int kGarantyTest{garantyTest()};

  if (kGarantyTest == 0 ||  kGarantyTest == 1) {
    int time = 0;
    std::queue<Task> ready_tasks;
  }
}

int RMAlgorithm::garantyTest() {
  if (tasks_.size() > 0) {
    double upper_limit = tasks_.size() * (pow(2, 1 / tasks_.size()) - 1);
    double use_factor = 0.0;

    for (const auto& task : tasks_)
      use_factor += task.timeTask / task.period;

    if (use_factor <= upper_limit) {
      return 0; ///<Planificable

    } else if (use_factor < 1.00) {
      return 1; ///<Success not guaranteed

    } else return 2; ///<Overload
  }

  return -1; ///<No tasks
}
