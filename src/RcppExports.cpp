// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// admm_genlasso_CPP
Rcpp::List admm_genlasso_CPP(const arma::mat& A, const arma::colvec& b, const arma::mat& D, const double lambda, const double reltol, const double abstol, const int maxiter, const double rho);
RcppExport SEXP _augmentedADMM_admm_genlasso_CPP(SEXP ASEXP, SEXP bSEXP, SEXP DSEXP, SEXP lambdaSEXP, SEXP reltolSEXP, SEXP abstolSEXP, SEXP maxiterSEXP, SEXP rhoSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type A(ASEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type b(bSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type D(DSEXP);
    Rcpp::traits::input_parameter< const double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const double >::type reltol(reltolSEXP);
    Rcpp::traits::input_parameter< const double >::type abstol(abstolSEXP);
    Rcpp::traits::input_parameter< const int >::type maxiter(maxiterSEXP);
    Rcpp::traits::input_parameter< const double >::type rho(rhoSEXP);
    rcpp_result_gen = Rcpp::wrap(admm_genlasso_CPP(A, b, D, lambda, reltol, abstol, maxiter, rho));
    return rcpp_result_gen;
END_RCPP
}
// admm_genlasso_for_graph_CPP
Rcpp::List admm_genlasso_for_graph_CPP(const arma::mat& A, const arma::colvec& b, const arma::mat& D, const arma::mat& C, const double lambda1, const double lambda2, const double reltol, const double rho, const double abstol, const int maxiter);
RcppExport SEXP _augmentedADMM_admm_genlasso_for_graph_CPP(SEXP ASEXP, SEXP bSEXP, SEXP DSEXP, SEXP CSEXP, SEXP lambda1SEXP, SEXP lambda2SEXP, SEXP reltolSEXP, SEXP rhoSEXP, SEXP abstolSEXP, SEXP maxiterSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type A(ASEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type b(bSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type D(DSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type C(CSEXP);
    Rcpp::traits::input_parameter< const double >::type lambda1(lambda1SEXP);
    Rcpp::traits::input_parameter< const double >::type lambda2(lambda2SEXP);
    Rcpp::traits::input_parameter< const double >::type reltol(reltolSEXP);
    Rcpp::traits::input_parameter< const double >::type rho(rhoSEXP);
    Rcpp::traits::input_parameter< const double >::type abstol(abstolSEXP);
    Rcpp::traits::input_parameter< const int >::type maxiter(maxiterSEXP);
    rcpp_result_gen = Rcpp::wrap(admm_genlasso_for_graph_CPP(A, b, D, C, lambda1, lambda2, reltol, rho, abstol, maxiter));
    return rcpp_result_gen;
END_RCPP
}
// aug_admm_genlasso_CPP
Rcpp::List aug_admm_genlasso_CPP(const arma::mat& A, const arma::colvec& b, const arma::mat& D, const arma::mat& M, const double lambda, const double reltol, const double abstol, const int maxiter, const double rho);
RcppExport SEXP _augmentedADMM_aug_admm_genlasso_CPP(SEXP ASEXP, SEXP bSEXP, SEXP DSEXP, SEXP MSEXP, SEXP lambdaSEXP, SEXP reltolSEXP, SEXP abstolSEXP, SEXP maxiterSEXP, SEXP rhoSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type A(ASEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type b(bSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type D(DSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type M(MSEXP);
    Rcpp::traits::input_parameter< const double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const double >::type reltol(reltolSEXP);
    Rcpp::traits::input_parameter< const double >::type abstol(abstolSEXP);
    Rcpp::traits::input_parameter< const int >::type maxiter(maxiterSEXP);
    Rcpp::traits::input_parameter< const double >::type rho(rhoSEXP);
    rcpp_result_gen = Rcpp::wrap(aug_admm_genlasso_CPP(A, b, D, M, lambda, reltol, abstol, maxiter, rho));
    return rcpp_result_gen;
END_RCPP
}
// aug_admm_genlasso_for_graph_CPP
Rcpp::List aug_admm_genlasso_for_graph_CPP(const arma::mat& A, const arma::colvec& b, const arma::mat& D, const arma::mat& M, const arma::mat& C, const double lambda1, const double lambda2, const double reltol, const double abstol, const int maxiter, const double rho);
RcppExport SEXP _augmentedADMM_aug_admm_genlasso_for_graph_CPP(SEXP ASEXP, SEXP bSEXP, SEXP DSEXP, SEXP MSEXP, SEXP CSEXP, SEXP lambda1SEXP, SEXP lambda2SEXP, SEXP reltolSEXP, SEXP abstolSEXP, SEXP maxiterSEXP, SEXP rhoSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type A(ASEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type b(bSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type D(DSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type M(MSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type C(CSEXP);
    Rcpp::traits::input_parameter< const double >::type lambda1(lambda1SEXP);
    Rcpp::traits::input_parameter< const double >::type lambda2(lambda2SEXP);
    Rcpp::traits::input_parameter< const double >::type reltol(reltolSEXP);
    Rcpp::traits::input_parameter< const double >::type abstol(abstolSEXP);
    Rcpp::traits::input_parameter< const int >::type maxiter(maxiterSEXP);
    Rcpp::traits::input_parameter< const double >::type rho(rhoSEXP);
    rcpp_result_gen = Rcpp::wrap(aug_admm_genlasso_for_graph_CPP(A, b, D, M, C, lambda1, lambda2, reltol, abstol, maxiter, rho));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_augmentedADMM_admm_genlasso_CPP", (DL_FUNC) &_augmentedADMM_admm_genlasso_CPP, 8},
    {"_augmentedADMM_admm_genlasso_for_graph_CPP", (DL_FUNC) &_augmentedADMM_admm_genlasso_for_graph_CPP, 10},
    {"_augmentedADMM_aug_admm_genlasso_CPP", (DL_FUNC) &_augmentedADMM_aug_admm_genlasso_CPP, 9},
    {"_augmentedADMM_aug_admm_genlasso_for_graph_CPP", (DL_FUNC) &_augmentedADMM_aug_admm_genlasso_for_graph_CPP, 11},
    {NULL, NULL, 0}
};

RcppExport void R_init_augmentedADMM(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}