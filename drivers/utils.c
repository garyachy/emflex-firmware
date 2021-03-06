/*****************************************************************************
* File:       utils.c
*
* Created on: Apr 24, 2016
*
* Author:     rostokus
******************************************************************************

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
******************************************************************************
 */

#include "utils.h"

void reverse(char *s)
{
  char c = 0;
  int n = 0;
  int i = 0;

  if (s == 0)
  {
    return;
  }

  n = strlen(s) - 1;

  while (n > i)
  {
    c = s[n];
    s[n] = s[i];
    s[i] = c;
    i++;
    n--;
  }
  return;
}
/*
 * Float to string converting function
 *
 */
RV_t floatToStr(float f, char *rez, int len)
{
  RV_t rv = RV_FAILURE;
  float temp_f = 0.0;
  int sLen = 0;

  if (!rez)
  {
    return rv;
  }

  if (0 == osapiItoa((int)f, rez, len))
  {
    return rv;
  }

  if (f < 0)
  {
    temp_f = -f;
  }
  else
  {
    temp_f = f;
  }
  /* get remainder */
  temp_f = temp_f - (int)temp_f;

  sLen = strnlen(rez, len);
  /* 3 bytes are reserved for '.' and remainder and '\0' */
  if ((len - sLen) < 3)
  {
    return rv;
  }
  else
  {
    rez[sLen] = '.';
    rez[sLen+1] = ((int) (temp_f * 10)) + '0';
    rez[sLen+2] = '\0';
  }

  return RV_SUCCESS;
}

char *osapiItoa(int val, char *rez, uint32_t rezLen)
{
  uint32_t i = 0;
  uint32_t n = 0;
  int isNeg = 0;

  if ((rez == 0) | (rezLen < 1))
  {
    return 0;
  }

  if (val < 0)
  {
    rez[i++] = '-';
    val = -val;
    isNeg = 1;
  }

  if (val == 0)
  {
    rez[i++] = '0';
  }
  else
  {
    while (val)
    {
      n = val % 10;
      if (i < rezLen)
      {
          rez[i++] = n + '0';
      }
      else
      {
          return 0;
      }
      val /= 10;
    }
  }
  if (i < rezLen)
  {
    rez[i] = '\0';
  }
  else
  {
      return 0;
  }

  reverse(rez+isNeg);

  return rez;
}
