/** 
 * \file    dreameye.h
 * \brief   Dreameye driver extension
 * \date    2015
 * \author  SWAT www.dc-swat.ru
 */

#ifndef __DS_DREAMEYE_H
#define __DS_DREAMEYE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <dc/maple.h>
#include <dc/maple/dreameye.h>

/** \brief  Dreameye status structure.

    This structure contains information about the status of the Camera device
    and can be fetched with maple_dev_status(). You should not change any of
    this information, it should all be considered read-only.
*/
typedef struct dreameye_state_ext {
    /** \brief  The number of images on the device. */
    int             image_count;

    /** \brief  Is the image_count field valid? */
    int             image_count_valid;

    /** \brief  The number of transfer operations required for the selected
                image. */
    int             transfer_count;

    /** \brief  Is an image transferring now? */
    int             img_transferring;

    /** \brief  Storage for image data. */
    uint8          *img_buf;

    /** \brief  The size of the image in bytes. */
    int             img_size;

    /** \brief  The image number currently being transferred. */
    uint8           img_number;
	
    /** \brief  The value from/to subsystems. */
    int             value;
} dreameye_state_ext_t;


/** \brief  Read/write CMOS Image Sensor registers. */
#define DREAMEYE_COND_REG_CIS    0x00

/** \brief  Read/write Image Signal Processor registers. */
#define DREAMEYE_COND_REG_ISP    0x10

/** \brief  Read/write JangGu Compression Engine registers. */
#define DREAMEYE_COND_REG_JANGGU 0x20

/** \brief  Read/write JPEG Compression Engine registers. */
#define DREAMEYE_COND_REG_JPEG   0x21 // Supported by Dreameye???

/**
 * Really clock frequency request for each subsystem, 
 * but Dreameye response only for maple bus (use 0x90 as argument too)
 */
#define DREAMEYE_COND_MAPLE_BITRATE    0x90
#define DREAMEYE_GETCOND_RESOLUTION    0x91
#define DREAMEYE_GETCOND_COMPRESS_FMT  0x92
#define DREAMEYE_COND_FLASH_TOTAL      0x94
#define DREAMEYE_COND_FLASH_REMAIN     0x96

#define DREAMEYE_DATA_IMAGE   0x00
#define DREAMEYE_DATA_PROGRAM 0xC1

#define DREAMEYE_IMAGE_SIZE_QSIF 0x00
#define DREAMEYE_IMAGE_SIZE_QCIF 0x01
#define DREAMEYE_IMAGE_SIZE_SIF  0x02
#define DREAMEYE_IMAGE_SIZE_CIF  0x03
#define DREAMEYE_IMAGE_SIZE_VGA  0x04 // Only this supported by Dreameye???
#define DREAMEYE_IMAGE_SIZE_SVGA 0x05


/** \brief  Transfer an image from the Dreameye.

    This function fetches a single image from the specified Dreameye device.
    This function will block, and can take a little while to execute. You must
    use the first subdevice of the MAPLE_FUNC_CONTROLLER root device of the
    Dreameye as the dev parameter.

    \param  dev             The device to get an image from.
    \param  image           The image number to download.
    \param  data            A pointer to a buffer to store things in. This
                            will be allocated by the function and you are
                            responsible for freeing the data when you are done.
    \param  img_sz          A pointer to storage for the size of the image, in
                            bytes.
    \retval MAPLE_EOK       On success.
    \retval MAPLE_EFAIL     On error.
*/
int dreameye_get_video_frame(maple_device_t *dev, uint8 image, uint8 **data, int *img_sz);


/** \brief  Get params from any subsystem
 * TODO
 */
int dreameye_get_param(maple_device_t *dev, uint8 param, uint8 arg, uint16 *value);

/** \brief  Set params for any subsystem
 * TODO
 */
int dreameye_set_param(maple_device_t *dev, uint8 param, uint8 arg, uint16 value);

__END_DECLS

#endif  /* __DS_DREAMEYE_H */
