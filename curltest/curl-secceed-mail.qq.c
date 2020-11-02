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
 
  return 0;
}


