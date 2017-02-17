
/*
 * Description: An example showing how to use libv4l2 API.
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 13:44:30 2017
 * Project: libv4l2
 *
 * Copyright (c) 2017 All rights reserved
 */

#include <libv4l2.h>
#include <collections.h>

int main(void)
{
    v4l2_t *v4l2 = NULL;
    v4l2_image_t *img;
    int i;

    collections_init(NULL);
    v4l2 = v4l2_open("/dev/video0", 640, 480, V4L2_IMAGE_FMT_YUYV,
                     V4L2_MODEL_USB_WEBCAM, V4L2_CHANNEL_COMPOSITE);

    if (NULL == v4l2)
        printf("%s\n", v4l2_strerror(v4l2_get_last_error()));

    if (v4l2 != NULL) {
        printf("%s, %s, %s, %s\n", v4l2_device_name(v4l2),
                v4l2_card_name(v4l2), v4l2_driver_name(v4l2),
                v4l2_bus_info(v4l2));

        for (i = 0; i < 10; i++) {
            img = v4l2_grab_image(v4l2, true);
            printf("Grab %d: %dx%d, %d bytes\n", i + 1, v4l2_image_width(img),
                    v4l2_image_height(img), v4l2_image_size(img));

            v4l2_image_unref(img);
            printf("Release\n");
        }

        v4l2_close(v4l2);
    }

    collections_uninit();
    cexit();

    return 0;
}

