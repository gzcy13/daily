#include <stdio.h>
#include <curl/curl.h>
 
/* <DESC>
 * Get a single file from an FTPS server.
 * </DESC>
 */
 
struct FtpFile {
  const char *filename;
  FILE *stream;
};
 
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,
                        void *stream)
{
  struct FtpFile *out=(struct FtpFile *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}
 
 
int main(void)
{


               char *url="http://192.168.74.207:8002/uploadCalibrationPic";
               //char *url="http://192.168.74.207:8080";
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
                    CURLFORM_FILE, "/home/ox/daily/curltest/yzyhanpi.jpg",                //此处表示图片文件的路径
                    CURLFORM_CONTENTTYPE, "image/jpeg",
                    CURLFORM_END);


                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "deviceId",                           //此处为别的参数
                    CURLFORM_COPYCONTENTS, "dev-01",             //要上传的json字符串
                    CURLFORM_END
                );
			

/*                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "backImage",              //此处表示要传的参数名
                    CURLFORM_FILE, "/home/ox/daily/curltest/index.png",     //此处表示图片文件的路径
                    CURLFORM_CONTENTTYPE, "image/jpeg",
                    CURLFORM_END);
*/
                pCurl = curl_easy_init();
                if (NULL != pCurl)
                {

                    //curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 5);
                    curl_easy_setopt(pCurl, CURLOPT_URL, url);
                    curl_easy_setopt(pCurl, CURLOPT_HTTPPOST, post);
		    printf("start curl_easy_perform\n");
                    res = curl_easy_perform(pCurl);
		    printf("finished curl_easy_perform\n");
                    if (res != CURLE_OK)
                    {
                        printf("curl_easy_perform() failed，error code is:%s\n", curl_easy_strerror(res));
                    }
                    curl_easy_cleanup(pCurl);

                }
  return 0;
}


