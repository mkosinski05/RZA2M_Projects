/**********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "r_typedefs.h"
#include "iodefine.h"
#include "r_cache_lld_rza2m.h"

#include "r_bcd_ae.h"
#include "r_bcd_camera.h"
#include "r_bcd_lcd.h"
#include "draw.h"
#include "perform.h"
#include "r_mmu_lld_rza2m.h"
#include "r_zxing.h"

#include "r_dk2_if.h"
#include "r_drp_simple_isp.h"
#include "r_drp_binarization_adaptive_bit.h"
#include "r_drp_reed_solomon.h"
#include "r_drp_image_rotate.h"

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
#define TILE_0          (0)
#define TILE_1          (1)
#define TILE_2          (2)
#define TILE_3          (3)
#define TILE_4          (4)
#define TILE_5          (5)

#define DRP_NOT_FINISH  (0)
#define DRP_FINISH      (1)

#define DRP_DRV_ASSERT(x) if ((x) != 0) goto sample_finish

#define ZXING_RESULT_BUF_SIZE       (256)
#define ZXING_RESULT_DISP_BUF_SIZE  (300)

#define STR_DISP_AREA_HW            (640)
#define STR_DISP_AREA_VW            (192)

/* Switching ISP function */
#define KEY_STAUS_INIT  (0xFFFFFFFFU)
#define KEY_CHECK_BIT   (0x00000003U)
#define KEY_JUST_ON     (0x00000002U)
#define ISP_AE_OFF  (0)
#define ISP_AE_ON   (1)

typedef struct {
    uint16_t    gain_red;
    uint16_t    gain_green;
    uint16_t    gain_blue;
    uint16_t    median_blend;
    int8_t      bias_red;
    int8_t      bias_green;
    int8_t      bias_blue;
    uint8_t     unsharp_strength;
    uint8_t     unsharp_coring;
} simple_setting_t;

/* Terminal window escape sequences */
static const char_t * const sp_clear_screen = "\x1b[2J";
static const char_t * const sp_cursor_home  = "\x1b[H";

/**********************************************************************************************************************
Imported global variables and functions (from other files)
**********************************************************************************************************************/
extern uint8_t g_drp_lib_isp_bayer2grayscale_6[];
extern uint8_t g_drp_lib_binarization_adaptive_bit[];
extern uint8_t g_drp_lib_reed_solomon[];
extern uint8_t g_drp_lib_image_rotate[];

/**********************************************************************************************************************
Private global variables and functions
**********************************************************************************************************************/
static r_drp_simple_isp_t param_isp __attribute__ ((section("Uncache_IRAM")));
static r_drp_binarization_adaptive_bit_t param_bin __attribute__ ((section("Uncache_IRAM")));
static r_drp_reed_solomon_t param_rs __attribute__ ((section("Uncache_IRAM")));
static uint8_t drp_work_uncache[256] __attribute__ ((section("Uncache_IRAM")));
static uint8_t drp_binarization_work_ram[((R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT)/64)+2];
static uint32_t ReedsolomonTime = 0;
static r_drp_image_rotate_t param_imr __attribute__ ((section("Uncache_IRAM")));

/* use ae */
static uint8_t  look_up_table[256] __attribute__ ((section("Uncache_IRAM")));
static uint32_t ave_result[9] __attribute__ ((section("Uncache_IRAM")));
static simple_setting_t simple_isp_set;

static uint8_t drp_lib_id[R_DK2_TILE_NUM] = {0};
static volatile uint8_t drp_lib_status[R_DK2_TILE_NUM] = {DRP_NOT_FINISH};
static r_bcd_ae_setting_t ae_setting;

/* Switching ISP function */
static uint32_t key_status;
static uint32_t isp_ae_mode;

static void cb_drp_finish(uint8_t id);

