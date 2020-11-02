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
#if 0
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile={
    "myfile.txt", /* name to store the file as if successful */
    NULL
  };
 
  printf("come in\n");
  //return 0;
  
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
  printf("begin curl_easy_setopt\n");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");
    curl_easy_setopt(curl, CURLOPT_URL, "https://mail.qq.com");
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 
    /* We activate SSL and we require it for both control and data */
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    /* always cleanup */
    curl_easy_cleanup(curl);
 
    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 
  curl_global_cleanup();
#endif


               char *url="http://192.168.74.207:8080/uploadCalibrationPic";
               //char *url="http://192.168.74.207:8080";
                CURL *pCurl = NULL;
                CURLcode res;

                struct curl_slist *headerlist = NULL;

                                struct curl_httppost *post = NULL;
                struct curl_httppost *last = NULL;

                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "image",                     //此处表示要传的参数名
                    CURLFORM_FILE, "/home/ox/daily/curltest/yzyhanpi.jpg",                //此处表示图片文件的路径
                    CURLFORM_CONTENTTYPE, "image/jpeg",
                    CURLFORM_END);


                curl_formadd(&post, &last,
                    CURLFORM_COPYNAME, "body",                           //此处为别的参数
                    CURLFORM_COPYCONTENTS, "yzyhanpi",             //要上传的json字符串
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

                    res = curl_easy_perform(pCurl);
                    if (res != CURLE_OK)
                    {
                        printf("curl_easy_perform() failed，error code is:%s\n", curl_easy_strerror(res));
                    }


                    curl_easy_cleanup(pCurl);

                }
  return 0;
}


