/*
 * Ea_Cfg.c
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include "Ea_Cfg.h"

Block_S_T Block_Arr[Num_of_Blocks] =
        { { Block_ID_1, Eight_Bytes, 0x0000 },
          { Block_ID_2, Eight_Bytes, 0x0070 },
          { Block_ID_3, Eight_Bytes, 0x0090 },
          { Block_ID_4, Eight_Bytes, 0x0150 } };

