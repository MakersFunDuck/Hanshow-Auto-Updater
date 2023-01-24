#include "tl_common.h"

#include "main.h"
#include "stack/ble/ble.h"
#include "epd_ble_service.h"
#include "ble.h"

typedef struct
{
  /** Minimum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMin;
  /** Maximum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMax;
  /** Number of LL latency connection events (0x0000 - 0x03e8) */
  u16 latency;
  /** Connection Timeout (0x000A - 0x0C80 * 10 ms) */
  u16 timeout;
} gap_periConnectParams_t;

static const u16 clientCharacterCfgUUID = GATT_UUID_CLIENT_CHAR_CFG;

static const u16 extReportRefUUID = GATT_UUID_EXT_REPORT_REF;

static const u16 reportRefUUID = GATT_UUID_REPORT_REF;

static const u16 characterPresentFormatUUID = GATT_UUID_CHAR_PRESENT_FORMAT;

static const u16 userdesc_UUID	= GATT_UUID_CHAR_USER_DESC;

static const u16 serviceChangeUUID = GATT_UUID_SERVICE_CHANGE;

static const u16 my_primaryServiceUUID = GATT_UUID_PRIMARY_SERVICE;

static const u16 my_characterUUID = GATT_UUID_CHARACTER;

static const u16 my_devServiceUUID = SERVICE_UUID_DEVICE_INFORMATION;

static const u16 my_PnPUUID = CHARACTERISTIC_UUID_PNP_ID;

static const u16 my_devNameUUID = GATT_UUID_DEVICE_NAME;

static const u16 my_gapServiceUUID = SERVICE_UUID_GENERIC_ACCESS;

static const u16 my_appearanceUIID = GATT_UUID_APPEARANCE;

static const u16 my_periConnParamUUID = GATT_UUID_PERI_CONN_PARAM;

static const u16 my_appearance = GAP_APPEARE_UNKNOWN;

static const u16 my_gattServiceUUID = SERVICE_UUID_GENERIC_ATTRIBUTE;

static const gap_periConnectParams_t my_periConnParameters = {20, 40, 0, 1000};

static u16 serviceChangeVal[2] = {0};

static u8 serviceChangeCCC[2] = {0,0};

static const u8 my_devName[] = {'E','S','L'};

static const u8 my_PnPtrs [] = {0x02, 0x8a, 0x24, 0x66, 0x82, 0x01, 0x00};

//////////////////////// Battery /////////////////////////////////////////////////
static const u16 my_batServiceUUID        = SERVICE_UUID_BATTERY;
static const u16 my_batCharUUID       	  = CHARACTERISTIC_UUID_BATTERY_LEVEL;
static u8 batteryValueInCCC[2];
RAM u8 my_batVal[1] 	= {100};

//////////////////////// Temp /////////////////////////////////////////////////
static const u16 my_tempServiceUUID       = 0x181A;
static const u16 my_tempCharUUID       	  = 0x2A1F;
static u8 tempValueInCCC[2];
RAM u8 my_tempVal[2] 	= {0};

/////////////////////////////////////////////////////////
static const  u16 my_OtaServiceUUID				= 0x221f;
static const  u16 my_OtaUUID			    = 0x331f;
static u8 my_OtaData = 0x00;
static u8  my_OtaCCC[2];

// RxTx Char
static const  u16 my_RxTxUUID				= 0x1f1f;
static const  u16 my_RxTx_ServiceUUID		= 0x1f10;
static u8 	  my_RxTx_Data 					= 0x00;
static u8 RxTxValueInCCC[2];

// EPD_BLE Char.
// 4B646063-6264-F3A7-8941-E65356EA82FE
#define EPD_BLE_CHAR_UUID 0xfe, 0x82, 0xea, 0x56, 0x53, 0xe6, 0x41, 0x89, 0xa7, 0xf3, 0x64, 0x62, 0x63, 0x60, 0x64, 0x4b
static const  u8 my_EPD_BLEUUID[16]				= { EPD_BLE_CHAR_UUID };
// 13187B10-EBA9-A3BA-044E-83D3217D9A38
#define EPD_BLE_SERVICE_UUID 0x38, 0x9a, 0x7d, 0x21, 0xd3, 0x83, 0x4e, 0x04, 0xba, 0xa3, 0xa9, 0xeb, 0x10, 0x7b, 0x18, 0x13
static const  u8 my_EPD_BLE_ServiceUUID[16]		= { EPD_BLE_SERVICE_UUID };
static u8 	  my_EPD_BLE_Data 					= 0x00;

