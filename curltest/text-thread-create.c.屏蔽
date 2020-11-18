
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <curl/curl.h>



typedef struct evd_upload{
    char id[20];
    char illegal_time[100]; //违法时间
    unsigned char crypto[50];       //MD5校验码
    char gps[20];          //GPS纬度信息
    char plate[20];        //车牌
    char carType[20];      //车型
    char wfID[20];         //违章类型编号
    char evdImage[100];     //违法图片
    char evdVideo[100];     //违法视频
}evd_upload_tag;


evd_upload_tag evdJGT;
//char buffer[20]="dev-01";
//evdJGT.id = "dev-01";
//memcpy(evdJGT.id, buffer, strlen(buffer)-1);



void* evdupload_thread(void *arg)
{
		printf("begin thread\n");
		//printf("evdJGT.id =  %s \n",arg->id);
               char *url="http://192.168.31.253:8002/uploadCalibrationPic";

                CURL *pCurl = NULL;
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
                    CURLFORM_COPYNAME, "deviceId",                           //此处为别的参数
                    CURLFORM_COPYCONTENTS, "dev-01",             //要上传的json字符串
                    CURLFORM_END
                );
			

/*                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "backImage",              //此处表示要传的参数名
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
		    printf("start curl_easy_perform\n");
                    res = curl_easy_perform(pCurl);
		    printf("\nfinished curl_easy_perform\n");
                    if (res != CURLE_OK)
                    {
                        printf("curl_easy_perform() failed，error code is:%s\n", curl_easy_strerror(res));
                    }
                    curl_easy_cleanup(pCurl);

                }
printf("end thread\n");
  return 0;
}
int main()
{
	static pthread_t __pid_evd_hb = 2;
int err;
printf("begin\n");


err = pthread_create(&__pid_evd_hb,NULL,evdupload_thread,(void*)&evdJGT);
	if (err !=0)
	{printf("err!=0\n");}
	else
	{printf("pthread_create secceed\n");}
sleep(1);
	printf("finished\n");
return 0;
}

