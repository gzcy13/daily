#ifndef _EVD_UPLOAD_H_
#define _EVD_UPLOAD_H_
/**
 * @file    evd_upload.h
 * @author  gzcy
 * @version 0.0.1
 * @date    2020-11-11
 * @brief   将对应设备的算法带框证据图像上传给服务器
 */
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <curl/curl.h>

#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sys/time.h>

#include <curl/curl.h>
#include <curl/easy.h>

//#include "deviceInfo.h"

using namespace std;

static pthread_t __pid_evd_hb = 0;

//struct Point
//{
//	int x;
//	int y;
//};
struct EvdInfo{
    string str_device_id;   ///< 设备id
    string str_url;         ///< 设备源地址
    string str_img_path;
};



//EvdInfo evdstruct = { "dev-01","http://192.168.31.253:8002/uploadCalibrationPic"};
EvdInfo evdstruct;

#endif 
