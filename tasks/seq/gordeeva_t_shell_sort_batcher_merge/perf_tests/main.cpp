#include <gtest/gtest.h>

#include <vector>

#include "core/perf/include/perf.hpp"
#include "seq/gordeeva_t_shell_sort_batcher_merge/include/ops_seq.hpp"

TEST(gordeeva_t_shell_sort_batcher_merge_seq, test_pipeline_run) {
  const int sz_vec = 500;

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();

  auto testTaskSequential = std::make_shared<gordeeva_t_shell_sort_batcher_merge_seq::TestTaskSequential>(taskDataSeq);

  std::vector<int> vect = gordeeva_t_shell_sort_batcher_merge_seq::TestTaskSequential::rand_vec(sz_vec);

  taskDataSeq->inputs_count.emplace_back(sz_vec);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vect.data()));

  std::vector<int> res(sz_vec, 0);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);

  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(gordeeva_t_shell_sort_batcher_merge_seq, test_task_run) {
  const int sz_vec = 700;

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();

  auto testTaskSequential = std::make_shared<gordeeva_t_shell_sort_batcher_merge_seq::TestTaskSequential>(taskDataSeq);

  std::vector<int> vect = gordeeva_t_shell_sort_batcher_merge_seq::TestTaskSequential::rand_vec(sz_vec);

  taskDataSeq->inputs_count.emplace_back(sz_vec);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vect.data()));

  std::vector<int> res(sz_vec, 0);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);

  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}



//TEST(sequential_example_perf_test, test_pipeline_run) {
//  const int count = 100;
//
//  // Create data
//  std::vector<int> in(1, count);
//  std::vector<int> out(1, 0);
//
//  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
//  taskDataSeq->outputs_count.emplace_back(out.size());
//
//  // Create Task
//  auto testTaskSequential = std::make_shared<nesterov_a_test_task_seq::TestTaskSequential>(taskDataSeq);
//
//  // Create Perf attributes
//  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
//  perfAttr->num_running = 10;
//  const auto t0 = std::chrono::high_resolution_clock::now();
//  perfAttr->current_timer = [&] {
//    auto current_time_point = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
//    return static_cast<double>(duration) * 1e-9;
//  };
//
//  // Create and init perf results
//  auto perfResults = std::make_shared<ppc::core::PerfResults>();
//
//  // Create Perf analyzer
//  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
//  perfAnalyzer->pipeline_run(perfAttr, perfResults);
//  ppc::core::Perf::print_perf_statistic(perfResults);
//  ASSERT_EQ(count, out[0]);
//}
//
//TEST(sequential_example_perf_test, test_task_run) {
//  const int count = 100;
//
//  // Create data
//  std::vector<int> in(1, count);
//  std::vector<int> out(1, 0);
//
//  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
//  taskDataSeq->outputs_count.emplace_back(out.size());
//
//  // Create Task
//  auto testTaskSequential = std::make_shared<nesterov_a_test_task_seq::TestTaskSequential>(taskDataSeq);
//
//  // Create Perf attributes
//  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
//  perfAttr->num_running = 10;
//  const auto t0 = std::chrono::high_resolution_clock::now();
//  perfAttr->current_timer = [&] {
//    auto current_time_point = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
//    return static_cast<double>(duration) * 1e-9;
//  };
//
//  // Create and init perf results
//  auto perfResults = std::make_shared<ppc::core::PerfResults>();
//
//  // Create Perf analyzer
//  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
//  perfAnalyzer->task_run(perfAttr, perfResults);
//  ppc::core::Perf::print_perf_statistic(perfResults);
//  ASSERT_EQ(count, out[0]);
//}
