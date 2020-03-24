// ----- Davra Sample Code in C++ for Edge Devices -----
// Below code contains functionality for:
// 1) Creating or updating a Davra device
// 2) Sending in metric or event data to a device
// License: MIT License

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <curl/curl.h>

using namespace std;

//Fairly generic function for HTTP requests
int make_davra_request(string url, string bearer_token, string payload, string method) {
    CURL *hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, method.c_str());
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
    struct curl_slist *headers = NULL;
    string auth_string = "authorization: Bearer " + bearer_token;
    headers = curl_slist_append(headers, auth_string.c_str());
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, payload.c_str());
    CURLcode res = curl_easy_perform(hnd);
    long response_code;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &response_code);
    return response_code;
}

//The variables below need to be updated with appropriate values for your own server and device
int main() {

    //API endpoint for creating and updating new devices in Davra
    //More information here: http://help.davra.com/#/api/devices/createupdate
    string devices_payload = "{\"name\": \"testDeviceFromCppApp\",\"serialNumber\": \"testSerialNumberCppApp1\"}";
    string devices_endpoint = "https://demo.davra.com/api/v1/devices";

    //API endpoint for sending metric and event data to Davra
    //More information here: http://help.davra.com/#/api/iotdata/put-iotdata
    string iotdata_endpoint = "https://demo.davra.com/api/v1/iotdata";
    string iotdata_payload = "{\"UUID\": \"testSerialNumberCppApp1\",\"name\": \"rssi\",\"value\": -65,\"msg_type\": \"datum\"}";

    //Token for authentication
    string bearer_token = "your_own_token_here";

    //Create / update a device and display the HTTP response code
    printf("Creating or updating device ...\n\n");
    int devices_response = make_davra_request(devices_endpoint, bearer_token, devices_payload, "POST");
    printf("\n\nResponse from demo.davra.com devices endpoint: %d\n\n", devices_response);
    printf("Press ENTER to continue ...\n");

    //Pause execution until ENTER is pressed
    std::cin.ignore();

    //Send in metric data and display the HTTP response code
    printf("Sending data to iotdata endpoint ...");
    int iotdata_response = make_davra_request(iotdata_endpoint, bearer_token, iotdata_payload, "PUT");
    printf("\n\nResponse from demo.davra.com iotdata endpoint: %d\n\n", iotdata_response);

    return 0;
}
