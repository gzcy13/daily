/**
 * @file    evd_upload.cpp
 * @author  gzcy
 * @version 0.0.1
 * @date    2020-11-11
 * @brief   将对应设备的算法带框证据图像上传给服务器
 */
#include"evd_upload.h"
#include "json/json.h"
#include<fstream>
#include<sstream>
string pending = "pending.txt";



void delLine(int linnum) 
{
	int i = 0;
	ifstream in(pending.c_str());  // 以读方式打开文件
	string data = "";  // 保存文件内容
	string line, tmp;
	while (getline(in, line)) {
		//istringstream is(line);
		//is >> tmp;
		if (i >= linnum)
			data += (line+"\n");//将第num之后的行内容复制给data
		i ++;
	}
	in.close();  // 关闭文件
	ofstream os(pending.c_str());  // 以写方式打开文件，会删掉文件中的所有内容
	os << data;  // data通过os写回文件pengding.txt
	os.close();
}

void GetPendingInfo(void) 
{

	ifstream in(pending.c_str());  // 以读方式打开文件
	string line;

	/*****************get_upload********************/
	getline(in, line);
	evdstruct.str_device_id = line;
	getline(in, line);
	evdstruct.str_url = line;
	getline(in, line);
	evdstruct.str_img_path = line;
	printf("str_device_id = %s\n",(evdstruct.str_device_id).c_str());
	printf("str_url = %s\n",(evdstruct.str_url).c_str());
	printf("str_img_path = %s\n",(evdstruct.str_img_path).c_str());
	in.close();  // 关闭文件
}


void * evdupload_thread(void * paramJGT)
{
		int CheckIfContinue =1;
		printf("-----------------begin thread-------------------------- \n");
		printf("pending = %s\n",pending.c_str());
	while(CheckIfContinue)
	{
		string checkstring;
		ifstream in(pending.c_str());  // 以读方式打开文件
		getline(in, checkstring);
		if(0 == checkstring.length())
		{
			CheckIfContinue = 0;

			in.close();  // 关闭文件
			printf("pending file is null, path = %s\n",pending.c_str());
		}
            	else{
			in.close();  // 关闭文件
			GetPendingInfo();
            }
		//printf("CheckIfContinue = %d\n",CheckIfContinue);


		EvdInfo param_evdstruct =(EvdInfo)(*((EvdInfo*) paramJGT));//复制形参，转换格式
		printf("str_device_id = %s\n",(param_evdstruct.str_device_id).c_str());
		printf("str_url = %s\n",(param_evdstruct.str_url).c_str());
                CURL *pCurl = NULL;
                char *url;
		int len = param_evdstruct.str_url.length();
		url = (char *)malloc((len+1)*sizeof(char));//传递地址
		strcpy(url,(param_evdstruct.str_url).c_str());		
		printf("url = %s\n",url);

                CURLcode res;

		
		/* structure to be used as parameter for CURLFORM_ARRAY */
		struct curl_forms {
		  CURLformoption option;
		  const char     *value;
		};

                struct curl_slist *headerlist = NULL;
                struct curl_httppost *post = NULL;
                struct curl_httppost *last = NULL;

                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "image",                     //此处表示要传的参数名
                    CURLFORM_FILE, "./yzyhanpi.jpg",                //此处表示图片文件的路径
                    CURLFORM_CONTENTTYPE, "image/jpeg",
                    CURLFORM_END);

                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "deviceId",                //此处为别的参数
                    CURLFORM_COPYCONTENTS, (param_evdstruct.str_device_id).c_str(),             //要上传的json字符串
                    CURLFORM_END
                );
			

/*                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "backImage",    //此处表示要传的参数名
                    CURLFORM_FILE, "./index.png",     //此处表示图片文件的路径
                    CURLFORM_CONTENTTYPE, "image/jpeg",
                    CURLFORM_END);
*/
		printf("begin curl_easy_init \n");
                pCurl = curl_easy_init();
                if (NULL != pCurl)
                {

                    //curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 5);
                    curl_easy_setopt(pCurl, CURLOPT_URL, url);
                    curl_easy_setopt(pCurl, CURLOPT_HTTPPOST, post);
		    printf("begin curl_easy_perform\n");
                    res = curl_easy_perform(pCurl);
		    printf("\nfinished curl_easy_perform\n");
                    if (res != CURLE_OK)
                    {
                        printf("curl_easy_perform() failed，error code is:%s\n", curl_easy_strerror(res));
                    }
                    curl_easy_cleanup(pCurl);
                }
		//delete 3 line after upload evidence
		delLine(3);	

	}
  return 0;
}

#if 1
int main()
{
	int err;
			
		err = pthread_create(&__pid_evd_hb, 0, evdupload_thread, (void*)&evdstruct);
		if(err != 0)
		{
		printf("pthread create err\n");
		}


	while(1);
	return 0;
}
#endif

