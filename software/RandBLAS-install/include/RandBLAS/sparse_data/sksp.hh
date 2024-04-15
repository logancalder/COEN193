#ifndef randblas_sksp_hh
#define randblas_sksp_hh

#include "RandBLAS/base.hh"
#include "RandBLAS/dense_skops.hh"
#include "RandBLAS/sparse_data/sksp3_to_spmm.hh"

#include "RandBLAS/exceptions.hh"

namespace RandBLAS {

using namespace RandBLAS::dense;
using namespace RandBLAS::sparse_data;


// =============================================================================
/// \fn sketch_sparse(blas::Layout layout, blas::Op opS, blas::Op opA, int64_t d,
///     int64_t n, int64_t m, T alpha, DenseSkOp<T,RNG> &S, int64_t ro_s, int64_t co_s,
///     SpMat &A, int64_t ro_a, int64_t co_a, T beta, T *B, int64_t ldb
/// ) 
/// @verbatim embed:rst:leading-slashes
/// Sketch from the left in an SpMM-like operation
///
/// .. math::
///     \mat(B) = \alpha \cdot \underbrace{\op(\submat(S))}_{d \times m} \cdot \underbrace{\op(\submat(A))}_{m \times n} + \beta \cdot \underbrace{\mat(B)}_{d \times n},    \tag{$\star$}
///
/// where :math:`\alpha` and :math:`\beta` are real scalars, :math:`\op(X)` either returns a matrix :math:`X`
/// or its transpose, :math:`A` is a sparse matrix, and :math:`S` is a dense sketching operator.
/// 
/// .. dropdown:: FAQ
///   :animate: fade-in-slide-down
///
///     **What's** :math:`\mat(B)` **?**
///
///       It's matrix of shape :math:`d \times n`. Its contents are determined by :math:`(B, \ldb)`
///       and "layout", following the same convention as the Level 3 BLAS function "GEMM."
///
///     **What are** :math:`\submat(S)` **and** :math:`\submat(A)` **?**
///
///       Their shapes are determined implicitly by :math:`(\opS, d, m)` and :math:`(\opA, n, m)`.
///       If :math:`{\submat(X)}` is of shape :math:`r \times c`,
///       then it is the :math:`r \times c` submatrix of :math:`{X}` whose upper-left corner
///       appears at index :math:`(\texttt{ro_x}, \texttt{co_x})` of :math:`{X}`.
///
/// .. dropdown:: Full parameter descriptions
///     :animate: fade-in-slide-down
///
///      layout - [in]
///       * Layout::ColMajor or Layout::RowMajor.
///       * Matrix storage for :math:`\mat(B)`.
///
///      opS - [in]
///       * If :math:`\opS` = NoTrans, then :math:`\op(\submat(S)) = \submat(S)`.
///       * If :math:`\opS` = Trans, then :math:`\op(\submat(S)) = \submat(S)^T`.
///
///      opA - [in]
///       * If :math:`\opA` = NoTrans, then :math:`\op(\submat(A)) = \submat(A)`.
///       * If :math:`\opA` = Trans, then :math:`\op(\submat(A)) = \submat(A)^T`.
///
///      d - [in]
///       * A nonnegative integer.
///       * The number of rows in :math:`\mat(B)`.
///       * The number of rows in :math:`\op(\submat(S))`.
///
///      n - [in]
///       * A nonnegative integer.
///       * The number of columns in :math:`\mat(B)`.
///       * The number of columns in :math:`\op(\mat(A))`.
///
///      m - [in]
///       * A nonnegative integer.
///       * The number of columns in :math:`\op(\submat(S))`
///       * The number of rows in :math:`\op(\mat(A))`.
///
///      alpha - [in]
///       * A real scalar.
///       * If zero, then :math:`A` is not accessed.
///
///      S - [in]
///       * A DenseSkOp object.
///       * Defines :math:`\submat(S)`.
///
///      ro_s - [in]
///       * A nonnegative integer.
///       * The rows of :math:`\submat(S)` are a contiguous subset of rows of :math:`S`.
///       * The rows of :math:`\submat(S)` start at :math:`S[\texttt{ro_s}, :]`.
///
///      co_s - [in]
///       * A nonnegative integer.
///       * The columns of :math:`\submat(S)` are a contiguous subset of columns of :math:`S`.
///       * The columns :math:`\submat(S)` start at :math:`S[:,\texttt{co_s}]`. 
///
///      A - [in]
///       * A RandBLAS sparse matrix object.
///       * Defines :math:`\submat(A)`.
///
///      ro_a - [in]
///       * A nonnegative integer.
///       * The rows of :math:`\submat(A)` are a contiguous subset of rows of :math:`A`.
///       * The rows of :math:`\submat(A)` start at :math:`A[\texttt{ro_a}, :]`.
///
///      co_a - [in]
///       * A nonnegative integer.
///       * The columns of :math:`\submat(A)` are a contiguous subset of columns of :math:`A`.
///       * The columns :math:`\submat(A)` start at :math:`A[:,\texttt{co_a}]`. 
///
///      beta - [in]
///       * A real scalar.
///       * If zero, then :math:`B` need not be set on input.
///
///      B - [in, out]
///       * Pointer to 1D array of real scalars.
///       * On entry, defines :math:`\mat(B)`
///         on the RIGHT-hand side of :math:`(\star)`.
///       * On exit, defines :math:`\mat(B)`
///         on the LEFT-hand side of :math:`(\star)`.
///
///      ldb - [in]
///       * A nonnegative integer.
///       * Leading dimension of :math:`\mat(B)` when reading from :math:`B`.
///
/// @endverbatim
template <typename T, SparseMatrix SpMat, typename RNG>
inline void sketch_sparse(
    blas::Layout layout,
    blas::Op opS,
    blas::Op opA,
    int64_t d, // B is d-by-n
    int64_t n, // op(submat(A)) is m-by-n
    int64_t m, // op(submat(S)) is d-by-m
    T alpha,
    DenseSkOp<T, RNG> &S,
    int64_t ro_s,
    int64_t co_s,
    SpMat &A,
    int64_t ro_a,
    int64_t co_a,
    T beta,
    T *B,
    int64_t ldb
) {
    sparse_data::lsksp3(layout, opS, opA, d, n, m, alpha, S, ro_s, co_s, A, ro_a, co_a, beta, B, ldb);
    return;
}


// =============================================================================
/// \fn sketch_sparse(blas::Layout layout, blas::Op opS, blas::Op opA, int64_t d,
///     int64_t n, int64_t m, T alpha, SpMat &A, int64_t ro_a, int64_t co_a,
///     DenseSkOp<T,RNG> &S, int64_t ro_s, int64_t co_s, T beta, T *B, int64_t ldb
/// ) 
/// @verbatim embed:rst:leading-slashes
/// Sketch from the right in an SpMM-like operation
///
/// .. math::
///     \mat(B) = \alpha \cdot \underbrace{\op(\submat(A))}_{m \times n} \cdot \underbrace{\op(\submat(S))}_{n \times d} + \beta \cdot \underbrace{\mat(B)}_{m \times d},    \tag{$\star$}
///
/// where :math:`\alpha` and :math:`\beta` are real scalars, :math:`\op(X)` either returns a matrix :math:`X`
/// or its transpose, :math:`A` is a sparse matrix, and :math:`S` is a dense sketching operator.
/// 
/// .. dropdown:: FAQ
///   :animate: fade-in-slide-down
///
///     **What's** :math:`\mat(B)` **?**
///
///       It's matrix of shape :math:`m \times d`. Its contents are determined by :math:`(B, \ldb)`
///       and "layout", following the same convention as the Level 3 BLAS function "GEMM."
///
///     **What are** :math:`\submat(S)` **and** :math:`\submat(A)` **?**
///
///       Their shapes are determined implicitly by :math:`(\opS, n, d)` and :math:`(\opA, m, n)`.
///       If :math:`{\submat(X)}` is of shape :math:`r \times c`,
///       then it is the :math:`r \times c` submatrix of :math:`{X}` whose upper-left corner
///       appears at index :math:`(\texttt{ro_x}, \texttt{co_x})` of :math:`{X}`.
///
/// .. dropdown:: Full parameter descriptions
///     :animate: fade-in-slide-down
///
///      layout - [in]
///       * Layout::ColMajor or Layout::RowMajor.
///       * Matrix storage for :math:`\mat(B)`.
///
///      opA - [in]
///       * If :math:`\opA` == NoTrans, then :math:`\op(\submat(A)) = \submat(A)`.
///       * If :math:`\opA` == Trans, then :math:`\op(\submat(A)) = \submat(A)^T`.
///
///      opS - [in]
///       * If :math:`\opS` = NoTrans, then :math:`\op(\submat(S)) = \submat(S)`.
///       * If :math:`\opS` = Trans, then :math:`\op(\submat(S)) = \submat(S)^T`.
///
///      m - [in]
///       * A nonnegative integer.
///       * The number of rows in :math:`\mat(B)`.
///       * The number of rows in :math:`\op(\submat(A))`.
///
///      d - [in]
///       * A nonnegative integer.
///       * The number of columns in :math:`\mat(B)`
///       * The number of columns in :math:`\op(\submat(S))`.
///
///      n - [in]
///       * A nonnegative integer.
///       * The number of columns in :math:`\op(\submat(A))`
///       * The number of rows in :math:`\op(\submat(S))`.
///
///      alpha - [in]
///       * A real scalar.
///       * If zero, then :math:`A` is not accessed.
///
///      S - [in]
///       * A DenseSkOp object.
///       * Defines :math:`\submat(S)`.
///
///      ro_s - [in]
///       * A nonnegative integer.
///       * The rows of :math:`\submat(S)` are a contiguous subset of rows of :math:`S`.
///       * The rows of :math:`\submat(S)` start at :math:`S[\texttt{ro_s}, :]`.
///
///      co_s - [in]
///       * A nonnegative integer.
///       * The columns of :math:`\submat(S)` are a contiguous subset of columns of :math:`S`.
///       * The columns :math:`\submat(S)` start at :math:`S[:,\texttt{co_s}]`. 
///
///      A - [in]
///       * A RandBLAS sparse matrix object.
///       * Defines :math:`\submat(A)`.
///
///      ro_a - [in]
///       * A nonnegative integer.
///       * The rows of :math:`\submat(A)` are a contiguous subset of rows of :math:`A`.
///       * The rows of :math:`\submat(A)` start at :math:`A[\texttt{ro_a}, :]`.
///
///      co_a - [in]
///       * A nonnegative integer.
///       * The columns of :math:`\submat(A)` are a contiguous subset of columns of :math:`A`.
///       * The columns :math:`\submat(A)` start at :math:`A[:,\texttt{co_a}]`. 
///
///      beta - [in]
///       * A real scalar.
///       * If zero, then :math:`B` need not be set on input.
///
///      B - [in, out]
///       * Pointer to 1D array of real scalars.
///       * On entry, defines :math:`\mat(B)`
///         on the RIGHT-hand side of :math:`(\star)`.
///       * On exit, defines :math:`\mat(B)`
///         on the LEFT-hand side of :math:`(\star)`.
///
///      ldb - [in]
///       * A nonnegative integer.
///       * Leading dimension of :math:`\mat(B)` when reading from :math:`B`.
///
/// @endverbatim
template <typename T, SparseMatrix SpMat, typename RNG>
inline void sketch_sparse(
    blas::Layout layout,
    blas::Op opA,
    blas::Op opS,
    int64_t m, // B is m-by-d
    int64_t d, // op(submat(A)) is m-by-n
    int64_t n, // op(submat(S)) is n-by-d
    T alpha,
    SpMat &A,
    int64_t ro_a,
    int64_t co_a,
    DenseSkOp<T, RNG> &S,
    int64_t ro_s,
    int64_t co_s,
    T beta,
    T *B,
    int64_t ldb
) {
    sparse_data::rsksp3(layout, opA, opS, m, d, n, alpha, A, ro_a, co_a, S, ro_s, co_s, beta, B, ldb);
    return;
}

}  // end namespace RandBLAS
#endif
