/**
 * @file main.c
 *
 * @description This file defines WebPA's main function
 *
 * Copyright (c) 2015  Comcast
 */
#include "stdlib.h"
#include "signal.h"
#include "webpa_adapter.h"
#include "libpd.h"
#ifdef FEATURE_SUPPORT_WEBCONFIG
#include <curl/curl.h>
#endif
#ifdef INCLUDE_BREAKPAD
#include "breakpad_wrapper.h"
#endif

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
#ifndef INCLUDE_BREAKPAD
static void sig_handler(int sig);
#endif
void test_Getfunction();
/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

int main()
{
        int ret = -1;

#ifdef INCLUDE_BREAKPAD
    breakpad_ExceptionHandler();
#else
	signal(SIGTERM, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGBUS, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGILL, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGALRM, sig_handler);
#endif
	const char *pComponentName = WEBPA_COMPONENT_NAME;
	WalInfo("********** Starting component: %s **********\n ", pComponentName); 
        drop_root_privilege();
	/* Backend Manager for Webpa Creation and Initilization 
    CosaWebpaBEManagerCreate( );*/
	WalInfo("B4 msgBusInit\n");
	msgBusInit(pComponentName);
	WalInfo("After msgBusInit\n");
	ret = waitForOperationalReadyCondition();
	libpd_client_mgr();
	WalInfo("Syncing backend manager with DB....\n");
	CosaWebpaSyncDB();
	WalInfo("Webpa backend manager is in sync with DB\n");

	initComponentCaching(ret);
	// Initialize Apply WiFi Settings handler
	initApplyWiFiSettings();
	initNotifyTask(ret);
#ifdef FEATURE_SUPPORT_WEBCONFIG
	curl_global_init(CURL_GLOBAL_DEFAULT);
#endif

	test_Getfunction();
	parodus_receive_wait();
#ifdef FEATURE_SUPPORT_WEBCONFIG
curl_global_cleanup();
#endif
	WalInfo("Exiting webpa main thread!!\n");
	return 1;
}

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/

void test_Getfunction()
{
	WalInfo("Inside test_Getfunction()\n");
	char *reqPayload = "{\"names\":[\"Device.DeviceInfo.X_CISCO_COM_FirmwareName\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.Enabled\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.SchemaID\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.Default.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.Default.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.InterfaceDevicesWifi.Default.OverrideTTL\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.Enabled\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.SchemaID\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.Default.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.Default.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesStatus.Default.OverrideTTL\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.Enabled\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.SchemaID\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.Default.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.Default.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.Default.OverrideTTL\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.Enabled\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.SchemaID\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.Default.ReportingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.Default.PollingPeriod\",\"Device.X_RDKCENTRAL-COM_Report.RadioInterfaceStatistics.Default.OverrideTTL\",\"Device.WiFi.SSID.10001.Enable\",\"Device.WiFi.SSID.10001.Status\",\"Device.WiFi.SSID.10001.Alias\",\"Device.WiFi.SSID.10001.Name\",\"Device.WiFi.SSID.10001.LastChange\",\"Device.WiFi.SSID.10001.LowerLayers\",\"Device.WiFi.SSID.10001.BSSID\",\"Device.WiFi.SSID.10001.MACAddress\",\"Device.WiFi.SSID.10001.SSID\",\"Device.WiFi.SSID.10001.X_COMCAST-COM_DefaultSSID\",\"Device.WiFi.SSID.10001.X_CISCO_COM_EnableOnline\",\"Device.WiFi.SSID.10001.X_CISCO_COM_RouterEnabled\",\"Device.WiFi.SSID.10001.Stats.BytesSent\",\"Device.WiFi.SSID.10001.Stats.BytesReceived\",\"Device.WiFi.SSID.10001.Stats.PacketsSent\",\"Device.WiFi.SSID.10001.Stats.PacketsReceived\",\"Device.WiFi.SSID.10001.Stats.ErrorsSent\",\"Device.WiFi.SSID.10001.Stats.ErrorsReceived\",\"Device.WiFi.SSID.10001.Stats.UnicastPacketsSent\",\"Device.WiFi.SSID.10001.Stats.UnicastPacketsReceived\",\"Device.WiFi.SSID.10001.Stats.DiscardPacketsSent\",\"Device.WiFi.SSID.10001.Stats.DiscardPacketsReceived\",\"Device.WiFi.SSID.10001.Stats.MulticastPacketsSent\",\"Device.WiFi.SSID.10001.Stats.MulticastPacketsReceived\",\"Device.WiFi.SSID.10001.Stats.BroadcastPacketsSent\",\"Device.WiFi.SSID.10001.Stats.BroadcastPacketsReceived\",\"Device.WiFi.SSID.10001.Stats.UnknownProtoPacketsReceived\",\"Device.WiFi.SSID.10001.Stats.RetransCount\",\"Device.WiFi.SSID.10001.Stats.FailedRetransCount\",\"Device.WiFi.SSID.10001.Stats.RetryCount\",\"Device.WiFi.SSID.10001.Stats.MultipleRetryCount\",\"Device.WiFi.SSID.10001.Stats.AggregatedPacketCount\",\"Device.WiFi.SSID.10001.Stats.ACKFailureCount\"],\"command\": \"GET\"}";
    	char *transactionId = "aasfsdfgeh"; 
    	char *resPayload = NULL;
	processRequest(reqPayload, transactionId, &resPayload);
}
#ifndef INCLUDE_BREAKPAD
static void sig_handler(int sig)
{

	if ( sig == SIGINT ) 
	{
		signal(SIGINT, sig_handler); /* reset it to this function */
		WalInfo("SIGINT received!\n");
	}
	else if ( sig == SIGUSR1 ) 
	{
		signal(SIGUSR1, sig_handler); /* reset it to this function */
		WalInfo("SIGUSR1 received!\n");
	}
	else if ( sig == SIGUSR2 ) 
	{
		WalInfo("SIGUSR2 received!\n");
	}
	else if ( sig == SIGCHLD ) 
	{
		signal(SIGCHLD, sig_handler); /* reset it to this function */
		WalInfo("SIGHLD received!\n");
	}
	else if ( sig == SIGPIPE ) 
	{
		signal(SIGPIPE, sig_handler); /* reset it to this function */
		WalInfo("SIGPIPE received!\n");
	}
	else if ( sig == SIGALRM ) 
	{
		signal(SIGALRM, sig_handler); /* reset it to this function */
		WalInfo("SIGALRM received!\n");
	}
	else 
	{
		WalInfo("Signal %d received!\n", sig);
		OnboardLog("Signal %d received!\n", sig);
		exit(0);
	}
	
}
#endif
