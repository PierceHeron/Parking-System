/*************************************************************************
 * @Filename              :  JPG.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-16 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-20 Mon
 ************************************************************************/



/*
* @Author: haidee
* @Date:   2018-02-06 09:53:44
* @Last Modified by:   haidee
* @Last Modified time: 2018-02-08 10:21:56
*/
#include "JPG.h"


/**
 * [Is_JPG description:Determind the file whether is jpg file]
 * @param  PicName [The file name]
 * @return   true  [it is]
 *                 false [it is not]
 */
bool Is_JPG(char *PicName)
{
        while ((*PicName) != '.')
                PicName += 1;

        if (strncmp(PicName, ".jpg", 4) == 0)
                return true;
        else
                return false;
}
/**
 * [open_image description:Open the file]
 * @param fd             []
 * @param PitName  [The file's name]
 * @param mode       []
 * @param JPG_info   [The pointer to the file stat struture]
 */
void Open_Image( int *fd , char *PitName, int mode, struct stat *JPG_info)
{
        stat(PitName, JPG_info);
        *fd = open(PitName, mode);
}

/**
 * [read_image description : read data from the image]
 * @param fd       [description]
 * @param jpg_size [the picture's size]
 * @param jpg_buf  [description]
 */
void Read_Image(int fd , size_t jpg_size, void *jpg_buf)
{
        unsigned char n = 1;

        while (n > 0)
        {
                n = read(fd , jpg_buf, jpg_size);
                if (n == -1)
                {
                        perror("read failed");
                        exit(0);
                }
                else if (n == 0)
                        break;

                jpg_size -= n;
                jpg_buf += n;
        }

        close(fd);
}

/**
 * [JPG_to_BMP description]
 * @param  image    [description]
 * @param  jpg_data [description]
 * @param  JPG_info [description]
 * @return          [description]
 */
int JPG_to_BMP(struct RGB *image, unsigned char *jpg_data, int size)
{
        // [假设]：
        // jpg_data中已经存放了某张JPG图片的原始数据
        // jpg_info中已经存放了这张JPG图片的stat信息
        // [固定步骤]声明JPG信息结构体，以及错误管理结构体
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        // [固定步骤]使用缺省的出错处理来初始化cinfo
        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);

        // [固定步骤]配置该cinfo，使其从jpg_data中读取st_size个字节
        jpeg_mem_src(&cinfo, jpg_data, size);

        // [固定步骤]读取JPG数据的头，并判断其格式是否合法
        if (jpeg_read_header(&cinfo, true) != 1)
        {
                perror("这不是JPG图片");
                return -1;
        }
        // [固定步骤]开始解码
        jpeg_start_decompress(&cinfo);

        /* [注意]
        * 此时，cinfo中存放了图片的尺寸信息：
        * 宽：cinfo.output_width
        * 高：cinfo.output_height
        * 深：cinfo.output_components（单位是字节）
        *
        * 它们可能是你要用到的信息
        */
        image->width = cinfo.output_width;
        image->height = cinfo.output_height;
        image->bpp = cinfo.output_components;
        // 根据图片的尺寸大小，分配一块相应的内存rgb_data
        // 用来存放从jpg_data解码出来的RGB数据
        unsigned long rgb_size = cinfo.output_width * cinfo.output_height * cinfo.output_components;
        image->rgb_data = malloc(rgb_size);

        // [固定步骤]循环地将图片的每一行读出并解码到rgb_data中
        int row_stride = cinfo.output_width * cinfo.output_components;
        while (cinfo.output_scanline < cinfo.output_height)
        {
                unsigned char *tmp[1];
                tmp[0] = image->rgb_data + (cinfo.output_scanline) * row_stride;
                jpeg_read_scanlines(&cinfo, tmp, 1);
        }

        /* [注意]
        *
        *  此时，rgb_data中已经存放了解码了的图像数据
        * 它可能是你要用到的信息
        */

        // 解码完毕，释放相关资源
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);

        return 0;
}

/**
 * [BMP_to_LCD description]
 * @param  image [description]
 * @return       [description]
 */
int * BMP_to_LCD(struct RGB image)
{

        int *lcd_buf;
        int *lcd_buff;
        int CurX = 0, CurY = 0;             //对首地址进行适当偏移方便图片在指定地方显示
        int i = 0, j = 0;

        float multiple = 0;     //大图的缩小倍数

        lcd_buf = (int *)calloc(1, 800 * 480 * 4);

        /*判断是否是大图*/
        if (image.height > 480 || image.width > 800)
                multiple = (800.0 / image.width) > (480.0 / image.height) ? (480.0 / image.height) : (800.0 / image.width);
        else
                multiple = 1;

        for (j = 0; j < 480 ; j ++)
        {
                CurY = (int)((j - (240 - (int)(image.height * multiple * 0.5))) / multiple);
                for (i = 0; i < 800; i++)
                {
                        CurX = (int)((i - (400 - (int)(image.width * multiple * 0.5))) / multiple);
                        if (i > 400 - (int)(image.width * multiple * 0.5) && i < 400 + (int)(image.width * multiple * 0.5))
                                if ((j > 240 - (int)(image.height * multiple * 0.5)) && (j < 240 + (int)(image.height * multiple * 0.5)) )
                                {
                                        *(lcd_buf + i + j * 800) = ((*(image.rgb_data + (CurX + CurY * image.width) * 3 + 0)) << 16)
                                                                   + ((*(image.rgb_data + (CurX + CurY * image.width) * 3 + 1)) << 8  )
                                                                   + ((*(image.rgb_data + (CurX + CurY * image.width) * 3 + 2)) << 0  );
                                        continue;
                                }

                        *(lcd_buf + i + j * 800) = 0x00F0F0F0;
                }
        }
	free(image.rgb_data);

        return lcd_buf;
}


int * BMP_to_LCD_Low(struct RGB image)
{
	int * lcd_buf = (int *)calloc(1, image.width * image.height * 4);

	int i,j;
	for(i = 0; i < image.height; i++)
	{
		for(j = 0; j < image.width; j++)
		{
			*(lcd_buf+i*image.width+j) =((image.rgb_data[(i*image.width + j) * 3 + 2])     |
						(image.rgb_data[(i*image.width + j) * 3 + 1] << 8) |
						(image.rgb_data[(i*image.width + j) * 3] << 16)) ;
		}
	}
	free(image.rgb_data);

	return lcd_buf;

}

/**
 * [Get_Buf description: Get data from image and dispose it]
 * @param  filename [The picture's name]
 * @return   buf         [The pointer to the data had read]
 */
int *Get_Buf(char *filename)
{
        struct RGB image;                       //Record image  rgb data and stat
        unsigned char *jpg_data;            //Record image jpg data
        struct stat  JPG_info;                   //Record image stat
        int fd;                                          //Record image

        /*Open image , record images stat*/
        Open_Image(&fd, filename, O_RDONLY, &JPG_info);
        jpg_data = (unsigned char *)calloc(1, JPG_info.st_size);

        /*Get the jpg data form the file*/
        Read_Image(fd,  JPG_info.st_size, jpg_data);
        /*Change jpg data to rgb data*/
        if (JPG_to_BMP(&image, jpg_data, JPG_info.st_size) == -1)
                return NULL;
        /*Change rgb data size*/
        return BMP_to_LCD(image);
}

/**
 * [Display_JPG description:Display a Picture]
 * @param  filename [The picture's name]
 */
void Display_JPG(char * filename)
{
	int * buf;

	buf = Get_Buf(filename);

        Display(buf);
}
