/********************************************************************************************************
 * @file     usbmouse_i.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     Sep. 30, 2010
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/

#pragma once

#include <application/app/usbmouse.h>

#include "../usbstd/usb.h"
#include "../usbstd/usbhw.h"
#include "../usbstd/usbhw_i.h"
#include "../../vendor/common/default_config.h"
/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
/* debug note: */
/*
 0x85, 0x01, //Report ID (1) keyboard
 0x85, 0x02, //report ID 02 mouse
 �Ƿ���Ҫ������� , 1,2�����Ƿ���ȷ
 */
static const USB_Descriptor_HIDReport_Datatype_t mouse_report_desc[] = {
#if 0
	//ÿ�п�ʼ�ĵ�һ�ֽ�Ϊ����Ŀ��ǰ׺��ǰ׺�ĸ�ʽΪ��
	//D7~D4��bTag��D3~D2��bType��D1~D0��bSize�����·ֱ��ÿ����Ŀע�͡�

	//����һ��ȫ�֣�bTypeΪ1����Ŀ��ѡ����;ҳΪ��ͨ����Generic Desktop Page(0x01)
	//�����һ�ֽ����ݣ�bSizeΪ1����������ֽ����Ͳ�ע���ˣ�
	//�Լ�����bSize���жϡ�
	HID_RPT_USAGE_PAGE(8, 0x01), /* Generic Desktop */

	//����һ���ֲ���bTypeΪ2����Ŀ��˵����������Ӧ�ü�����;�������
    HID_RPT_USAGE(8, 0x02)		, /* Mouse */

	//����һ������Ŀ��bTypeΪ0����Ŀ�������ϣ������������0x01��ʾ
	//�ü�����һ��Ӧ�ü��ϡ�����������ǰ������;ҳ����;����Ϊ
	//��ͨ�����õ���ꡣ
    HID_RPT_COLLECTION(8, 0x01)		, /* Application */

    HID_RPT_REPORT_ID(8, USB_HID_MOUSE)		, /*Report ID*/

    HID_RPT_USAGE_PAGE(8, 0x09)		, /* Button */

	//����һ���ֲ���Ŀ��˵����;����СֵΪ1��ʵ��������������
	// 1 is mouse left button,2 is mouse right button,3 is central buuton
    HID_RPT_USAGE_MINIMUM(8, 0x01)		,
	//����һ���ֲ���Ŀ��˵����;�����ֵ
    HID_RPT_USAGE_MAXIMUM(8, 0x05),

	//����һ��ȫ����Ŀ��˵�����ص����ݵ��߼�ֵ���������Ƿ��ص��������ֵ����
	//��СΪ0����Ϊ����������Bit����ʾһ�������������СΪ0�����Ϊ1��
    HID_RPT_LOGICAL_MINIMUM(8, 0x00)		,
	//����һ��ȫ����Ŀ��˵���߼�ֵ���Ϊ1��
    HID_RPT_LOGICAL_MAXIMUM(8, 0x01),

	//����һ��ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ1��bit��
	HID_RPT_REPORT_SIZE(8, 0x01),
	//����һ��ȫ����Ŀ��˵��total button ����Ϊ5����
    HID_RPT_REPORT_COUNT(8, 0x05), /* debug note: 3->5*/

	//����һ������Ŀ��˵����3������Ϊ1bit�������������ͳ���
	//��ǰ�������ȫ����Ŀ�����壩������Ϊ���룬
	//����Ϊ��Data,Var,Abs��Data��ʾ��Щ���ݿ��Ա䶯��Var��ʾ
	//��Щ�������Ƕ����ģ�ÿ�����ʾһ����˼��Abs��ʾ����ֵ��
	//��������Ľ�����ǣ���һ��������bit0��ʾ����1��������Ƿ��£�
	//�ڶ���������bit1��ʾ����2���Ҽ����Ƿ��£�������������bit2��ʾ
	//����3���м����Ƿ��¡�
    HID_RPT_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	//����һ��ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ
	HID_RPT_REPORT_SIZE(8, 0x03), /* debug note: 5->3*/
	//����һ��ȫ����Ŀ��˵������������Ϊ1��
    HID_RPT_REPORT_COUNT(8, 0x01),

	//����һ������Ŀ�������ã���ǰ������ȫ����Ŀ��֪������Ϊ3bit��
	//����Ϊ1������������Ϊ�����������ص�����һֱ��0����
	//���ֻ��Ϊ�˴���һ���ֽڣ�ǰ������3��bit��������һЩ����
	//���ѣ���������û��ʵ����;�ġ�
    HID_RPT_INPUT(8, HID_IOF_CONSTANT),

	//����һ���ֲ���Ŀ��˵����;Ϊָ�뼯��
    HID_RPT_USAGE(8, 0x01), /* Pointer */

	//����һ������Ŀ�������ϣ������������0x00��ʾ�ü�����һ��
	//�����ϣ���;��ǰ��ľֲ���Ŀ����Ϊָ�뼯�ϡ�
    HID_RPT_COLLECTION(8, 0x00), /* Physical */

	//����һ��ȫ����Ŀ��ѡ����;ҳΪ��ͨ����Generic Desktop Page(0x01)
    HID_RPT_USAGE_PAGE(8, 0x01),  /* Generic Desktop */

	//����һ���ֲ���Ŀ��˵����;ΪX��
    HID_RPT_USAGE(8, 0x30), /* Usage X */

	//����һ���ֲ���Ŀ��˵����;ΪY��
    HID_RPT_USAGE(8, 0x31), /* Usage Y */

	//��������Ϊȫ����Ŀ��˵�����ص��߼���С�����ֵ��
	//��Ϊ���ָ���ƶ�ʱ��ͨ���������ֵ����ʾ�ģ�
	//���ֵ����˼���ǣ���ָ���ƶ�ʱ��ֻ�����ƶ�����
	//�����ƶ�ʱ��XֵΪ���������ƶ�ʱ��YֵΪ����
	//���ڹ��֣����������Ϲ�ʱ��ֵΪ����
    HID_RPT_LOGICAL_MINIMUM(8, 0x81), //     LOGICAL_MINIMUM (-127)
    HID_RPT_LOGICAL_MAXIMUM(8, 0x7f), //     LOGICAL_MAXIMUM (127)
	//����һ��ȫ����Ŀ��˵��������ĳ��ȡ����ʹ�� 16���Ϳ��Ա�ʾ��������
    HID_RPT_REPORT_SIZE(8, 0x08),
    HID_RPT_REPORT_COUNT(8, 0x02),
	//����һ������Ŀ����˵��������8bit���������������õģ�
	//����Ϊ��Data,Var,Rel��Data˵�������ǿ��Ա�ģ�Var˵��
	//��Щ�������Ƕ����ģ�����һ��8bit��ʾX�ᣬ�ڶ���8bit��ʾ
	//Y�ᣬ������8bit��ʾ���֡�Rel��ʾ��Щֵ�����ֵ��
    HID_RPT_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

    HID_RPT_USAGE(8, 0x38),  /* Usage Wheel */
    HID_RPT_LOGICAL_MINIMUM(8, 0x81),	 //LOGICAL_MINIMUM (-127)
    HID_RPT_LOGICAL_MAXIMUM(8, 0x7f),	 //LOGICAL_MAXIMUM (127)
    HID_RPT_REPORT_SIZE(8, 0x08),		 //REPORT_SIZE (8)
    HID_RPT_REPORT_COUNT(8, 0x01),		//REPORT_COUNT (1)
    HID_RPT_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

    HID_RPT_END_COLLECTION(0),
    HID_RPT_END_COLLECTION(0),
        
    HID_RPT_USAGE_PAGE(8, 0x0c),             //global, usage page (follow 1 bytes) consumer page
    HID_RPT_USAGE(8, 0x01),                  //local,  usage ID 01  Consumer Control
    HID_RPT_COLLECTION(8, 0x01),             //main, collection
    HID_RPT_REPORT_ID(8, USB_HID_KB_MEDIA),  //Report ID
    HID_RPT_REPORT_SIZE(8, 0x10),            //global, report size 16 bits
    HID_RPT_REPORT_COUNT(8, 0x02),           //global, report count 2
    HID_RPT_LOGICAL_MINIMUM(8, 0x01),        //global, min  0x01
    HID_RPT_LOGICAL_MAXIMUM(16, 0x02ff),     //global, max  0x028c
    HID_RPT_USAGE_MINIMUM(8, 0x01),          //local, min   0x01
    HID_RPT_USAGE_MAXIMUM(16, 0x02ff),       //local, max    0x28c
    HID_RPT_INPUT(8, HID_IOF_ABSOLUTE),      //main,  input data varible, absolute
    HID_RPT_END_COLLECTION(0),               //main, end collection

	HID_RPT_USAGE_PAGE(8, 0x01),             //gobal,  USAGE_PAGE 1 (Generic Desktop)
	HID_RPT_USAGE(8, 0x80),                  //local, usage ID 0x80 system control
	HID_RPT_COLLECTION(8, 0x01),             //main conllection
    HID_RPT_REPORT_ID(8, USB_HID_KB_SYS),    //Report ID
	HID_RPT_REPORT_SIZE(8, 0x01),            //global, report size 2
	HID_RPT_REPORT_COUNT(8, 0x03),           //report count  1
	HID_RPT_LOGICAL_MINIMUM(8, 0x00),        //global min 01
    HID_RPT_LOGICAL_MAXIMUM(8, 0x01),        //gobal, max 3
	HID_RPT_USAGE(8, 0x81),					//local usage ID 0x81 system power down
    HID_RPT_USAGE(8, 0x82),                  //local usage ID 0x82 system sleep
    HID_RPT_USAGE(8, 0x83),                  //local usage ID 0x83 system wakeup
    HID_RPT_INPUT(8, HID_IOF_ABSOLUTE|HID_IOF_NO_PREFERRED_STATE|HID_IOF_NULLSTATE),
    HID_RPT_REPORT_SIZE(8, 0x05),            //global report size 6
	HID_RPT_REPORT_COUNT(8, 0x01),			//report count	1
    HID_RPT_INPUT(8, HID_IOF_CONSTANT|HID_IOF_VARIABLE),
    HID_RPT_END_COLLECTION(0),               //end of collection

#else

	//����һ��ȫ�֣�bTypeΪ1����Ŀ��ѡ����;ҳΪ��ͨ����Generic Desktop Page(0x01)
	//�����һ�ֽ����ݣ�bSizeΪ1����������ֽ����Ͳ�ע���ˣ�
	//�Լ�����bSize���жϡ�
	0x05, 0x01, // USAGE_PAGE (Generic Desktop)

	//����һ���ֲ���bTypeΪ2����Ŀ��˵����������Ӧ�ü�����;�������
	0x09, 0x02, // USAGE (Mouse)

	//����һ������Ŀ��bTypeΪ0����Ŀ�������ϣ������������0x01��ʾ
	//�ü�����һ��Ӧ�ü��ϡ�����������ǰ������;ҳ����;����Ϊ
	//��ͨ�����õ���ꡣ
	0xa1, 0x01, // COLLECTION (Application)

	0x85, USB_HID_MOUSE, //report ID 01

	//����һ���ֲ���Ŀ��˵����;Ϊָ�뼯��
	0x09, 0x01, //   USAGE (Pointer)

	//����һ������Ŀ�������ϣ������������0x00��ʾ�ü�����һ��
	//�����ϣ���;��ǰ��ľֲ���Ŀ����Ϊָ�뼯�ϡ�
	0xa1, 0x00, //   COLLECTION (Physical)


	//����һ��ȫ����Ŀ��ѡ����;ҳΪ������Button Page(0x09)��
	0x05, 0x09, //     USAGE_PAGE (Button)

	//����һ���ֲ���Ŀ��˵����;����СֵΪ1��ʵ��������������
	// 1 is mouse left button,2 is mouse right button,3 is central buuton
	0x19, 0x01, //     USAGE_MINIMUM (Button 1)

	//����һ���ֲ���Ŀ��˵����;�����ֵΪ3��ʵ����������м���
	0x29, 0x05, //     USAGE_MAXIMUM (Button 5)

	//����һ��ȫ����Ŀ��˵�����ص����ݵ��߼�ֵ���������Ƿ��ص��������ֵ����
	//��СΪ0����Ϊ����������Bit����ʾһ�������������СΪ0�����Ϊ1��
	0x15, 0x00, //     LOGICAL_MINIMUM (0)

	//����һ��ȫ����Ŀ��˵���߼�ֵ���Ϊ1��
	0x25, 0x01, //     LOGICAL_MAXIMUM (1)

	//����һ��ȫ����Ŀ��˵��total button ����Ϊ5����
	0x95, 0x05, //     REPORT_COUNT (3)
	//����һ��ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ1��bit��
	0x75, 0x01, //     REPORT_SIZE (1)

	//����һ������Ŀ��˵����5������Ϊ1bit�������������ͳ���
	//��ǰ�������ȫ����Ŀ�����壩������Ϊ���룬
	//����Ϊ��Data,Var,Abs��Data��ʾ��Щ���ݿ��Ա䶯��Var��ʾ
	//��Щ�������Ƕ����ģ�ÿ�����ʾһ����˼��Abs��ʾ����ֵ��
	//��������Ľ�����ǣ���һ��������bit0��ʾ����1��������Ƿ��£�
	//�ڶ���������bit1��ʾ����2���Ҽ����Ƿ��£�������������bit2��ʾ
	//����3���м����Ƿ��¡�
	0x81, 0x02, //     INPUT (Data,Var,Abs)

	//����һ��ȫ����Ŀ��˵������������Ϊ1��
	0x95, 0x01, //     REPORT_COUNT (1)
	//����һ��ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ3bit��
	0x75, 0x03, //     REPORT_SIZE (3)


	//����һ������Ŀ�������ã���ǰ������ȫ����Ŀ��֪������Ϊ3bit��
	//����Ϊ1������������Ϊ�����������ص�����һֱ��0����
	//���ֻ��Ϊ�˴���һ���ֽڣ�ǰ������3��bit��������һЩ����
	//���ѣ���������û��ʵ����;�ġ�
	0x81, 0x01, //     INPUT (Cnst,Var,Abs)


	//����һ��ȫ����Ŀ��ѡ����;ҳΪ��ͨ����Generic Desktop Page(0x01)
	0x05, 0x01, //     USAGE_PAGE (Generic Desktop)

	//����һ���ֲ���Ŀ��˵����;ΪX��
	0x09, 0x30, //     USAGE (X)

	//����һ���ֲ���Ŀ��˵����;ΪY��
	0x09, 0x31, //     USAGE (Y)
	//��������Ϊȫ����Ŀ��˵�����ص��߼���С�����ֵ��
	//��Ϊ���ָ���ƶ�ʱ��ͨ���������ֵ����ʾ�ģ�
	//���ֵ����˼���ǣ���ָ���ƶ�ʱ��ֻ�����ƶ�����
	//�����ƶ�ʱ��XֵΪ���������ƶ�ʱ��YֵΪ����
	//���ڹ��֣����������Ϲ�ʱ��ֵΪ����
	0x15, 0x81, //     LOGICAL_MINIMUM (-127)
	0x25, 0x7f, //     LOGICAL_MAXIMUM (127)

	//����һ��ȫ����Ŀ��˵��������ĳ���Ϊ8bit��
	0x75, 0x08, //     REPORT_SIZE (16)

	//����һ��ȫ����Ŀ��˵��������ĸ���Ϊ2����
	0x95, 0x02, //     REPORT_COUNT (2)

	//����һ������Ŀ����˵��������8bit���������������õģ�
	//����Ϊ��Data,Var,Rel��Data˵�������ǿ��Ա�ģ�Var˵��
	//��Щ�������Ƕ����ģ�����һ��8bit��ʾX�ᣬ�ڶ���8bit��ʾ
	//Y�ᣬ������8bit��ʾ���֡�Rel��ʾ��Щֵ�����ֵ��
	0x81, 0x06, //     INPUT (Data,Var,Rel)

	//����һ���ֲ���Ŀ��˵����;Ϊ����
	0x09, 0x38, //     USAGE (Wheel)
	0x15, 0x81, //LOGICAL_MINIMUM (-127)
	0x25, 0x7f, //LOGICAL_MAXIMUM (127)
	0x75, 0x08, //REPORT_SIZE (16)
	0x95, 0x01, //REPORT_COUNT (1)
	0x81, 0x06, //INPUT (Data,Var,Rel)


	//��������������Ŀ�����ر�ǰ��ļ����á�
	//���ǿ����������ϣ�����Ҫ�����Ρ�bSizeΪ0�����Ժ���û���ݡ�
	0xc0, //   END_COLLECTION
	0xc0, // END_COLLECTION

#if (ONEKEY_WEB==0)
	// begin of media key
	0x05,0x0c,     //global, usage page (follow 1 bytes) consumer page
	0x09,0x01,     //local,  usage ID 01  Consumer Control
	0xA1,0x01,     //main, collection
	0x85,USB_HID_KB_MEDIA,     //global, report ID 0x03
	0x75,0x10,     //global, report size 16 bits
	0x95,0x02,     //global, report count 2
	0x15,0x01,     //global, min  0x01
	0x26,0x9c,0x02,  //global, max  0x29c
#if CHIP_EOP_ERROR
	0x19,0x01,     //local, min   0x01
	0x2a,0xff,0x02,  //local, max    0x2ff
#else
	0x19,0x01,     //local, min   0x01
	0x2a,0x8c,0x02,  //local, max    0x28c
#endif
	0x81,0x00,     //main,  input data varible, absolute
	0xc0,        //main, end collection

	0x05,0x01,     //gobal,  USAGE_PAGE 1 (Generic Desktop)
	0x09,0x80,     //local, usage ID 0x80 system control
	0xa1,0x01,     //main conllection
	0x85,USB_HID_KB_SYS,     //global report ID 0x4
	0x75,0x02,     //global, report size 2
	0x95,0x01,     //report count  1
	0x15,0x01,     //global min 01
	0x25,0x03,     //gobal, max 3
	0x09,0x82,     //local usage ID 0x82 system sleep
	0x09,0x81,     //local usage ID 0x81 system power down
	0x09,0x83,     //local usage ID 0x83 system wakeup
	0x81,0x60,     //main, input data, var, abs, No Prefer, NULL state
	0x75,0x06,     //global report size 6
	0x81,0x03,     //main input, constant, array
	0xc0,        //end of collection
	// end of media key
#endif
#endif
    //need Jensen's help: report ID 5
    HID_RPT_USAGE_PAGE(8, 0x01),     //global,  USAGE_PAGE 1 (Generic Desktop)
	0x09,0x00,     //usage undefined
	0xa1,0x01,     //main collection
	0x85,0x05,     //global report ID 0x5
	0x06,0x00,0xff,  //global usage page
	0x09,0x01,     //local,  usage ID 01  Consumer Control
	0x15,0x81,     //global min 81
	0x25,0x7f,     //global, max 7f
	0x75,0x08,     //global, report size 8
	0x95,0x07,     //report count  7
	0xb1,0x02,     //feature (data, var, abs)
	HID_RPT_END_COLLECTION(0),         //main, end collection
};

static inline u8* usbmouse_get_report_desc(void) {
	return (u8*) (mouse_report_desc);
}

static inline u16 usbmouse_get_report_desc_size(void) {
	return sizeof(mouse_report_desc);
}

