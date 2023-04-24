/* 
Copyright 2023 Ajax

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.

You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
    
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. 
*/
#ifndef TEMPLATE
#define TEMPLATE


#define TEMPLATE_RESULT_SIZE 4096
#define TEMPLATE_DEC_SIZE 20
#define DEC_NUM 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Kvmap {
	int type;
	char* key;
	char* value;					// #	1
	
	char* dec[ DEC_NUM ];
	void (*Func)(char*, char *);			// 
};

typedef struct template_name_path {
	char  name[64];
	char* template_data;
} template_name_path;

typedef struct template_dec {
	int size;
	template_name_path template_np[ TEMPLATE_DEC_SIZE ];
} template_dec;

#ifdef __cplusplus
extern "C" {
#endif

	void template_init();

	void template_free();

	char* get_template(char* template_name);

	char * local_template(char * template_path);

	static void parse_dec(char* tt, char* dec[], char* inner);

	char * parse_context(char *context, struct Kvmap *kv, int kv_num);

#ifdef __cplusplus
}		/* end of the 'extern "C"' block */
#endif

#endif