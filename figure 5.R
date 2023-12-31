###
# Testing with data generated from ADMM package
# augADMM for graph with different D
###

library(microbenchmark)
library(ggplot2)
library(Matrix)
library(augmentedADMM)
source("gen_data_v2.R")

set.seed(123)

# Define different problem sizes
problem_sizes <- seq(100, 300, by = 100)
multipliers <- c(1, 5, 10)

# Data frame to store the results
benchmark_results <- data.frame(size = integer(), method = character(), time = numeric())

for (dim in problem_sizes) {
  for (m in multipliers) {
    data_params <- list(num.groups = dim, num.vars.per.group=11,
                        n = 200, num.active.groups=4, cor=0.7, err.var=0.1)
    data <- do.call(gen_data, data_params)

    X <- data$X
    Y <- data$Y
    D <- data$A
    C <- data$C
    M <- diag(m * norm(D, "2"), nrow = ncol(D), ncol = ncol(D))

    # Set regularization lambda value
    lambda1 <- 0.5
    lambda2 <- 0.1

    # Benchmark augmented ADMM
    cat(sprintf("Benchmarking augmented ADMM for graph for size: %d; M: %d...\n", dim, m))
    admm_aug_for_graph_bench <- microbenchmark(
      aug_admm_genlasso_for_graph(X, Y, D, M, C, lambda1, lambda2),
      times = 10
    )

    # Store the results
    benchmark_results <- rbind(benchmark_results,
                               data.frame(size = dim, M = sprintf("%d||D_opt||^2 *I", m), time = median(admm_aug_for_graph_bench$time)))
  }
}

benchmark_results$time <- benchmark_results$time / 1e9

# Plot the results
ggplot(benchmark_results, aes(x = size, y = time, color = M)) +
  geom_line() +
  geom_point() +
  labs(title = "Run Time Comparison between Standard ADMM and Augmented ADMM for graph",
       x = "Problem Size (n)", y = "Time (seconds)") +
  theme_minimal() +
  scale_y_continuous(labels = scales::comma) # To format the y axis with commas

# Save the plot to a file
ggsave("augmentedADMM/output/aug_admm_for_graph_w_diff_M_runtime_comparison.png", device = "png", width = 10, height = 6, dpi=300)


