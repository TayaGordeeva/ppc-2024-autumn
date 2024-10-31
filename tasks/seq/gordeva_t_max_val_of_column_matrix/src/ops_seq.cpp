// Copyright 2024 Nesterov Alexander
#include "seq/gordeva_t_max_val_of_column_matrix/include/ops_seq.hpp"

#include <random>
#include <thread>

using namespace std::chrono_literals;

namespace gordeva_t_max_val_of_column_matrix_seq {

bool gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  // input_ = reinterpret_cast<int*>(taskData->inputs[0])[0];
  // res = 0;

  int rows = taskData->inputs_count[0];
  int cols = taskData->inputs_count[1];
  int* input_matr;
  input_.resize(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; i++) {
    input_matr = reinterpret_cast<int*>(taskData->inputs[i]);
    for (int j = 0; j < cols; j++) input_[i][j] = input_matr[j];
  }

  res_.resize(cols);

  return true;
}

bool gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::validation() {
  internal_order_test();
  // Check count elements of output

  if ((taskData->inputs.empty() || taskData->outputs.empty()) ||
      (taskData->inputs_count.size() < 2 || taskData->inputs_count[0] <= 0 || taskData->inputs_count[1] <= 0) ||
      (taskData->outputs_count.size() != 1 || taskData->outputs_count[0] != taskData->inputs_count[1]))
    return false;
  return true;
  // return taskData->inputs_count[0] == 1 && taskData->outputs_count[0] == 1;
}

bool gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::run() {
  internal_order_test();

  // int cols = input_[0].size();
  // int rows = input_.size();

  for (size_t i = 0; i < input_[0].size(); i++) {
    int max_el = input_[0][i];
    for (size_t j = 1; j < input_.size(); j++)
      if (input_[j][i] > max_el) max_el = input_[j][i];

    res_[i] = max_el;
  }

  return true;
}

bool gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::post_processing() {
  internal_order_test();

  int* output_matr = reinterpret_cast<int*>(taskData->outputs[0]);

  for (size_t i = 0; i < res_.size(); i++) output_matr[i] = res_[i];
  return true;
}

std::vector<int> gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::gen_rand_vec(int size, int lower_bound,
                                                                                          int upper_bound) {
  std::vector<int> v(size);
  for (auto& number : v) number = lower_bound + (std::rand() % (upper_bound - lower_bound + 1));
  return v;
}

std::vector<std::vector<int>> gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential::gen_rand_matr(int rows,
                                                                                                        int cols) {
  std::vector<std::vector<int>> matr(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; ++i) {
    matr[i] = gen_rand_vec(cols, -500, 500);
  }
  for (int j = 0; j < cols; ++j) {
    int row_rand = std::rand() % rows;
    matr[row_rand][j] = 10;
  }
  return matr;
}

}  // namespace gordeva_t_max_val_of_column_matrix_seq