// Include attribute (Battery service)
static const u16 include[3] = {BATT_PS_H, BATT_LEVEL_INPUT_CCB_H, SERVICE_UUID_BATTERY};


//// GAP attribute values
static const u8 my_devNameCharVal[5] = {
	CHAR_PROP_READ | CHAR_PROP_NOTIFY,
	U16_LO(GenericAccess_DeviceName_DP_H), U16_HI(GenericAccess_DeviceName_DP_H),
	U16_LO(GATT_UUID_DEVICE_NAME), U16_HI(GATT_UUID_DEVICE_NAME)
};
static const u8 my_appearanceCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(GenericAccess_Appearance_DP_H), U16_HI(GenericAccess_Appearance_DP_H),
	U16_LO(GATT_UUID_APPEARANCE), U16_HI(GATT_UUID_APPEARANCE)
};
static const u8 my_periConnParamCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(CONN_PARAM_DP_H), U16_HI(CONN_PARAM_DP_H),
	U16_LO(GATT_UUID_PERI_CONN_PARAM), U16_HI(GATT_UUID_PERI_CONN_PARAM)
};

//// GATT attribute values
static const u8 my_serviceChangeCharVal[5] = {
	CHAR_PROP_INDICATE,
	U16_LO(GenericAttribute_ServiceChanged_DP_H), U16_HI(GenericAttribute_ServiceChanged_DP_H),
	U16_LO(GATT_UUID_SERVICE_CHANGE), U16_HI(GATT_UUID_SERVICE_CHANGE)
};

//// Battery attribute values
static const u8 my_batCharVal[5] = {
	CHAR_PROP_READ | CHAR_PROP_NOTIFY,
	U16_LO(BATT_LEVEL_INPUT_DP_H), U16_HI(BATT_LEVEL_INPUT_DP_H),
	U16_LO(CHARACTERISTIC_UUID_BATTERY_LEVEL), U16_HI(CHARACTERISTIC_UUID_BATTERY_LEVEL)
};

//// Temp attribute values
static const u8 my_tempCharVal[5] = {
	CHAR_PROP_READ | CHAR_PROP_NOTIFY,
	U16_LO(TEMP_LEVEL_INPUT_DP_H), U16_HI(TEMP_LEVEL_INPUT_DP_H),
	U16_LO(0x2A1F), U16_HI(0x2A1F)
};

//// OTA attribute values
static const u8 my_OtaCharVal[5] = {
	CHAR_PROP_NOTIFY | CHAR_PROP_WRITE,
	U16_LO(OTA_CMD_OUT_DP_H), U16_HI(OTA_CMD_OUT_DP_H),
	U16_LO(0x331f), U16_HI(0x331f)
};

//// RxTx attribute values
static const u8 my_RxTxCharVal[5] = {
	CHAR_PROP_NOTIFY | CHAR_PROP_WRITE,
	U16_LO(RxTx_CMD_OUT_DP_H), U16_HI(RxTx_CMD_OUT_DP_H),
	U16_LO(0x1f1f), U16_HI(0x1f1f)
};

//// EPD_BLE attribute values
static const u8 my_EPD_BLECharVal[19] = {
	CHAR_PROP_READ | CHAR_PROP_WRITE,
	U16_LO(EPD_BLE_CMD_OUT_DP_H), U16_HI(EPD_BLE_CMD_OUT_DP_H),
	EPD_BLE_CHAR_UUID,
};

