/* ---------------------------------------------------------------------
 *
 * -- Automatically Tuned Linear Algebra Software (ATLAS)
 *    (C) Copyright 2000 All Rights Reserved
 *
 * -- ATLAS routine -- Version 3.2 -- December 25, 2000
 *
 * Author         : Antoine P. Petitet
 * Originally developed at the University of Tennessee,
 * Innovative Computing Laboratory, Knoxville TN, 37996-1301, USA.
 *
 * ---------------------------------------------------------------------
 *
 * -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 * 1. Redistributions  of  source  code  must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce  the above copyright
 *    notice,  this list of conditions, and the  following disclaimer in
 *    the documentation and/or other materials provided with the distri-
 *    bution.
 * 3. The name of the University,  the ATLAS group,  or the names of its
 *    contributors  may not be used to endorse or promote products deri-
 *    ved from this software without specific written permission.
 *
 * -- Disclaimer:
 *
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO,  PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEO-
 * RY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (IN-
 * CLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ---------------------------------------------------------------------
 */
/*
 * Include files
 */
#include "atlas_refmisc.h"
#include "atlas_reflvl3.h"
#include "atlas_reflevel3.h"

void ATL_zrefsyr2kLT
(
   const int                  N,
   const int                  K,
   const double               * ALPHA,
   const double               * A,
   const int                  LDA,
   const double               * B,
   const int                  LDB,
   const double               * BETA,
   double                     * C,
   const int                  LDC
)
{
/*
 * Purpose
 * =======
 *
 * ATL_zrefsyr2kLT( ... )
 *
 * <=>
 *
 * ATL_zrefsyr2k( AtlasLower, AtlasTrans, ... )
 *
 * See ATL_zrefsyr2k for details.
 *
 * ---------------------------------------------------------------------
 */
/*
 * .. Local Variables ..
 */
   double                     t0_i, t0_r, t1_i, t1_r;
   int                        i, iali, ialj, ibli, iblj, icij, j, jai, jaj,
                              jbi, jbj, jcj, l, lda2 = ( LDA << 1 ),
                              ldb2 = ( LDB << 1 ), ldc2 = ( LDC << 1 );
/* ..
 * .. Executable Statements ..
 *
 */
   for( j = 0,      jaj  = 0,    jbj  = 0,    jcj  = 0;
        j < N; j++, jaj += lda2, jbj += ldb2, jcj += ldc2 )
   {
      for( i = j,      jai  = j*lda2, jbi  = j*ldb2, icij  = (j << 1)+jcj;
           i < N; i++, jai += lda2,   jbi += ldb2,   icij += 2 )
      {
         Mset( ATL_dZERO, ATL_dZERO, t0_r, t0_i );
         Mset( ATL_dZERO, ATL_dZERO, t1_r, t1_i );
         for( l = 0,   iali  = jai, ialj  = jaj, ibli  = jbi, iblj  = jbj;
              l < K; l++, iali += 2,   ialj += 2,   ibli += 2,   iblj += 2 )
         {
            Mmla( A[iali], A[iali+1], B[iblj], B[iblj+1], t0_r, t0_i );
            Mmla( A[ialj], A[ialj+1], B[ibli], B[ibli+1], t1_r, t1_i );
         }
         Mzelscal( BETA[0], BETA[1], C[icij], C[icij+1] );
         Mmla( ALPHA[0], ALPHA[1], t0_r, t0_i, C[icij], C[icij+1] );
         Mmla( ALPHA[0], ALPHA[1], t1_r, t1_i, C[icij], C[icij+1] );
      }
   }
/*
 * End of ATL_zrefsyr2kLT
 */
}
