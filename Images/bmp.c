#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "bmp.h"
BMPHeader* read_head(FILE* fp)
{
	BMPHeader* header = malloc(sizeof(*header));
	fread(header,sizeof(*header),1,fp);
	return header;
}
char* _check_err(const char* error)
{
	char* err = malloc(sizeof(*err)*(strlen(error) + 1));
	strcpy(err, error);
	return err;
}

bool _check(bool condition, bool* a_ok, char** a_error, const char* msg_if_fails) {
	if(*a_ok && !condition) {
		*a_ok = false; 
		*a_error = _check_err(msg_if_fails);
	}
	return *a_ok;
}

BMPImage* read_bmp(FILE* fp, char** error)
{
	bool ok = true;
	BMPImage* image = NULL;
	BMPHeader* header = malloc(sizeof(*header));
	if (_check(header !=NULL , &ok, error, "malloc header fail in read_bmp")){
		if (_check(fread(header,sizeof(*header),1,fp) == 1, &ok, error,"fread fail in read_bmp")){
			if (_check(check_bmp_header(header,fp)== 1,&ok,error,"header checked fails in read_bmp")){;
				image = malloc(sizeof(*image));
				image -> header = *header;
				image -> data = malloc(header -> image_size_bytes);
				if (_check(image != NULL, &ok,error,"malloc data fail in read_bmp")){
					fread(image -> data,header -> image_size_bytes,1,fp);
				}
			}
		}
	}
	free(header);
	if(ok)
	{
		return image;
	}
	else{
		return NULL;
	}
}

void free_bmp(BMPImage* bmp)
{
	free(bmp -> data);
	free(bmp);
}

bool write_bmp(FILE* fp, BMPImage* image, char** error)
{
	fwrite(&image -> header,sizeof(image->header),1,fp);
	fwrite(image->data, image->header.image_size_bytes,1,fp);
	return true;
}

BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error)
{
    int i = 0;
	int n_h = 0;
	int n_w = 0;
	int byte_per = image->header.bits_per_pixel / 8;
	BMPImage* copy = malloc(sizeof(*copy));
	int byte_per_r = byte_per * image->header.width_px + image->header.width_px % 4;
	int cnt = 0;
	copy->data = malloc((w*byte_per+w%4)*h);
	for ( n_h = h-1; n_h >= 0; n_h --)
	{
		for( n_w = 0; n_w < w; n_w ++)
		{
			int index_r = y + n_h;
			int index_c = x + n_w;
			int index =(image->header.height_px - index_r - 1)* byte_per_r + index_c * byte_per;
			copy->data[cnt++] = image->data[index];
			copy->data[cnt++] = image->data[index + 1];
			copy->data[cnt++] = image->data[index + 2];
		}
		for ( i = 0; i < w % 4; i++)
		{
			copy->data[cnt++] = 0x00;
		}
	}
	copy->header = image->header;
	copy->header.image_size_bytes = (w*byte_per + w%4) * h;
	copy->header.size =(copy->header.image_size_bytes + BMP_HEADER_SIZE);
	copy->header.width_px = w;
	copy->header.height_px = h;

	return copy;	

}

bool check_bmp_header(BMPHeader* hdr,FILE* fp)
{
	
	if ((hdr->width_px *  hdr->bits_per_pixel / 8 + hdr->width_px % 4) * hdr->height_px != hdr->image_size_bytes)
	{
		return 0;
	}
	if (hdr->image_size_bytes + 54 != hdr->size)
	{
		return 0;
	}

	if (hdr->type !=0x4d42)
	{
		return 0;
	}
	if (hdr->offset != 54)
	{
		return 0;
	}
	if (hdr->num_planes != 1)
	{
		return 0;
	}
	if (hdr->compression !=0)
	{
		return 0;
	}
	if ((hdr->num_colors != 0) || (hdr->important_colors != 0))
	{
		return 0;
	}
	if (hdr->bits_per_pixel != 24)
	{
		return 0;
	}
	if (hdr->dib_header_size != 40)
	{
		return 0;
	}
	fseek(fp,0L,SEEK_SET);
	BMPHeader* read_h = read_head(fp);
	if (read_h == NULL || fp == NULL)
	{
		return 0;
	}
	if (read_h->type != hdr->type)
	{
		return 0;
	}
	if (read_h->size != hdr->size)
	{
		return 0;
	}
	if (read_h->reserved1 != hdr->reserved1)
	{
		return 0;
	}
	if (read_h->reserved2 != hdr->reserved2)
	{
		return 0;
	}
	if (read_h->offset != hdr->offset)
	{
		return 0;
	}
	if (read_h->dib_header_size != hdr->dib_header_size)
	{
		return 0;
	}
	if (read_h->width_px != hdr->width_px)
	{
		return 0;
	}
	if (read_h->height_px != hdr->height_px)
	{
		return 0;
	}
	if (read_h->num_planes !=hdr->num_planes)
	{
		return 0;
	}
	if (read_h->bits_per_pixel != hdr->bits_per_pixel)
	{
		return 0;
	}
	if (read_h->compression != hdr->compression)
	{
		return 0;
	}
	if (read_h->image_size_bytes != hdr->image_size_bytes)
	{
		return 0;
	}
	if (read_h->x_resolution_ppm != hdr->x_resolution_ppm)
	{
		return 0;
	}
	if (read_h->y_resolution_ppm != hdr->y_resolution_ppm)
	{
		return 0;
	}
	if (read_h->num_colors != hdr->num_colors)
	{
		return 0;
	}
	if (read_h-> important_colors != hdr->important_colors)
	{
		return 0;
	}
	free(read_h);
	return 1;


}


