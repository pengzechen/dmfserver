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
#ifndef REQUEST
#define REQUEST


// #define MULTI_DEBUG
// #define REQUEST_DEBUG

#define BODY_MAX 1024*1024				// body 数据大小
#define MULTI_PART_MAX 1024*1024		// multipart 数据大小
#define MULTI_PART_MAX_NUM 20			// 最大multipart 数量

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Multi_kv {
	char key[32];
	char data[64];
};

struct Multipart {
	struct Multi_kv name;
	struct Multi_kv dis;
	struct Multi_kv filename;
	char *data;
	int length;
};

struct Query {
	char key[64];
	char data[512];
};

struct Params {
	char key[64];
	char data[256];
};

struct Body {
	char *body;
	int length;
};

struct req {
	char method[5];
	char path[512];
	char protocol[5];
	char version[4];
	
	int q_int;
	int p_int;
	int multi_part_num;
	
	struct Query query[10];
	struct Params params[20];
	struct Body body;
	
	struct Multipart *multi[MULTI_PART_MAX_NUM];
};

typedef struct req Request;

#ifdef __cplusplus
extern "C" {
#endif

	static void MultiParse (Request *request, char *boundary );

	void ParseHttp(Request *request, char *data);

	void freeReq(Request *req);


#ifdef __cplusplus
}		/* end of the 'extern "C"' block */
#endif

#endif // REQUEST