#ifdef __cplusplus
extern "C" {
#endif
#include "lmp_f2c.h"
static integer c__1 = 1;
int zhetf2_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *info,
            ftnlen uplo_len)
{
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2, z__3, z__4, z__5, z__6;
    double sqrt(doublereal), d_lmp_imag(doublecomplex *);
    void d_lmp_cnjg(doublecomplex *, doublecomplex *);
    doublereal d__;
    integer i__, j, k;
    doublecomplex t;
    doublereal r1, d11;
    doublecomplex d12;
    doublereal d22;
    doublecomplex d21;
    integer kk, kp;
    doublecomplex wk;
    doublereal tt;
    doublecomplex wkm1, wkp1;
    integer imax, jmax;
    extern int zher_(char *, integer *, doublereal *, doublecomplex *, integer *, doublecomplex *,
                     integer *, ftnlen);
    doublereal alpha;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    integer kstep;
    logical upper;
    extern int zswap_(integer *, doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dlapy2_(doublereal *, doublereal *);
    doublereal absakk;
    extern logical disnan_(doublereal *);
    extern int xerbla_(char *, integer *, ftnlen),
        zdscal_(integer *, doublereal *, doublecomplex *, integer *);
    doublereal colmax;
    extern integer izamax_(integer *, doublecomplex *, integer *);
    doublereal rowmax;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    *info = 0;
    upper = lsame_(uplo, (char *)"U", (ftnlen)1, (ftnlen)1);
    if (!upper && !lsame_(uplo, (char *)"L", (ftnlen)1, (ftnlen)1)) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*lda < max(1, *n)) {
        *info = -4;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_((char *)"ZHETF2", &i__1, (ftnlen)6);
        return 0;
    }
    alpha = (sqrt(17.) + 1.) / 8.;
    if (upper) {
        k = *n;
    L10:
        if (k < 1) {
            goto L90;
        }
        kstep = 1;
        i__1 = k + k * a_dim1;
        absakk = (d__1 = a[i__1].r, abs(d__1));
        if (k > 1) {
            i__1 = k - 1;
            imax = izamax_(&i__1, &a[k * a_dim1 + 1], &c__1);
            i__1 = imax + k * a_dim1;
            colmax =
                (d__1 = a[i__1].r, abs(d__1)) + (d__2 = d_lmp_imag(&a[imax + k * a_dim1]), abs(d__2));
        } else {
            colmax = 0.;
        }
        if (max(absakk, colmax) == 0. || disnan_(&absakk)) {
            if (*info == 0) {
                *info = k;
            }
            kp = k;
            i__1 = k + k * a_dim1;
            i__2 = k + k * a_dim1;
            d__1 = a[i__2].r;
            a[i__1].r = d__1, a[i__1].i = 0.;
        } else {
            if (absakk >= alpha * colmax) {
                kp = k;
            } else {
                i__1 = k - imax;
                jmax = imax + izamax_(&i__1, &a[imax + (imax + 1) * a_dim1], lda);
                i__1 = imax + jmax * a_dim1;
                rowmax = (d__1 = a[i__1].r, abs(d__1)) +
                         (d__2 = d_lmp_imag(&a[imax + jmax * a_dim1]), abs(d__2));
                if (imax > 1) {
                    i__1 = imax - 1;
                    jmax = izamax_(&i__1, &a[imax * a_dim1 + 1], &c__1);
                    i__1 = jmax + imax * a_dim1;
                    d__3 = rowmax, d__4 = (d__1 = a[i__1].r, abs(d__1)) +
                                          (d__2 = d_lmp_imag(&a[jmax + imax * a_dim1]), abs(d__2));
                    rowmax = max(d__3, d__4);
                }
                if (absakk >= alpha * colmax * (colmax / rowmax)) {
                    kp = k;
                } else {
                    i__1 = imax + imax * a_dim1;
                    if ((d__1 = a[i__1].r, abs(d__1)) >= alpha * rowmax) {
                        kp = imax;
                    } else {
                        kp = imax;
                        kstep = 2;
                    }
                }
            }
            kk = k - kstep + 1;
            if (kp != kk) {
                i__1 = kp - 1;
                zswap_(&i__1, &a[kk * a_dim1 + 1], &c__1, &a[kp * a_dim1 + 1], &c__1);
                i__1 = kk - 1;
                for (j = kp + 1; j <= i__1; ++j) {
                    d_lmp_cnjg(&z__1, &a[j + kk * a_dim1]);
                    t.r = z__1.r, t.i = z__1.i;
                    i__2 = j + kk * a_dim1;
                    d_lmp_cnjg(&z__1, &a[kp + j * a_dim1]);
                    a[i__2].r = z__1.r, a[i__2].i = z__1.i;
                    i__2 = kp + j * a_dim1;
                    a[i__2].r = t.r, a[i__2].i = t.i;
                }
                i__1 = kp + kk * a_dim1;
                d_lmp_cnjg(&z__1, &a[kp + kk * a_dim1]);
                a[i__1].r = z__1.r, a[i__1].i = z__1.i;
                i__1 = kk + kk * a_dim1;
                r1 = a[i__1].r;
                i__1 = kk + kk * a_dim1;
                i__2 = kp + kp * a_dim1;
                d__1 = a[i__2].r;
                a[i__1].r = d__1, a[i__1].i = 0.;
                i__1 = kp + kp * a_dim1;
                a[i__1].r = r1, a[i__1].i = 0.;
                if (kstep == 2) {
                    i__1 = k + k * a_dim1;
                    i__2 = k + k * a_dim1;
                    d__1 = a[i__2].r;
                    a[i__1].r = d__1, a[i__1].i = 0.;
                    i__1 = k - 1 + k * a_dim1;
                    t.r = a[i__1].r, t.i = a[i__1].i;
                    i__1 = k - 1 + k * a_dim1;
                    i__2 = kp + k * a_dim1;
                    a[i__1].r = a[i__2].r, a[i__1].i = a[i__2].i;
                    i__1 = kp + k * a_dim1;
                    a[i__1].r = t.r, a[i__1].i = t.i;
                }
            } else {
                i__1 = k + k * a_dim1;
                i__2 = k + k * a_dim1;
                d__1 = a[i__2].r;
                a[i__1].r = d__1, a[i__1].i = 0.;
                if (kstep == 2) {
                    i__1 = k - 1 + (k - 1) * a_dim1;
                    i__2 = k - 1 + (k - 1) * a_dim1;
                    d__1 = a[i__2].r;
                    a[i__1].r = d__1, a[i__1].i = 0.;
                }
            }
            if (kstep == 1) {
                i__1 = k + k * a_dim1;
                r1 = 1. / a[i__1].r;
                i__1 = k - 1;
                d__1 = -r1;
                zher_(uplo, &i__1, &d__1, &a[k * a_dim1 + 1], &c__1, &a[a_offset], lda, (ftnlen)1);
                i__1 = k - 1;
                zdscal_(&i__1, &r1, &a[k * a_dim1 + 1], &c__1);
            } else {
                if (k > 2) {
                    i__1 = k - 1 + k * a_dim1;
                    d__1 = a[i__1].r;
                    d__2 = d_lmp_imag(&a[k - 1 + k * a_dim1]);
                    d__ = dlapy2_(&d__1, &d__2);
                    i__1 = k - 1 + (k - 1) * a_dim1;
                    d22 = a[i__1].r / d__;
                    i__1 = k + k * a_dim1;
                    d11 = a[i__1].r / d__;
                    tt = 1. / (d11 * d22 - 1.);
                    i__1 = k - 1 + k * a_dim1;
                    z__1.r = a[i__1].r / d__, z__1.i = a[i__1].i / d__;
                    d12.r = z__1.r, d12.i = z__1.i;
                    d__ = tt / d__;
                    for (j = k - 2; j >= 1; --j) {
                        i__1 = j + (k - 1) * a_dim1;
                        z__3.r = d11 * a[i__1].r, z__3.i = d11 * a[i__1].i;
                        d_lmp_cnjg(&z__5, &d12);
                        i__2 = j + k * a_dim1;
                        z__4.r = z__5.r * a[i__2].r - z__5.i * a[i__2].i,
                        z__4.i = z__5.r * a[i__2].i + z__5.i * a[i__2].r;
                        z__2.r = z__3.r - z__4.r, z__2.i = z__3.i - z__4.i;
                        z__1.r = d__ * z__2.r, z__1.i = d__ * z__2.i;
                        wkm1.r = z__1.r, wkm1.i = z__1.i;
                        i__1 = j + k * a_dim1;
                        z__3.r = d22 * a[i__1].r, z__3.i = d22 * a[i__1].i;
                        i__2 = j + (k - 1) * a_dim1;
                        z__4.r = d12.r * a[i__2].r - d12.i * a[i__2].i,
                        z__4.i = d12.r * a[i__2].i + d12.i * a[i__2].r;
                        z__2.r = z__3.r - z__4.r, z__2.i = z__3.i - z__4.i;
                        z__1.r = d__ * z__2.r, z__1.i = d__ * z__2.i;
                        wk.r = z__1.r, wk.i = z__1.i;
                        for (i__ = j; i__ >= 1; --i__) {
                            i__1 = i__ + j * a_dim1;
                            i__2 = i__ + j * a_dim1;
                            i__3 = i__ + k * a_dim1;
                            d_lmp_cnjg(&z__4, &wk);
                            z__3.r = a[i__3].r * z__4.r - a[i__3].i * z__4.i,
                            z__3.i = a[i__3].r * z__4.i + a[i__3].i * z__4.r;
                            z__2.r = a[i__2].r - z__3.r, z__2.i = a[i__2].i - z__3.i;
                            i__4 = i__ + (k - 1) * a_dim1;
                            d_lmp_cnjg(&z__6, &wkm1);
                            z__5.r = a[i__4].r * z__6.r - a[i__4].i * z__6.i,
                            z__5.i = a[i__4].r * z__6.i + a[i__4].i * z__6.r;
                            z__1.r = z__2.r - z__5.r, z__1.i = z__2.i - z__5.i;
                            a[i__1].r = z__1.r, a[i__1].i = z__1.i;
                        }
                        i__1 = j + k * a_dim1;
                        a[i__1].r = wk.r, a[i__1].i = wk.i;
                        i__1 = j + (k - 1) * a_dim1;
                        a[i__1].r = wkm1.r, a[i__1].i = wkm1.i;
                        i__1 = j + j * a_dim1;
                        i__2 = j + j * a_dim1;
                        d__1 = a[i__2].r;
                        z__1.r = d__1, z__1.i = 0.;
                        a[i__1].r = z__1.r, a[i__1].i = z__1.i;
                    }
                }
            }
        }
        if (kstep == 1) {
            ipiv[k] = kp;
        } else {
            ipiv[k] = -kp;
            ipiv[k - 1] = -kp;
        }
        k -= kstep;
        goto L10;
    } else {
        k = 1;
    L50:
        if (k > *n) {
            goto L90;
        }
        kstep = 1;
        i__1 = k + k * a_dim1;
        absakk = (d__1 = a[i__1].r, abs(d__1));
        if (k < *n) {
            i__1 = *n - k;
            imax = k + izamax_(&i__1, &a[k + 1 + k * a_dim1], &c__1);
            i__1 = imax + k * a_dim1;
            colmax =
                (d__1 = a[i__1].r, abs(d__1)) + (d__2 = d_lmp_imag(&a[imax + k * a_dim1]), abs(d__2));
        } else {
            colmax = 0.;
        }
        if (max(absakk, colmax) == 0. || disnan_(&absakk)) {
            if (*info == 0) {
                *info = k;
            }
            kp = k;
            i__1 = k + k * a_dim1;
            i__2 = k + k * a_dim1;
            d__1 = a[i__2].r;
            a[i__1].r = d__1, a[i__1].i = 0.;
        } else {
            if (absakk >= alpha * colmax) {
                kp = k;
            } else {
                i__1 = imax - k;
                jmax = k - 1 + izamax_(&i__1, &a[imax + k * a_dim1], lda);
                i__1 = imax + jmax * a_dim1;
                rowmax = (d__1 = a[i__1].r, abs(d__1)) +
                         (d__2 = d_lmp_imag(&a[imax + jmax * a_dim1]), abs(d__2));
                if (imax < *n) {
                    i__1 = *n - imax;
                    jmax = imax + izamax_(&i__1, &a[imax + 1 + imax * a_dim1], &c__1);
                    i__1 = jmax + imax * a_dim1;
                    d__3 = rowmax, d__4 = (d__1 = a[i__1].r, abs(d__1)) +
                                          (d__2 = d_lmp_imag(&a[jmax + imax * a_dim1]), abs(d__2));
                    rowmax = max(d__3, d__4);
                }
                if (absakk >= alpha * colmax * (colmax / rowmax)) {
                    kp = k;
                } else {
                    i__1 = imax + imax * a_dim1;
                    if ((d__1 = a[i__1].r, abs(d__1)) >= alpha * rowmax) {
                        kp = imax;
                    } else {
                        kp = imax;
                        kstep = 2;
                    }
                }
            }
            kk = k + kstep - 1;
            if (kp != kk) {
                if (kp < *n) {
                    i__1 = *n - kp;
                    zswap_(&i__1, &a[kp + 1 + kk * a_dim1], &c__1, &a[kp + 1 + kp * a_dim1], &c__1);
                }
                i__1 = kp - 1;
                for (j = kk + 1; j <= i__1; ++j) {
                    d_lmp_cnjg(&z__1, &a[j + kk * a_dim1]);
                    t.r = z__1.r, t.i = z__1.i;
                    i__2 = j + kk * a_dim1;
                    d_lmp_cnjg(&z__1, &a[kp + j * a_dim1]);
                    a[i__2].r = z__1.r, a[i__2].i = z__1.i;
                    i__2 = kp + j * a_dim1;
                    a[i__2].r = t.r, a[i__2].i = t.i;
                }
                i__1 = kp + kk * a_dim1;
                d_lmp_cnjg(&z__1, &a[kp + kk * a_dim1]);
                a[i__1].r = z__1.r, a[i__1].i = z__1.i;
                i__1 = kk + kk * a_dim1;
                r1 = a[i__1].r;
                i__1 = kk + kk * a_dim1;
                i__2 = kp + kp * a_dim1;
                d__1 = a[i__2].r;
                a[i__1].r = d__1, a[i__1].i = 0.;
                i__1 = kp + kp * a_dim1;
                a[i__1].r = r1, a[i__1].i = 0.;
                if (kstep == 2) {
                    i__1 = k + k * a_dim1;
                    i__2 = k + k * a_dim1;
                    d__1 = a[i__2].r;
                    a[i__1].r = d__1, a[i__1].i = 0.;
                    i__1 = k + 1 + k * a_dim1;
                    t.r = a[i__1].r, t.i = a[i__1].i;
                    i__1 = k + 1 + k * a_dim1;
                    i__2 = kp + k * a_dim1;
                    a[i__1].r = a[i__2].r, a[i__1].i = a[i__2].i;
                    i__1 = kp + k * a_dim1;
                    a[i__1].r = t.r, a[i__1].i = t.i;
                }
            } else {
                i__1 = k + k * a_dim1;
                i__2 = k + k * a_dim1;
                d__1 = a[i__2].r;
                a[i__1].r = d__1, a[i__1].i = 0.;
                if (kstep == 2) {
                    i__1 = k + 1 + (k + 1) * a_dim1;
                    i__2 = k + 1 + (k + 1) * a_dim1;
                    d__1 = a[i__2].r;
                    a[i__1].r = d__1, a[i__1].i = 0.;
                }
            }
            if (kstep == 1) {
                if (k < *n) {
                    i__1 = k + k * a_dim1;
                    r1 = 1. / a[i__1].r;
                    i__1 = *n - k;
                    d__1 = -r1;
                    zher_(uplo, &i__1, &d__1, &a[k + 1 + k * a_dim1], &c__1,
                          &a[k + 1 + (k + 1) * a_dim1], lda, (ftnlen)1);
                    i__1 = *n - k;
                    zdscal_(&i__1, &r1, &a[k + 1 + k * a_dim1], &c__1);
                }
            } else {
                if (k < *n - 1) {
                    i__1 = k + 1 + k * a_dim1;
                    d__1 = a[i__1].r;
                    d__2 = d_lmp_imag(&a[k + 1 + k * a_dim1]);
                    d__ = dlapy2_(&d__1, &d__2);
                    i__1 = k + 1 + (k + 1) * a_dim1;
                    d11 = a[i__1].r / d__;
                    i__1 = k + k * a_dim1;
                    d22 = a[i__1].r / d__;
                    tt = 1. / (d11 * d22 - 1.);
                    i__1 = k + 1 + k * a_dim1;
                    z__1.r = a[i__1].r / d__, z__1.i = a[i__1].i / d__;
                    d21.r = z__1.r, d21.i = z__1.i;
                    d__ = tt / d__;
                    i__1 = *n;
                    for (j = k + 2; j <= i__1; ++j) {
                        i__2 = j + k * a_dim1;
                        z__3.r = d11 * a[i__2].r, z__3.i = d11 * a[i__2].i;
                        i__3 = j + (k + 1) * a_dim1;
                        z__4.r = d21.r * a[i__3].r - d21.i * a[i__3].i,
                        z__4.i = d21.r * a[i__3].i + d21.i * a[i__3].r;
                        z__2.r = z__3.r - z__4.r, z__2.i = z__3.i - z__4.i;
                        z__1.r = d__ * z__2.r, z__1.i = d__ * z__2.i;
                        wk.r = z__1.r, wk.i = z__1.i;
                        i__2 = j + (k + 1) * a_dim1;
                        z__3.r = d22 * a[i__2].r, z__3.i = d22 * a[i__2].i;
                        d_lmp_cnjg(&z__5, &d21);
                        i__3 = j + k * a_dim1;
                        z__4.r = z__5.r * a[i__3].r - z__5.i * a[i__3].i,
                        z__4.i = z__5.r * a[i__3].i + z__5.i * a[i__3].r;
                        z__2.r = z__3.r - z__4.r, z__2.i = z__3.i - z__4.i;
                        z__1.r = d__ * z__2.r, z__1.i = d__ * z__2.i;
                        wkp1.r = z__1.r, wkp1.i = z__1.i;
                        i__2 = *n;
                        for (i__ = j; i__ <= i__2; ++i__) {
                            i__3 = i__ + j * a_dim1;
                            i__4 = i__ + j * a_dim1;
                            i__5 = i__ + k * a_dim1;
                            d_lmp_cnjg(&z__4, &wk);
                            z__3.r = a[i__5].r * z__4.r - a[i__5].i * z__4.i,
                            z__3.i = a[i__5].r * z__4.i + a[i__5].i * z__4.r;
                            z__2.r = a[i__4].r - z__3.r, z__2.i = a[i__4].i - z__3.i;
                            i__6 = i__ + (k + 1) * a_dim1;
                            d_lmp_cnjg(&z__6, &wkp1);
                            z__5.r = a[i__6].r * z__6.r - a[i__6].i * z__6.i,
                            z__5.i = a[i__6].r * z__6.i + a[i__6].i * z__6.r;
                            z__1.r = z__2.r - z__5.r, z__1.i = z__2.i - z__5.i;
                            a[i__3].r = z__1.r, a[i__3].i = z__1.i;
                        }
                        i__2 = j + k * a_dim1;
                        a[i__2].r = wk.r, a[i__2].i = wk.i;
                        i__2 = j + (k + 1) * a_dim1;
                        a[i__2].r = wkp1.r, a[i__2].i = wkp1.i;
                        i__2 = j + j * a_dim1;
                        i__3 = j + j * a_dim1;
                        d__1 = a[i__3].r;
                        z__1.r = d__1, z__1.i = 0.;
                        a[i__2].r = z__1.r, a[i__2].i = z__1.i;
                    }
                }
            }
        }
        if (kstep == 1) {
            ipiv[k] = kp;
        } else {
            ipiv[k] = -kp;
            ipiv[k + 1] = -kp;
        }
        k += kstep;
        goto L50;
    }
L90:
    return 0;
}
#ifdef __cplusplus
}
#endif