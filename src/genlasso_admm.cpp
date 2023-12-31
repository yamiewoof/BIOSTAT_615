#include "utils.h"
#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
Rcpp::List admm_genlasso_CPP(const arma::mat &A, const arma::colvec &b,
                             const arma::mat &D, const double lambda,
                             const double reltol, const double abstol,
                             const int maxiter, const double rho) {
  // 1. get parameters
  //   const int m = A.n_rows;
  const int n = A.n_cols;

  // 2. set ready
  arma::colvec x(n, fill::randn);
  x /= 10.0;
  arma::colvec z(D * x);
  arma::colvec u(D * x - z);
  arma::colvec q(n, fill::zeros);
  arma::colvec zold(z);
  arma::colvec x_hat(n, fill::zeros);

  // 3. precompute static variables for x-update and factorization
  arma::mat Atb = A.t() * b;
  arma::mat U = genlasso_factor(A, rho, D.t() * D);
  arma::mat L = U.t();

  // 4. iteration
  arma::vec h_objval(maxiter, fill::zeros);
  arma::vec h_r_norm(maxiter, fill::zeros);
  arma::vec h_s_norm(maxiter, fill::zeros);
  arma::vec h_eps_pri(maxiter, fill::zeros);
  arma::vec h_eps_dual(maxiter, fill::zeros);

  // Added: Matrix to store x at each iteration
  arma::mat x_iter;

  double sqrtn = std::sqrt(static_cast<float>(n));
  int k;
  for (k = 0; k < maxiter; k++) {
    // 4-1. update 'x'
    q = Atb + rho * D.t() * (z - u); // temporary value
    x = solve(trimatu(U), solve(trimatl(L), q));
    //        if (m >= n){
    //            x = solve(trimatu(U),solve(trimatl(L),q));
    //        } else {
    //            x = q/rho -
    //            (A.t()*solve(trimatu(U),solve(trimatl(L),A*q)))/rho2;
    //        }

    // 4-2. update 'z'
    zold = z;
    z = genlasso_shrinkage(D * x + u, lambda / rho);

    // 4-3. update 'u'
    u = u + D * x - z;

    // 4-3. dianostics, reporting
    h_objval(k) = genlasso_objective(A, b, D, lambda, x, z);
    h_r_norm(k) = arma::norm(D * x - z);
    h_s_norm(k) = arma::norm(-rho * (z - zold));
    if (norm(x) > norm(-z)) {
      h_eps_pri(k) = sqrtn * abstol + reltol * norm(x);
    } else {
      h_eps_pri(k) = sqrtn * abstol + reltol * norm(-z);
    }
    h_eps_dual(k) = sqrtn * abstol + reltol * norm(rho * u);
    
    // Update x_iter by adding x as a new column
    if (k == 0) {
      x_iter = x;
    } else {
      x_iter = arma::join_horiz(x_iter, x);
    }

      // 4-4. termination
      if ((h_r_norm(k) < h_eps_pri(k)) && (h_s_norm(k) < h_eps_dual(k))) {
        break;
      }
    }

    // 5. report results
    List output;
    output["x"] = x; // coefficient function
    output["x_iter"] = x_iter;
    output["objval"] = h_objval; // |x|_1
    output["k"] = k;             // number of iterations
    output["r_norm"] = h_r_norm;
    output["s_norm"] = h_s_norm;
    output["eps_pri"] = h_eps_pri;
    output["eps_dual"] = h_eps_dual;

    return (output);
  }

  // [[Rcpp::export]]
  Rcpp::List admm_genlasso_for_graph_CPP(
      const arma::mat &A, const arma::colvec &b, const arma::mat &D,
      const arma::mat &C, const double lambda1, const double lambda2,
      const double reltol, const double abstol, const int maxiter, 
      const double rho) {
    // 1. get parameters
    const int n = A.n_rows;
    const int p = A.n_cols;
    const int m = D.n_rows - p;

    // 2. set ready
    arma::colvec x(p, fill::randn);
    x /= 10.0;
    arma::colvec z(D * x);
    arma::colvec z1 = z.head(p);
    arma::colvec z2 = z.tail(m);
    arma::colvec u(D * x - z);
    arma::colvec q(p, fill::zeros);
    arma::colvec zold(z);
    arma::colvec x_hat(p, fill::zeros);

    // 3. precompute static variables for x-update and factorization
    arma::mat Atb = A.t() * b;
    arma::mat U = genlasso_factor(A, rho, D.t() * D); // returns upper
    arma::mat L = U.t();

    // 4. iteration
    arma::vec h_objval(maxiter, fill::zeros);
    arma::vec h_r_norm(maxiter, fill::zeros);
    arma::vec h_s_norm(maxiter, fill::zeros);
    arma::vec h_eps_pri(maxiter, fill::zeros);
    arma::vec h_eps_dual(maxiter, fill::zeros);

    // Added: Matrix to store x at each iteration
    arma::mat x_iter;

    double sqrtn = std::sqrt(static_cast<float>(n));
    int k;
    for (k = 0; k < maxiter; k++) {
      arma::colvec u1 = u.head(p);
      arma::colvec u2 = u.tail(m);
      // 4-1. update 'x'
      q = Atb + rho * D.t() * (z - u / rho); // temporary value
      x = solve(trimatu(U), solve(trimatl(L), q));
      //        if (m >= n){
      //            x = solve(trimatu(U),solve(trimatl(L),q));
      //        } else {
      //            x = q/rho -
      //            (A.t()*solve(trimatu(U),solve(trimatl(L),A*q)))/rho2;
      //        }

      // 4-2. update 'z'
      zold = z;
      z1 = genlasso_shrinkage(x + u1 / rho, lambda1 / rho);
      z2 = genlasso_shrinkage(C * x + u2 / rho, lambda2 / rho);
      z = join_cols(z1, z2);

      // 4-3. update 'u'
      u = u + rho * (D * x - z);

      // 4-3. diagnostics, reporting
      h_objval(k) = genlasso_objective_graph(A, b, C, lambda1, lambda2, x, z);
      h_r_norm(k) = arma::norm(D * x - z);
      h_s_norm(k) = arma::norm(-rho * D.t() * (z - zold));
      if (norm(x) > norm(-z)) {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(D * x);
      } else {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(-z);
      }
      h_eps_dual(k) = sqrtn * abstol + reltol * norm(D.t() * u);

       // Update x_iter by adding x as a new column
      if (k == 0) {
        x_iter = x;
      } else {
        x_iter = arma::join_horiz(x_iter, x);
      }

      // 4-4. termination
      if ((h_r_norm(k) < h_eps_pri(k)) && (h_s_norm(k) < h_eps_dual(k))) {
        break;
      }
    }

    // 5. report results
    List output;
    output["x"] = x;             // coefficient function
    output["x_iter"] = x_iter;
    output["objval"] = h_objval; // |x|_1
    output["k"] = k;             // number of iterations
    output["r_norm"] = h_r_norm;
    output["s_norm"] = h_s_norm;
    output["eps_pri"] = h_eps_pri;
    output["eps_dual"] = h_eps_dual;
    return (output);
  }

  // [[Rcpp::export]]
  Rcpp::List aug_admm_genlasso_CPP(
      const arma::mat &A, const arma::colvec &b, const arma::mat &D,
      const arma::mat &M, const double lambda, const double reltol,
      const double abstol, const int maxiter, const double rho) {
    // 1. get parameters
    //   const int m = A.n_rows;
    const int n = A.n_cols;

    // 2. set ready
    arma::colvec x(n, fill::randn);
    x /= 10.0;
    arma::colvec z(D * x);
    arma::colvec u_prev(D * x - z);
    arma::colvec u(D * x - z);
    arma::colvec q(n, fill::zeros);
    arma::colvec zold(z);
    arma::colvec x_hat(n, fill::zeros);

    // 3. precompute static variables for x-update and factorization
    arma::mat Atb = A.t() * b;
    arma::mat U = genlasso_factor(A, rho, M); // returns upper
    arma::mat L = U.t();

    // 4. iteration
    arma::vec h_objval(maxiter, fill::zeros);
    arma::vec h_r_norm(maxiter, fill::zeros);
    arma::vec h_s_norm(maxiter, fill::zeros);
    arma::vec h_eps_pri(maxiter, fill::zeros);
    arma::vec h_eps_dual(maxiter, fill::zeros);

    // Create a matrix to store x at each iteration
    arma::mat x_iter;

    double sqrtn = std::sqrt(static_cast<float>(n));
    int k;
    for (k = 0; k < maxiter; k++) {
      // 4-1. update 'x'
      q = Atb - D.t() * (2 * u - u_prev) + rho / 2 * M * x +
          rho / 2 * M.t() * x; // temporary value
      x = solve(trimatu(U), solve(trimatl(L), q));
      //        if (m >= n){
      //            x = solve(trimatu(U),solve(trimatl(L),q));
      //        } else {
      //            x = q/rho -
      //            (A.t()*solve(trimatu(U),solve(trimatl(L),A*q)))/rho2;
      //        }

      // 4-2. update 'z'
      zold = z;
      z = genlasso_shrinkage(D * x + u / rho, lambda / rho);

      // 4-3. update 'u'
      u_prev = u;
      u = u + rho * (D * x - z);

      // 4-3. dianostics, reporting
      h_objval(k) = genlasso_objective(A, b, D, lambda, x, z);
      h_r_norm(k) = arma::norm(D * x - z);
      h_s_norm(k) = arma::norm(-rho * D.t() * (z - zold));
      if (norm(x) > norm(-z)) {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(D * x);
      } else {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(-z);
      }
      h_eps_dual(k) = sqrtn * abstol + reltol * norm(D.t() * u);

      if (k == 0) {
            x_iter = x;
        } else {
            x_iter = arma::join_horiz(x_iter, x);
        }

      // 4-4. termination
      if ((h_r_norm(k) < h_eps_pri(k)) && (h_s_norm(k) < h_eps_dual(k))) {
        break;
      }
    }

    // 5. report results
    List output;
    output["x"] = x; // coefficient function
    output["x_iter"] = x_iter;
    output["objval"] = h_objval; // |x|_1
    output["k"] = k;             // number of iterations
    output["r_norm"] = h_r_norm;
    output["s_norm"] = h_s_norm;
    output["eps_pri"] = h_eps_pri;
    output["eps_dual"] = h_eps_dual;

    return (output);
  }

  // [[Rcpp::export]]
  Rcpp::List aug_admm_genlasso_for_graph_CPP(
      const arma::mat &A, const arma::colvec &b, const arma::mat &D,
      const arma::mat &M, const arma::mat &C, const double lambda1,
      const double lambda2, const double reltol, const double abstol,
      const int maxiter, const double rho) {
    // 1. get parameters
    const int n = A.n_rows;
    const int p = A.n_cols;
    const int m = D.n_rows - p;

    // 2. set ready
    arma::colvec x(p, fill::randn);
    x /= 10.0;
    arma::colvec z(D * x);
    arma::colvec z1 = z.head(p);
    arma::colvec z2 = z.tail(m);
    arma::colvec u_prev(D * x - z);
    arma::colvec u(D * x - z);
    arma::colvec q(p, fill::zeros);
    arma::colvec zold(z);
    arma::colvec x_hat(p, fill::zeros);

    // 3. precompute static variables for x-update and factorization
    arma::mat Atb = A.t() * b;
    arma::mat U = genlasso_factor(A, rho, M); // returns upper
    arma::mat L = U.t();

    // 4. iteration
    arma::vec h_objval(maxiter, fill::zeros);
    arma::vec h_r_norm(maxiter, fill::zeros);
    arma::vec h_s_norm(maxiter, fill::zeros);
    arma::vec h_eps_pri(maxiter, fill::zeros);
    arma::vec h_eps_dual(maxiter, fill::zeros);

    // Added: Matrix to store x at each iteration
    arma::mat x_iter;

    double sqrtn = std::sqrt(static_cast<float>(n));
    int k;
    for (k = 0; k < maxiter; k++) {
      arma::colvec u1 = u.head(p);
      arma::colvec u2 = u.tail(m);
      // 4-1. update 'x'
      q = Atb - D.t() * (2 * u - u_prev) + rho / 2 * M * x +
          rho / 2 * M.t() * x; // temporary value
      x = solve(trimatu(U), solve(trimatl(L), q));
      //        if (m >= n){
      //            x = solve(trimatu(U),solve(trimatl(L),q));
      //        } else {
      //            x = q/rho -
      //            (A.t()*solve(trimatu(U),solve(trimatl(L),A*q)))/rho2;
      //        }

      // 4-2. update 'z'
      zold = z;
      z1 = genlasso_shrinkage(x + u1 / rho, lambda1 / rho);
      z2 = genlasso_shrinkage(C * x + u2 / rho, lambda2 / rho);
      z = join_cols(z1, z2);

      // 4-3. update 'u'
      u_prev = u;
      u = u + rho * (D * x - z);

      // 4-3. diagnostics, reporting
      h_objval(k) = genlasso_objective_graph(A, b, C, lambda1, lambda2, x, z);
      h_r_norm(k) = arma::norm(D * x - z);
      h_s_norm(k) = arma::norm(-rho * D.t() * (z - zold));
      if (norm(x) > norm(-z)) {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(D * x);
      } else {
        h_eps_pri(k) = sqrtn * abstol + reltol * norm(-z);
      }
      h_eps_dual(k) = sqrtn * abstol + reltol * norm(D.t() * u);

       // Update x_iter by adding x as a new column
      if (k == 0) {
        x_iter = x;
      } else {
        x_iter = arma::join_horiz(x_iter, x);
      }

      // 4-4. termination
      if ((h_r_norm(k) < h_eps_pri(k)) && (h_s_norm(k) < h_eps_dual(k))) {
        break;
      }
    }

    // 5. report results
    List output;
    output["x"] = x;             // coefficient function
    output["x_iter"] = x_iter;
    output["objval"] = h_objval; // |x|_1
    output["k"] = k;             // number of iterations
    output["r_norm"] = h_r_norm;
    output["s_norm"] = h_s_norm;
    output["eps_pri"] = h_eps_pri;
    output["eps_dual"] = h_eps_dual;
    return (output);
  }
