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

/* s_rintf.c -- float version of s_rint.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

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

#include "include/libm.h"
#include "math_private.h"

static const float
TWO23[2]={
  8.3886080000e+06, /* 0x4b000000 */
 -8.3886080000e+06, /* 0xcb000000 */
};

float
rintf(float x)
{
	int32_t i0,jj0,sx;
	uint32_t i,i1;
#ifdef __i386__ /* XXX gcc4 will omit the rounding otherwise */
	volatile
#endif
		float w;
	float t;
	GET_FLOAT_WORD(i0,x);
	sx = (i0>>31)&1;
	jj0 = ((i0>>23)&0xff)-0x7f;
	if(jj0<23) {
	    if(jj0<0) {
		if((i0&0x7fffffff)==0) return x;
		i1 = (i0&0x07fffff);
		i0 &= 0xfff00000;
		i0 |= ((i1|-i1)>>9)&0x400000;
		SET_FLOAT_WORD(x,i0);
	        w = TWO23[sx]+x;
	        t =  w-TWO23[sx];
		GET_FLOAT_WORD(i0,t);
		SET_FLOAT_WORD(t,(i0&0x7fffffff)|(sx<<31));
	        return t;
	    } else {
		i = (0x007fffff)>>jj0;
		if((i0&i)==0) return x; /* x is integral */
		i>>=1;
		if((i0&i)!=0) i0 = (i0&(~i))|((0x100000)>>jj0);
	    }
	} else {
	    if(jj0==0x80) return x+x;	/* inf or NaN */
	    else return x;		/* x is integral */
	}
	SET_FLOAT_WORD(x,i0);
	w = TWO23[sx]+x;
	return w-TWO23[sx];
}

#endif
