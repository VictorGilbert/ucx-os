/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Fri Jan 30 14:41:34 2009 
 */

/* @(#)s_floor.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "include/config.h"
#ifdef POK_NEEDS_LIBMATH

/*
 * trunc(x)
 * Return x rounded toward 0 to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to trunc(x).
 */

#include "include/libm.h"
#include "math_private.h"

static const double huge = 1.0e300;

double
trunc(double x)
{
	int32_t i0,i1,jj0;
	uint32_t i;
	EXTRACT_WORDS(i0,i1,x);
	jj0 = ((i0>>20)&0x7ff)-0x3ff;
	if(jj0<20) {
	    if(jj0<0) { 	/* raise inexact if x != 0 */
		if(huge+x>0.0) {/* |x|<1, so return 0*sign(x) */
		    i0 &= 0x80000000U;
		    i1 = 0;
		}
	    } else {
		i = (0x000fffff)>>jj0;
		if(((i0&i)|i1)==0) return x; /* x is integral */
		if(huge+x>0.0) {	/* raise inexact flag */
		    i0 &= (~i); i1=0;
		}
	    }
	} else if (jj0>51) {
	    if(jj0==0x400) return x+x;	/* inf or NaN */
	    else return x;		/* x is integral */
	} else {
	    i = ((uint32_t)(0xffffffff))>>(jj0-20);
	    if((i1&i)==0) return x;	/* x is integral */
	    if(huge+x>0.0)		/* raise inexact flag */
		i1 &= (~i);
	}
	INSERT_WORDS(x,i0,i1);
	return x;
}

#endif
