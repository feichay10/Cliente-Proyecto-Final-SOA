#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
  if (tableTasks != NULL) {
    for(int i{0}; i < tableTasks->rowCount(); ++i) {
      Task current_task{tableTasks->item(i, 0)->text(), std::stoi(tableTasks->item(i, 1)->text().toStdString()), std::stoi(tableTasks->item(i, 2)->text().toStdString()), std::stoi(tableTasks->item(i, 3)->text().toStdString()), std::stoi(tableTasks->item(i, 1)->text().toStdString()), 0, 0, true};
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
      std::cout << "T: " << current_time;
      std::list<Task*> runnable_tasks;

      for (int i = 0; i < tasks_.size(); ++i) {
        if (tasks_[i].last_entry_point + tasks_[i].period <= current_time || tasks_[i].exec_num == 0) {
          runnable_tasks.push_back(&tasks_[i]);

          if (tasks_[i].just_arrived) {
            tasks_[i].last_entry_point = current_time;
            tasks_[i].just_arrived = false;
          }
        }
      }

      if (!runnable_tasks.empty()) {
        runnable_tasks.sort([] (Task * task_a, Task * task_b) {
          return task_a->period < task_b->period;
        });

        if (current_task == NULL || current_task->period > runnable_tasks.front()->period) current_task = runnable_tasks.front();
      }

      if (current_task != NULL) {
        std::cout << " - Executing " << current_task->name.toStdString() << current_task->exec_num << " remaining time: " << current_task ->remaining_time;
        //std::cout << " entered processor in: " << current_task->last_entry_point;
        current_task->remaining_time--;

        if (current_task->remaining_time == 0) {
          current_task->remaining_time = current_task->timeTask;
          current_task->exec_num++;
          current_task->just_arrived = true;
          current_task = NULL;
        }
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