// TM : to modify
static const attribute_t my_Attributes[] = {
	{ATT_END_H - 1, 0,0,0,0,0},	// total num of attribute
	// 0001 - 0007  gap
	{7,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_gapServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_devNameCharVal),(u8*)(&my_characterUUID), (u8*)(my_devNameCharVal), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_devName), (u8*)(&my_devNameUUID), (u8*)(my_devName), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_appearanceCharVal),(u8*)(&my_characterUUID), (u8*)(my_appearanceCharVal), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof (my_appearance), (u8*)(&my_appearanceUIID), 	(u8*)(&my_appearance), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_periConnParamCharVal),(u8*)(&my_characterUUID), (u8*)(my_periConnParamCharVal), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof (my_periConnParameters),(u8*)(&my_periConnParamUUID), 	(u8*)(&my_periConnParameters), 0},
	// 0008 - 000b gatt
	{4,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_gattServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_serviceChangeCharVal),(u8*)(&my_characterUUID), 		(u8*)(my_serviceChangeCharVal), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof (serviceChangeVal), (u8*)(&serviceChangeUUID), 	(u8*)(&serviceChangeVal), 0},
	{0,ATT_PERMISSIONS_RDWR,2,sizeof (serviceChangeCCC),(u8*)(&clientCharacterCfgUUID), (u8*)(serviceChangeCCC), 0},
	////////////////////////////////////// Battery Service /////////////////////////////////////////////////////
	// 002a - 002d
	{4,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_batServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_batCharVal),(u8*)(&my_characterUUID), (u8*)(my_batCharVal), 0},				//prop
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_batVal),(u8*)(&my_batCharUUID), 	(u8*)(my_batVal), 0},	//value
	{0,ATT_PERMISSIONS_RDWR,2,sizeof(batteryValueInCCC),(u8*)(&clientCharacterCfgUUID), 	(u8*)(batteryValueInCCC), 0},	//value
	////////////////////////////////////// Temp Service /////////////////////////////////////////////////////
	// 002a - 002d
	{4,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_tempServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_tempCharVal),(u8*)(&my_characterUUID), (u8*)(my_tempCharVal), 0},				//prop
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_tempVal),(u8*)(&my_tempCharUUID), 	(u8*)(my_tempVal), 0},	//value
	{0,ATT_PERMISSIONS_RDWR,2,sizeof(tempValueInCCC),(u8*)(&clientCharacterCfgUUID), 	(u8*)(tempValueInCCC), 0},	//value
	////////////////////////////////////// OTA /////////////////////////////////////////////////////
	// OTA
	{4,ATT_PERMISSIONS_READ, 2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_OtaServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ, 2, sizeof(my_OtaCharVal),(u8*)(&my_characterUUID), (u8*)(my_OtaCharVal), 0},				//prop
	{0,ATT_PERMISSIONS_WRITE, 2,sizeof(my_OtaData),(u8*)(&my_OtaUUID),	(&my_OtaData), &otaWritePre},			//value
	{0,ATT_PERMISSIONS_RDWR,2,sizeof(my_OtaCCC),(u8*)(&clientCharacterCfgUUID), 	(u8*)(my_OtaCCC), 0},	//value
	////////////////////////////////////// RxTx ////////////////////////////////////////////////////
	// RxTx Communication
	{4,ATT_PERMISSIONS_READ, 2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_RxTx_ServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ, 2, sizeof(my_RxTxCharVal),(u8*)(&my_characterUUID), (u8*)(my_RxTxCharVal), 0},				//prop
	{0,ATT_PERMISSIONS_WRITE, 2,sizeof(my_RxTx_Data),(u8*)(&my_RxTxUUID),	(&my_RxTx_Data), &RxTxWrite},			//value
	{0,ATT_PERMISSIONS_RDWR,2,sizeof(RxTxValueInCCC),(u8*)(&clientCharacterCfgUUID), 	(u8*)(RxTxValueInCCC), 0},	//value
	////////////////////////////////////// EPD_BLE ////////////////////////////////////////////////////
	{3,ATT_PERMISSIONS_READ, 2, 16,(u8*)(&my_primaryServiceUUID), (u8*)(&my_EPD_BLE_ServiceUUID), 0},
	{0,ATT_PERMISSIONS_READ, 2, sizeof(my_EPD_BLECharVal), (u8*)(&my_characterUUID), (u8*)(my_EPD_BLECharVal), 0},
	{0,ATT_PERMISSIONS_WRITE, 16, sizeof(my_EPD_BLE_Data), (u8*)(&my_EPD_BLEUUID),	(&my_EPD_BLE_Data), (att_readwrite_callback_t) &epd_ble_handle_write},
};

void my_att_init(void)
{
	bls_att_setAttributeTable ((u8 *)my_Attributes);
}


