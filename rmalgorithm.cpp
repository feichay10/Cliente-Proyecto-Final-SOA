#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
  if (tableTasks != NULL) {
    for(int i{0}; i < tableTasks->rowCount(); ++i) {
      Task current_task{tableTasks->item(i, 0)->text(), std::stoi(tableTasks->item(i, 1)->text().toStdString()), std::stoi(tableTasks->item(i, 2)->text().toStdString()), std::stoi(tableTasks->item(i, 3)->text().toStdString()), 0, 0};
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
    int current_time = 0, max_time = 120;
    Task* current_task = NULL;

    while (current_time < max_time) {
      std::list<Task*> runnable_tasks;

      for (int i = 0; i < tasks_.size(); ++i) {
        if (tasks_[i].last_exec_point + tasks_[i].period <= current_time || current_time == 0) runnable_tasks.push_back(&tasks_[i]);
      }

      if (!runnable_tasks.empty()) {
        runnable_tasks.sort([] (Task * task_a, Task * task_b) {
          return task_a->period < task_b->period;
        });
        current_task = runnable_tasks.back();
      }

      std::cout << "T: " << current_time;

      if (current_task != NULL) {
        std::cout << " - Executing " << current_task->name.toStdString();
        current_task->remaining_time--;
        current_task->last_exec_point = current_time;

        if (current_task->remaining_time == 0) current_task->remaining_time = current_task->timeTask;
      }

      std::cout << std::endl;
      ++current_time;
    }
  }
}

int RMAlgorithm::garantyTest() {
  if (tasks_.size() > 0) {
    double upper_limit = tasks_.size() * (pow(2, 1 / (double)tasks_.size()) - 1);
    double use_factor = 0.0;

    for (const auto& task : tasks_)
      use_factor += task.timeTask / (double)task.period;

    if (use_factor <= upper_limit) {
      return 0; ///<Planificable

    } else if (use_factor < 1.00) {
      return 1; ///<Success not guaranteed

    } else return 2; ///<Overload
  }

  return -1; ///<No tasks
}