/**********************************************************************************************************************
* Function Name: cb_drp_finish
* Description  : This function is a callback function called from the
*              : DRP driver at the finish of the DRP library processing.
* Arguments    : id
*              :   The ID of the DRP library that finished processing.
* Return Value : -
**********************************************************************************************************************/
static void cb_drp_finish(uint8_t id)
{
    uint32_t tile_no;

    /* Change the operation state of the DRP library notified by the argument to finish */
    for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
    {
        if (drp_lib_id[tile_no] == id)
        {
            drp_lib_status[tile_no] = DRP_FINISH;
            break;
        }
    }

    return;
}
/**********************************************************************************************************************
* End of function cb_drp_finish
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: R_BCD_MainBinarization2
* Description  : Function to perform binarization process called from ZXing process
* Arguments    : in_adr
*              :   Address of input image
*              : out_adr
*              :   Address of Output buffer
*              : width
*              :   Horizontal size of processed image
*              : height
*              :   Vertical size of processed image
* Return Value : -
**********************************************************************************************************************/
void R_BCD_MainBinarization2(uint32_t in_adr, uint32_t out_adr, uint32_t width, uint32_t height)
{
    /***************************************/
    /* Set R_DK2_Start function parameters */
    /***************************************/
    /* Set the address of buffer to be read/write by DRP */
    param_bin.src = in_adr;
    param_bin.dst = out_adr;

    /* Set Image size(width) */
    param_bin.width = (uint16_t)width;

    /* Set Image size(hight) */
    param_bin.height = (uint16_t)height;

    /* Set additional information (currently no additional information) */
    param_bin.work = (uint32_t)&drp_binarization_work_ram[0];
    param_bin.range = 0x1C;

    /* Initialize variables to be used in termination judgment of the DRP library */
    drp_lib_status[TILE_0] = DRP_NOT_FINISH;

    /* Clean D cache */
    R_CACHE_L1DataCleanInvalidAll();

    /*****************/
    /* Start DRP lib */
    /*****************/
    (void)R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_bin, sizeof(r_drp_binarization_adaptive_bit_t));

    /***************************************/
    /* Wait until DRP processing is finish */
    /***************************************/
    while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
    {
        /* DO NOTHING */
    }
    /* Set end time of DRP processing */
    PerformSetEndTime(7);

    /* Invalidate and clean all D cache */
    R_CACHE_L1DataCleanInvalidLine((void *)out_adr, (width * height)/8);

    return;
}
/**********************************************************************************************************************
* End of function R_BCD_MainBinarization2
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: R_BCD_MainReedsolomon
* Description  : Function to perform reedsolomon process called from ZXing process
* Arguments    : codewordBytes
*              :   Address that stores the result of reedsolomon processing
*              : numCodewords
*              :   Read size
*              : numECCodewords
*              :   Correct size
* Return Value : -
**********************************************************************************************************************/
bool R_BCD_MainReedsolomon(int8_t * codewordBytes, uint8_t numCodewords, uint8_t numECCodewords)
{
    bool ret;

    /***************************************/
    /* Set R_DK2_Start function parameters */
    /***************************************/
    /* Set the source address of buffer to be read/write by DRP */
    param_rs.src = (uint32_t)codewordBytes;

    /* Set the destination address of buffer to be read/write by DRP */
    param_rs.dst = (uint32_t)&drp_work_uncache[0];
    R_MMU_VAtoPA(param_rs.dst, &param_rs.dst);

    /* Set additional information (currently no additional information) */
    param_rs.src_size = (uint16_t)numCodewords;

    /* Set check size */
    param_rs.check_size = (uint16_t)numECCodewords;

    /* Initialize variables to be used in termination judgment of the DRP library */
    drp_lib_status[TILE_3] = DRP_NOT_FINISH;

    /* Clean D cache */
    R_CACHE_L1DataCleanLine((void *)codewordBytes, (uint32_t)(numCodewords + numECCodewords));

    /*****************/
    /* Start DRP lib */
    /*****************/
    (void)R_DK2_Start(drp_lib_id[TILE_3], (void *)&param_rs, sizeof(r_drp_reed_solomon_t));

    /***************************************/
    /* Wait until DRP processing is finish */
    /***************************************/
    while (drp_lib_status[TILE_3] == DRP_NOT_FINISH)
    {
        /* DO NOTHING */
    }

    ret = (drp_work_uncache[numCodewords] == 0);
    if (ret != false)
    {
        /* copy codewords */
        memcpy((void *)codewordBytes, (void *)drp_work_uncache, numCodewords);
    }

    return ret;
}
/**********************************************************************************************************************
* End of function R_BCD_MainReedsolomon
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: R_BCD_MainSetReedsolomonTime
* Description  : Function to get processing time of Reedsolomon
* Arguments    : time
*              :   Processing time of Reedsolomon
* Return Value : -
**********************************************************************************************************************/
void R_BCD_MainSetReedsolomonTime(uint32_t time)
{
    ReedsolomonTime = time;

    return;
}
void R_BSD_ImageRotate(uint32_t in_adr, uint32_t out_adr, uint16_t width, uint16_t height) {

	//param_imr.src = in_adr;
	R_MMU_VAtoPA((uint32_t)in_adr, &(param_imr.src));
	//param_imr.dst = out_adr;
	R_MMU_VAtoPA((uint32_t)out_adr, &(param_imr.dst));
	param_imr.src_width = width;
	param_imr.src_height = height;
	param_imr.dst_stride = 0;
	param_imr.mode = 1;

	/* Initialize variables to be used in termination judgment of the DRP library */
	drp_lib_status[TILE_4] = DRP_NOT_FINISH;

	/* Clean D cache */
	R_CACHE_L1DataCleanInvalidAll();

	/*****************/
	/* Start DRP lib */
	/*****************/
	(void)R_DK2_Start(drp_lib_id[TILE_4], (void *)&param_imr, sizeof(r_drp_image_rotate_t));

	/***************************************/
	/* Wait until DRP processing is finish */
	/***************************************/
	while (drp_lib_status[TILE_4] == DRP_NOT_FINISH)
	{
		/* DO NOTHING */
	}
	/* Set end time of DRP processing */
	PerformSetEndTime(7);

	/* Invalidate and clean all D cache */
	R_CACHE_L1DataCleanInvalidLine((void *)out_adr, (uint32_t)(width * height)/8);

}
/**********************************************************************************************************************
* End of function R_BCD_MainSetReedsolomonTime
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: sample_main
* Description  : First function called after initialization is completed
* Arguments    : -
* Return Value : -
**********************************************************************************************************************/
void sample_main(void)
{
    int32_t frame_buf_id;
    uint8_t buf[ZXING_RESULT_DISP_BUF_SIZE];
    int32_t ret_val;
    uint32_t us;
    uint8_t * p_input_bufadr;
    uint8_t * p_output_bufadr;
    uint8_t zxing_result_buf[ZXING_RESULT_BUF_SIZE] = {"Not found"};
    uint8_t result_buf[ZXING_RESULT_BUF_SIZE];
    int32_t result;
    uint32_t loop;
    static int32_t fail_count = 0;

    simple_isp_set.gain_red   = 0x1000;     /* set gainR: 1.000 */
    simple_isp_set.gain_green = 0x1000;     /* set gainG: 1.000 */
    simple_isp_set.gain_blue  = 0x1000;     /* set gainB: 1.000 */
    simple_isp_set.bias_red   = 0x00;       /* set biasR: +0 */
    simple_isp_set.bias_green = 0x00;       /* set biasF: +0 */
    simple_isp_set.bias_blue  = 0x00;       /* set gainB: +0 */

    simple_isp_set.median_blend = 0x0100;   /* set median alpha blend 100% */

    simple_isp_set.unsharp_strength = 28;   /* set unsharp strength k': 28 */
    simple_isp_set.unsharp_coring   = 60;   /* set unsharp coring: 60 */

    /* VDC6 L2 Cache ON */
    PRR.AXIBUSCTL6.BIT.VDC601ARCACHE = 0xF;
    PRR.AXIBUSCTL6.BIT.VDC602ARCACHE = 0xF;
    PRR.AXIBUSCTL7.BIT.VDC604ARCACHE = 0xF;

    /* DRP L2 Cache ON */
    PRR.AXIBUSCTL4.BIT.DRPARCACHE = 0xF;
    PRR.AXIBUSCTL4.BIT.DRPAWCACHE = 0xF;

    /* Initialization of VIN and MIPI driver */
    R_BCD_CameraInit();

    /* Initialization of LCD driver */
    R_BCD_LcdInit();

    /* Use PJ1 as peripheral function */
    PORTJ.PMR.BIT.PMR1 = 1;

    /* Set PJ1 as geheral port */
    PORTJ.PMR.BIT.PMR1 = 0;

    /* Set PJ1 as input port */
    PORTJ.PDR.BIT.PDR1 = 2;

    /* Dummy read PJ1 port */
    PORTJ.PIDR.BIT.PIDR1;

    /* Key status initialize */
    key_status = KEY_STAUS_INIT;

    /* Initialize AE mode */
    isp_ae_mode = ISP_AE_ON;

    /* Capture Start */
    R_BCD_CameraClearCaptureStatus();
    R_BCD_CameraCaptureStart();

    /* Initialize of Performance counter */
    PerformInit();

    /********************************/
    /* Initialization of DRP driver */
    /********************************/
    R_DK2_Initialize();

    R_BCD_AeInit(&ae_setting);

    /* Gamma Table */
    R_BCD_AeMakeGammaTable(&ae_setting, (double)1.2, look_up_table);
    printf("%s%s", sp_clear_screen, sp_cursor_home);
    fprintf(stdout,"Renesas DRP UPC and QR Decode\n");
    fflush(stdout);
    /* main loop */
    while (1)
    {

        /* Get key */
        key_status = (key_status << 1) | PORTJ.PIDR.BIT.PIDR1;
        if ( ( key_status & KEY_CHECK_BIT) == KEY_JUST_ON )
        {
            /* Change AE mode On/Off */
            if ( isp_ae_mode == ISP_AE_OFF )
            {
                R_BCD_AeStart(&ae_setting);
                isp_ae_mode = ISP_AE_ON;
            }
            else
            {
                R_BCD_AeStop(&ae_setting);
                isp_ae_mode = ISP_AE_OFF;
            }
        }

        /******************************/
        /* Load DRP Library           */
        /*        +-----------------+ */
        /* tile 0 |IspBayer2Gray    | */
        /*        |                 | */
        /* tile 1 |                 | */
        /*        |                 | */
        /* tile 2 |                 | */
        /*        |                 | */
        /* tile 3 |                 | */
        /*        |                 | */
        /* tile 4 |                 | */
        /*        |                 | */
        /* tile 5 |                 | */
        /*        +-----------------+ */
        /******************************/
        ret_val = R_DK2_Load(&g_drp_lib_isp_bayer2grayscale_6[0],
                            R_DK2_TILE_0,

                            /* set other parameters */
                            R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);

        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
        DRP_DRV_ASSERT(ret_val);

        /* Wait until camera capture is complete */
        while ((frame_buf_id = R_BCD_CameraGetCaptureStatus()) == R_BCD_CAMERA_NOT_CAPTURED)
        {
            /* DO NOTHING */
        }

        /* Set start time of process*/
        PerformSetStartTime(1);

        p_input_bufadr  = R_BCD_CameraGetFrameAddress(frame_buf_id);
        p_output_bufadr = R_BCD_LcdGetVramAddress();

        /* convert to phisical address */
        R_MMU_VAtoPA((uint32_t)p_input_bufadr, &(param_isp.src));

        /* convert to phisical address */
        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &(param_isp.dst));

        /* Set Image size */
        param_isp.width = R_BCD_CAMERA_WIDTH;
        param_isp.height = R_BCD_CAMERA_HEIGHT;

        /* cast to uint32_t */
        R_MMU_VAtoPA((uint32_t)look_up_table, &(param_isp.table));
        param_isp.gain_r = simple_isp_set.gain_red;
        param_isp.gain_g = simple_isp_set.gain_green;
        param_isp.gain_b = simple_isp_set.gain_blue;
        param_isp.gamma  = 0x01;        /* Gamma ON */
        param_isp.component = 0x01;     /* Accumlate ON */
        param_isp.bias_r = simple_isp_set.bias_red;
        param_isp.bias_g = simple_isp_set.bias_green;
        param_isp.bias_b = simple_isp_set.bias_blue;
        param_isp.blend  = simple_isp_set.median_blend;
        param_isp.strength=simple_isp_set.unsharp_strength;
        param_isp.coring  =simple_isp_set.unsharp_coring;
        param_isp.area1_offset_x = 0;
        param_isp.area1_offset_y = 0;
        param_isp.area1_width    = R_BCD_CAMERA_WIDTH;
        param_isp.area1_height   = R_BCD_CAMERA_HEIGHT;
        param_isp.area2_offset_x = 0;
        param_isp.area2_offset_y = 0;
        param_isp.area2_width    = R_BCD_CAMERA_WIDTH;
        param_isp.area2_height   = R_BCD_CAMERA_HEIGHT;
        param_isp.area3_offset_x = 0;
        param_isp.area3_offset_y = 0;
        param_isp.area3_width    = R_BCD_CAMERA_WIDTH;
        param_isp.area3_height   = R_BCD_CAMERA_HEIGHT;
        /* cast to uint32_t */
        R_MMU_VAtoPA((uint32_t)ave_result, &(param_isp.accumulate));

        /* Initialize variables to be used in termination judgment of the DRP library */
        drp_lib_status[TILE_0] = DRP_NOT_FINISH;

        /*********************/
        /* Start DRP Library */
        /*********************/
        ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_isp, sizeof(param_isp));
        DRP_DRV_ASSERT(ret_val);

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
        {
            /* DO NOTHING */
        }

        /* Set end time of process */
        PerformSetEndTime(1);

        /****************************************************************/
        /* Auto Exposure Correction                                     */
        /* ilumi = (R * 0.299 * 4) + (G * 0.587 * 2) + (B * 0.114  * 4) */
        /****************************************************************/
        /* Cast to an appropriate type */
        R_BCD_AeRunAutoExpousure(&ae_setting, 
            (uint16_t)( ( (ave_result[0] * 0.299 * 4) + (ave_result[1] * 0.587 * 2) + (ave_result[2] * 0.114 * 4) )
            / (R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT) ) );

        /**********************/
        /* Unload DRP Library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);

        /******************************************/
        /* Load DRP Library                       */
        /*        +-----------------------------+ */
        /* tile 0 |                             | */
        /*        +                             + */
        /* tile 1 | Binarization Adaptive (bit) | */
        /*        +                             + */
        /* tile 2 |                             | */
        /*        +-----------------------------+ */
        /* tile 3 | Reed Solomon                | */
        /*        +-----------------------------+ */
        /* tile 4 | Image Rotate                | */
        /*        +-----------------------------+ */
        /* tile 5 |                             | */
        /*        +-----------------------------+ */
        /******************************************/
        ret_val = R_DK2_Load(&g_drp_lib_binarization_adaptive_bit[0],
                            R_DK2_TILE_0,
                            /* DRP parameters */
                            R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        ret_val |= R_DK2_Load(&g_drp_lib_reed_solomon[0],
                            R_DK2_TILE_3,
                            /* DRP parameters */
                            R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        ret_val |= R_DK2_Load(&g_drp_lib_image_rotate[0],
                                    R_DK2_TILE_4,
                                    /* DRP parameters */
                                    R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);

        /************************/
        /* Activate DRP library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] | drp_lib_id[TILE_4], 0);
        DRP_DRV_ASSERT(ret_val);

        /* Set start time of process*/
        PerformSetStartTime(0);

        /* ZXing process */
        result = zxing_decode_image(

        /* set parameters */
        (uint8_t *)p_output_bufadr, R_BCD_CAMERA_WIDTH, R_BCD_CAMERA_HEIGHT, (char *)result_buf, 
                                                                                            (sizeof(result_buf))-1);
#if 1
        if ( result <= 0 ) {
        	/*
        	 * Rotate the image 90 degrees and try again
        	 * This only needs to be down once because ZXing can decode verital flipped images
        	 */
        	R_BSD_ImageRotate( (uint32_t)p_output_bufadr, (uint32_t)p_input_bufadr, R_BCD_CAMERA_WIDTH, R_BCD_CAMERA_HEIGHT );

        	/* ZXing process */
        	result = zxing_decode_image(
				/* set parameters */
				(uint8_t *)p_input_bufadr, R_BCD_CAMERA_HEIGHT, R_BCD_CAMERA_WIDTH, (char *)result_buf,
				(sizeof(result_buf))-1);

			fprintf(stdout,"2");
			fflush(stdout);

        }
#endif
        /* Set end time of process */
        PerformSetEndTime(0);

        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] | drp_lib_id[TILE_4], &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /* Check whether barcode decoding succeeded */
        if (result > 0)
        {
        	fprintf(stdout,"\n"); fflush(stdout);
            result = (result > (ZXING_RESULT_BUF_SIZE - 1)) ? (ZXING_RESULT_BUF_SIZE - 1) : result;
            result_buf[result] = 0;

            /* Replace line feed code with space */
            for (loop = 0;loop < result; loop++)
            {
                if (0x20 > result_buf[loop])
                {
                    result_buf[loop] = ' ';
                }
            }
            
            /* copy results */
            strcpy((void *)&zxing_result_buf[0], (void *)&result_buf[0]);
            ReedsolomonTime = PerformGetElapsedTime_us(10);
            fail_count = 0;
        }
        else
        {
            ReedsolomonTime = 0;
            if ((fail_count++) > 50)
            {
                /* copy Not found string */
                strcpy((void *)&zxing_result_buf[0], "Not found");
            }
        }
        /* Clear the current capture state and enable the detection of the next capture completion */
        R_BCD_CameraClearCaptureStatus();

        /* Display time taken for image processing */
        R_BCD_LcdClearGraphicsBuffer();
        us = PerformGetElapsedTime_us(0);

        /* generate strings */
        sprintf((void *)&buf[0],"2D Barcode : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000)) / 100));
        R_BCD_LcdWriteString(&buf[0], 0 + 2, 0 + 2, GREEN);
        us = PerformGetElapsedTime_us(9);

        /* generate strings */
        sprintf((void *)&buf[0],"(Including Binarization %d.%d[ms] and Reedsolomon %d.%d[ms])",

                                /* mili */
                                (int)(us / 1000),

                                /* 100 us */
                                (int)((us - ((us / 1000) * 1000)) / 100),

                                /* mili */
                                (int)(ReedsolomonTime / 1000),

                                /* 100 us */
                                (int)((ReedsolomonTime - ((ReedsolomonTime / 1000) * 1000)) / 100));
        R_BCD_LcdWriteString(&buf[0], 0 + 2, 30 + 2, GREEN);

        /* characters */
        printf("%s%s", sp_clear_screen, sp_cursor_home);
        fprintf( stdout, "Decode : %s\r\n", zxing_result_buf); 
		fflush(stdout);
        sprintf((void *)&buf[0],"Decode : %s",zxing_result_buf);
        R_BCD_LcdWriteString(&buf[0], 0 + 2, 60 + 2, GREEN);

        /* Write the data(buf) on the cache to physical memory */
        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), ((STR_DISP_AREA_HW * STR_DISP_AREA_VW) / 2));

        /* Display overlay buffer written processing time */
        R_BCD_LcdSwapGraphicsBuffer();
    }

sample_finish:
    {
        ;
    }
}
/**********************************************************************************************************************
* End of function sample_main
**********************************************************************************************************************/

/* End of File */
