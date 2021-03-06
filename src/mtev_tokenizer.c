/* Generated by re2c 0.12.3 on Thu May 14 00:29:12 2009 */
#line 1 "mtev_tokenizer.re"
/*
 * Copyright (c) 2007, OmniTI Computer Consulting, Inc.
 * All rights reserved.
 * Copyright (c) 2015, Circonus, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name OmniTI Computer Consulting, Inc. nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mtev_defines.h"
#include <stdlib.h>
#include <string.h>

struct token {
  char *token;
  const char *start;
  const char *end;
  const char *next;
  enum { NT_IDENT, NT_DQSTRING, NT_SPACE, NT_UNKNOWN, NT_EOF } type;
};
#define SET_TOKEN(t,a) (t)->next = (a)

static void c_unescape(char *p, char *only) {
  char *bt = p;
#define ASSIGN(a) *(bt++) = (a)
  while(p[0] != '\0') {
    if(p[0] == '\\' && p[1] != '\0' && (!only || p[1] == *only)) {
      switch(p[1]) {
        case ' ': ASSIGN(' '); p+=2; break;
        case '"': ASSIGN('"'); p+=2; break;
        case 'n': ASSIGN('\n'); p+=2; break;
        case 'r': ASSIGN('\r'); p+=2; break;
        case 't': ASSIGN('\t'); p+=2; break;
        case 'a': ASSIGN('\a'); p+=2; break;
        case 'b': ASSIGN('\b'); p+=2; break;
        case 'v': ASSIGN('\v'); p+=2; break;
        case 'f': ASSIGN('\f'); p+=2; break;
        case '0': ASSIGN('\0'); p+=2; break;
        case '\\': ASSIGN('\\'); p+=2; break;
        default: ASSIGN(*p); p++; ASSIGN(*p); p++; break;
      }
    }
    else {
      ASSIGN(*p); p++;
    }
  }
  *bt = '\0';
}

#define BAIL_UNKNOWN do { t->type = NT_UNKNOWN; return -1; } while(0)
static int token_scan(struct token *t)
{
  t->start = t->end = t->next;

 mainpattern:

#line 83 "mtev_tokenizer.c"
	{
		unsigned char yych;

		yych = (unsigned char)*t->next;
		switch(yych) {
		case 0x00:	goto yy10;
		case 0x09:
		case 0x0A:
		case 0x0D:
		case ' ':	goto yy2;
		case '"':	goto yy4;
		case '\'':	goto yy6;
		default:	goto yy8;
		}
yy2:
		++t->next;
		yych = (unsigned char)*t->next;
		goto yy17;
yy3:
#line 86 "mtev_tokenizer.re"
		{ t->token = NULL;
                      t->end = t->next;
                      t->type = NT_SPACE;
                      return 1; }
#line 108 "mtev_tokenizer.c"
yy4:
		++t->next;
#line 90 "mtev_tokenizer.re"
		{ t->type = NT_DQSTRING;
                      if(t->start != t->end) {
                        t->start++;
                        t->end = t->next - 1;
                        t->token = malloc(t->end-t->start + 1);
                        strlcpy(t->token, t->start, t->end-t->start + 1);
                        c_unescape(t->token, NULL);
                        return 1;
                      }
                      else
                        goto dqstring;
                    }
#line 124 "mtev_tokenizer.c"
yy6:
		++t->next;
#line 102 "mtev_tokenizer.re"
		{ t->type = NT_IDENT;
                      if(t->start != t->end) {
                        t->start++;
                        t->end = t->next - 1;
                        t->token = malloc(t->end-t->start + 1);
                        strlcpy(t->token, t->start, t->end-t->start + 1);
                        return 1;
                      }
                      else
                        goto sqstring;
                    }
#line 139 "mtev_tokenizer.c"
yy8:
		++t->next;
		yych = (unsigned char)*t->next;
		goto yy13;
yy9:
#line 114 "mtev_tokenizer.re"
		{ char only = ' ';
                      t->end = t->next;
                      t->type = NT_IDENT;
                      t->token = malloc(t->end-t->start + 1);
                      strlcpy(t->token, t->start, t->end-t->start + 1);
                      c_unescape(t->token, &only);
                      return 1;
                    }
#line 154 "mtev_tokenizer.c"
yy10:
		++t->next;
#line 122 "mtev_tokenizer.re"
		{ t->token = NULL;
                      t->type = NT_EOF;
                      return 0;
                    }
#line 162 "mtev_tokenizer.c"
yy12:
		++t->next;
		yych = (unsigned char)*t->next;
yy13:
		switch(yych) {
		case 0x00:
		case 0x09:
		case 0x0A:
		case 0x0D:
		case ' ':	goto yy9;
		case '\\':	goto yy14;
		default:	goto yy12;
		}
yy14:
		++t->next;
		yych = (unsigned char)*t->next;
		switch(yych) {
		case 0x00:
		case 0x09:
		case 0x0A:
		case 0x0D:	goto yy9;
		case '\\':	goto yy14;
		default:	goto yy12;
		}
yy16:
		++t->next;
		yych = (unsigned char)*t->next;
yy17:
		switch(yych) {
		case 0x09:
		case 0x0A:
		case 0x0D:
		case ' ':	goto yy16;
		default:	goto yy3;
		}
	}
#line 127 "mtev_tokenizer.re"


 sqstring:

#line 204 "mtev_tokenizer.c"
	{
		unsigned char yych;
		yych = (unsigned char)*t->next;
		switch(yych) {
		case 0x00:	goto yy23;
		case '\'':	goto yy20;
		default:	goto yy21;
		}
yy20:
#line 131 "mtev_tokenizer.re"
		{ t->end = t->next;
                      goto mainpattern; }
#line 217 "mtev_tokenizer.c"
yy21:
		++t->next;
		yych = (unsigned char)*t->next;
		switch(yych) {
		case 0x00:
		case '\'':	goto yy20;
		default:	goto yy21;
		}
yy23:
		++t->next;
#line 133 "mtev_tokenizer.re"
		{ BAIL_UNKNOWN; }
#line 230 "mtev_tokenizer.c"
	}
#line 134 "mtev_tokenizer.re"


 dqstring:

#line 237 "mtev_tokenizer.c"
	{
		unsigned char yych;
		yych = (unsigned char)*t->next;
		switch(yych) {
		case 0x00:	goto yy33;
		case '"':	goto yy29;
		case '\\':	goto yy27;
		default:	goto yy31;
		}
yy27:
		yych = (unsigned char)*++t->next;
		switch(yych) {
		case 0x00:	goto yy28;
		case '"':
		case '0':
		case '\\':
		case 'a':
		case 'b':
		case 'f':
		case 'n':
		case 'r':
		case 't':
		case 'v':	goto yy37;
		default:	goto yy35;
		}
yy28:
yy29:
		++t->next;
#line 142 "mtev_tokenizer.re"
		{ t->end = t->next--;
                      goto mainpattern;
                    }
#line 270 "mtev_tokenizer.c"
yy31:
		++t->next;
#line 145 "mtev_tokenizer.re"
		{ goto dqstring; }
#line 275 "mtev_tokenizer.c"
yy33:
		++t->next;
#line 146 "mtev_tokenizer.re"
		{ BAIL_UNKNOWN; }
#line 280 "mtev_tokenizer.c"
yy35:
		++t->next;
#line 141 "mtev_tokenizer.re"
		{ goto dqstring; }
#line 285 "mtev_tokenizer.c"
yy37:
		++t->next;
#line 139 "mtev_tokenizer.re"
		{ goto dqstring; }
#line 290 "mtev_tokenizer.c"
	}
#line 147 "mtev_tokenizer.re"

}

int mtev_tokenize(const char *input, char **vector, int *cnt) {
  struct token t;
  int i = 0;

  SET_TOKEN(&t, input);
  while(token_scan(&t) != -1) {
    switch(t.type) {
      case NT_IDENT:
      case NT_DQSTRING:
        if(i<*cnt) vector[i] = t.token;
        i++;
        break;
      case NT_SPACE:
        break;
      case NT_EOF:
        if(i<*cnt) *cnt = i;
        return i;
      case NT_UNKNOWN:
        /* UNREACHED */
        goto failure;
    }
  }
 failure:
  if(i<*cnt) *cnt = i;
  return input - t.next;
}
