
/*
 * Description: An example showing how to use libv4l2 API.
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 13:44:30 2017
 * Project: libv4l2
 *
 * Copyright (c) 2017 All rights reserved
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libv4l2.h>
#include <collections.h>

static void usage(void)
{
    printf("Usage: v4l2 [OPTIONS]\n");
    printf("An example showing how to use libv4l2's API.\n");
    printf("\nOptions:\n");
    printf("-h\t\tShows this help screen.\n");
    printf("-d [device]\tIndicates the video device to be manipulated.\n");
    printf("-g [frames]\tDefines the number of captures that will be made.\n");
    printf("\n");
}

int main(int argc, char **argv)
{
    const char *opt = "d:g:h\0";
    v4l2_t *v4l2 = NULL;
    v4l2_image_t *img;
    int i, option, grabs = -1;
    char *device = NULL, *filename = NULL;

    do {
        option = getopt(argc, argv, opt);

        switch (option) {
            case 'd':
                device = strdup(optarg);
                break;

            case 'h':
                usage();
                return 1;

            case 'g':
                grabs = atoi(optarg);
                break;

            case '?':
                return -1;
        }
    } while (option != -1);

    if (NULL == device) {
        printf("Needs to pass the device name\n");
        return -1;
    }

    collections_init(NULL);
    v4l2 = v4l2_open(device, 640, 480, V4L2_IMAGE_FMT_YUYV,
                     V4L2_MODEL_USB_WEBCAM, V4L2_CHANNEL_COMPOSITE);

    if (NULL == v4l2)
        printf("%s\n", v4l2_strerror(v4l2_get_last_error()));

    if (v4l2 != NULL) {
        printf("%s, %s, %s, %s\n", v4l2_device_name(v4l2),
                v4l2_card_name(v4l2), v4l2_driver_name(v4l2),
                v4l2_bus_info(v4l2));

        /* Sets the device settings */
        v4l2_set_setting(v4l2, V4L2_SETTING_BRIGHTNESS, 135);
        v4l2_set_setting(v4l2, V4L2_SETTING_CONTRAST, 33);

        v4l2_set_setting(v4l2, V4L2_SETTING_HUE, 0);
        v4l2_set_setting(v4l2, V4L2_SETTING_SATURATION, 40);

        for (i = 0; i < grabs; i++) {
            img = v4l2_grab_image(v4l2, false);
            printf("Grab %d: %dx%d, %d bytes\n", i + 1, v4l2_image_width(img),
                    v4l2_image_height(img), v4l2_image_size(img));

            asprintf(&filename, "test_%02d.raw", i + 1);
            cfsave(filename, v4l2_image_data(img), v4l2_image_size(img));
            v4l2_image_unref(img);
            free(filename);
        }

        v4l2_close(v4l2);
    }

    if (device != NULL)
        free(device);

    collections_uninit();
    cexit();

    return 0;
}

