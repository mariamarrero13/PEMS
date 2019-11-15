/*
 * Copyright (c) 2015-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== httpget.c ========
 *  HTTP Client GET example application
 */



/* POSIX Header files */
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
//#include <ti/display/Display.h>
#include <ti/net/http/httpclient.h>

#include "ti_drivers_config.h"
#include "pthread.h"

#include "semaphore.h"


#define HOSTNAME              "io.adafruit.com"
#define REQUEST_HUMIDITY      "/api/v2/diegoXdinero/feeds/weather.humidity/data?X-AIO-Key=60ea5b5a08fc459bb5ffd78ff5b3cc32"
#define REQUEST_TEMPERATURE   "/api/v2/diegoXdinero/feeds/weather.temperature/data?X-AIO-Key=60ea5b5a08fc459bb5ffd78ff5b3cc32"
#define REQUEST_CO2          "/api/v2/diegoXdinero/feeds/weather.co2/data?X-AIO-Key=60ea5b5a08fc459bb5ffd78ff5b3cc32"



#define REQUEST_URI          "/api/v2/diegoXdinero/feeds/weather.humidity/data?X-AIO-Key=60ea5b5a08fc459bb5ffd78ff5b3cc32"


#define USER_AGENT            "HTTPClient (ARM; TI-RTOS)"


#define HTTP_MIN_RECV         (256)


#define cont_type  "application/json"


#define key "X-AIO-Key:{60ea5b5a08fc459bb5ffd78ff5b3cc32}\r\nContent-Type: application/json"

#define REGISTER   "300"


#define builtBuff "{\"value\":420}"
//extern Display_Handle display;
extern sem_t ipEventSyncObj;



extern void printError(char *errString,
                       int code);

/*
 *  ======== httpTask ========
 *  Makes a HTTP GET request
 */
void* httpTask(struct info *pvParameters)
{

    struct info *args =pvParameters;


     char *jsoneo ="{\"value\":";
     char numbel[5];
     char *numero="}";

     char *final="";
     char *msg="";

ltoa( args ->values,numbel);
strcpy(msg,strcat(numbel,numero));
printf("CACHANDO %s \n",msg);

strcat(jsoneo,msg);


int parametro = (int) args -> parametro;


    bool moreDataFlag = false;
    char data[HTTP_MIN_RECV];
    int16_t ret = 0;
    int16_t len = 0;
//
//    Display_printf(display, 0, 0, "Sending a HTTP POST request to '%s'\n",
//                   jsoneo);

    HTTPClient_Handle httpClientHandle;
    int16_t statusCode;
    httpClientHandle = HTTPClient_create(&statusCode,0);
    if(statusCode < 0)
    {
        printError("httpTask: creation of http client handle failed",
                   statusCode);
    }

    ret =
        HTTPClient_setHeader(httpClientHandle,
                             HTTPClient_HFIELD_REQ_CONTENT_TYPE,
                             cont_type,strlen(cont_type)+1,
                             HTTPClient_HFIELD_PERSISTENT);
//    ret =
//            HTTPClient_setHeader(httpClientHandle,
//                                 HTTPClient_REQUEST_HEADER_MASK,
//                                 builtBuff,strlen(builtBuff)-3,
//                                 HTTPClient_HFIELD_PERSISTENT);
//    ret =
//           HTTPClient_setHeader(httpClientHandle,
//                                HTTPClient_HFIELD_REQ_AUTHORIZATION,
//                                key,sizeof(key),
//                                HTTPClient_HFIELD_PERSISTENT);
    if(ret < 0)
    {
        printError("httpTask: setting request header failed", ret);
    }

    ret = HTTPClient_connect(httpClientHandle,HOSTNAME,0,0);
    if(ret < 0)
    {
        printError("httpTask: connect failed", ret);
    }
   // Display_printf(display, 0, 0, "{\"datum\":{\"value\":\"10\"}\n");

    //Display_printf(display, 0, 0, "HEADER: %s\n",httpClientHandle );

if(parametro == 0)
    ret = HTTPClient_sendRequest(httpClientHandle,HTTP_METHOD_POST,REQUEST_TEMPERATURE,jsoneo, strlen(jsoneo),0);

if(parametro == 1)
    ret = HTTPClient_sendRequest(httpClientHandle,HTTP_METHOD_POST,REQUEST_HUMIDITY,jsoneo, strlen(jsoneo),0);
printf("SENT JSON : %s\n",final);
if(parametro == 2)
    ret = HTTPClient_sendRequest(httpClientHandle,REQUEST_CO2,REQUEST_CO2,jsoneo, strlen(jsoneo),0);
 //   ret = HTTPClient_sendRequest(httpClientHandle,HTTP_METHOD_GET,REQUEST_URI, NULL, 0,0);

   // Display_printf(display, 0, 0, "post ret = %d \n", ret);

    if(ret != HTTP_SC_OK)
    {
        printError("httpTask: cannot get status", ret);
    }

   // Display_printf(display, 0, 0, "HTTP Response Status Code: %d\n", ret);

    len = 0;
    do
    {
        ret = HTTPClient_readResponseBody(httpClientHandle, data, sizeof(data),
                                          &moreDataFlag);
        if(ret < 0)
        {
            printError("httpTask: response body processing failed", ret);
        }
       // Display_printf(display, 0, 0, "%.*s \r\n",ret,data);
        len += ret;
    }
    while(moreDataFlag);

   // Display_printf(display, 0, 0, "Received %d bytes of payload\n", len);

    ret = HTTPClient_disconnect(httpClientHandle);
    if(ret < 0)
    {
        printError("httpTask: disconnect failed", ret);
    }

    HTTPClient_destroy(httpClientHandle);
    return(0);
}
