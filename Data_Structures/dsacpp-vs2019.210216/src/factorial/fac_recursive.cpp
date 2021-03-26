/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/

#include "fac.h"
__int64_t facR ( int n ) { return ( n < 1 ) ? 1 : n * facR ( n - 1 ); } //�׳����㣨�ݹ�棩
