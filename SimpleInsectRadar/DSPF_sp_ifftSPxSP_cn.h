#pragma once

#include <math.h>

#include <stdio.h>

void tw_gen (float *w, int n);


void DSPF_sp_ifftSPxSP_cn (int N, float *ptr_x, float *ptr_w, float *ptr_y,
	unsigned char *brev, int n_min, int offset, int n_max);

unsigned int _bitr(unsigned int a) ;