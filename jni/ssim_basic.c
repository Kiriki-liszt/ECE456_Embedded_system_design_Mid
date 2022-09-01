#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#include <sys/time.h>

struct timeval tstart, tfinish;
double tsecs;

int main(){

	double Gaussian_kernel[11][11] = {
		{1.05757e-06,   7.81441153305360e-06,   3.70224770827489e-05,   0.000112464355116679,   0.000219050652866017,   0.000273561160085806,   0.000219050652866017,   0.000112464355116679,   3.70224770827489e-05,   7.81441153305360e-06,   1.05756559815326e-06},
		{7.81441153305360e-06,  5.77411251978637e-05,   0.000273561160085806,   0.000831005429087199,   0.00161857756253439,    0.00202135875836257,    0.00161857756253439,    0.000831005429087199,   0.000273561160085806,   5.77411251978637e-05,   7.81441153305360e-06},
		{3.70224770827489e-05,  0.000273561160085806,   0.00129605559384320,    0.00393706926284679,    0.00766836382523672,    0.00957662749024030,    0.00766836382523672,    0.00393706926284679,    0.00129605559384320,    0.000273561160085806,   3.70224770827489e-05},
		{0.000112464355116679,  0.000831005429087199,   0.00393706926284679,    0.0119597604100370, 0.0232944324734871, 0.0290912256485504, 0.0232944324734871, 0.0119597604100370, 0.00393706926284679,    0.000831005429087199,   0.000112464355116679},
		{0.000219050652866017,  0.00161857756253439,    0.00766836382523672,    0.0232944324734871, 0.0453713590956603, 0.0566619704916846, 0.0453713590956603, 0.0232944324734871, 0.00766836382523672,    0.00161857756253439,    0.000219050652866017},
		{0.000273561160085806,  0.00202135875836257,    0.00957662749024030,    0.0290912256485504, 0.0566619704916846, 0.0707622377639470, 0.0566619704916846, 0.0290912256485504, 0.00957662749024030,    0.00202135875836257,    0.000273561160085806},
		{0.000219050652866017,  0.00161857756253439,    0.00766836382523672,    0.0232944324734871, 0.0453713590956603, 0.0566619704916846, 0.0453713590956603, 0.0232944324734871, 0.00766836382523672,    0.00161857756253439,    0.000219050652866017},
		{0.000112464355116679,  0.000831005429087199,   0.00393706926284679,    0.0119597604100370, 0.0232944324734871, 0.0290912256485504, 0.0232944324734871, 0.0119597604100370, 0.00393706926284679,    0.000831005429087199,   0.000112464355116679},
		{3.70224770827489e-05,  0.000273561160085806,   0.00129605559384320,    0.00393706926284679,    0.00766836382523672,    0.00957662749024030,    0.00766836382523672,    0.00393706926284679,    0.00129605559384320,    0.000273561160085806,   3.70224770827489e-05},
		{7.81441153305360e-06,  5.77411251978637e-05,   0.000273561160085806,   0.000831005429087199,   0.00161857756253439,    0.00202135875836257,    0.00161857756253439,    0.000831005429087199,   0.000273561160085806,   5.77411251978637e-05,   7.81441153305360e-06},
		{1.05756559815326e-06,  7.81441153305360e-06,   3.70224770827489e-05,   0.000112464355116679,   0.000219050652866017,   0.000273561160085806,   0.000219050652866017,   0.000112464355116679,   3.70224770827489e-05,   7.81441153305360e-06,   1.05756559815326e-06}
	};

	BITMAPINFOHEADER bitmapInfoHeader;

	unsigned char* imageData = NULL;
	unsigned char* imageData_test = NULL;
	unsigned char* Orign_gray = NULL;
	unsigned char* Test_gray = NULL;
	unsigned int width, height;

	/* image content allocation */
	unsigned char redOriTemp, greenOriTemp, blueOriTemp;
	unsigned char redSampleTemp, greenSampleTemp, blueSampleTemp;

	/* fidelity calculation allocation */
	double mu1, mu2, stdOri, stdSample, stdOriSample, k1, k2, c1, c2, sum_ssim, mssim, sigma1_sq, sigma2_sq, mu1_mu2, mu1_sq, mu2_sq, sigma12;
	unsigned int lwHor, lwVer;

			// calculate SSIM
		k1 = 0.01;
		k2 = 0.03;

		// power -> constant
		c1 = 6.5025;
		c2 = 58.5225;

	/* counter allocation */
	unsigned long x, y;
	unsigned char xx, yy;


	unsigned char* filename;
	unsigned char* test;

	//added
	unsigned char size_uchar = sizeof(unsigned char);
	double width_x_height;
	double kernel=0, og=0, tg=0, ogt=0;
	unsigned int y_width, y_width_x_31, y_width_x_32; // unsigned int?
	int yyy, xyxy;

	//// For debugging
	//// for (int i = 0; i<=0; i++){
	for ( unsigned char i = 0 ; i <= 29 ; i++){
		//added
		filename = "testTID/I01.bmp\0testTID/I01.bmp\0testTID/I01.bmp\0testTID/I01.bmp\0testTID/I01.bmp\0testTID/I02.bmp\0testTID/I02.bmp\0testTID/I02.bmp\0testTID/I02.bmp\0testTID/I02.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I03.bmp\0testTID/I04.bmp\0testTID/I04.bmp\0testTID/I04.bmp\0testTID/I04.bmp\0testTID/I04.bmp\0testTID/I05.bmp\0testTID/I05.bmp\0testTID/I05.bmp\0testTID/I05.bmp\0testTID/I05.bmp\0" + 16*i;
		test = "testTID/i01_16_1.bmp\0testTID/i01_16_2.bmp\0testTID/i01_16_3.bmp\0testTID/i01_16_4.bmp\0testTID/i01_16_5.bmp\0testTID/i02_16_1.bmp\0testTID/i02_16_2.bmp\0testTID/i02_16_3.bmp\0testTID/i02_16_4.bmp\0testTID/i02_16_5.bmp\0testTID/i03_11_1.bmp\0testTID/i03_11_2.bmp\0testTID/i03_11_3.bmp\0testTID/i03_11_4.bmp\0testTID/i03_11_5.bmp\0testTID/i03_16_1.bmp\0testTID/i03_16_2.bmp\0testTID/i03_16_3.bmp\0testTID/i03_16_4.bmp\0testTID/i03_16_5.bmp\0testTID/i04_16_1.bmp\0testTID/i04_16_2.bmp\0testTID/i04_16_3.bmp\0testTID/i04_16_4.bmp\0testTID/i04_16_5.bmp\0testTID/i05_16_1.bmp\0testTID/i05_16_2.bmp\0testTID/i05_16_3.bmp\0testTID/i05_16_4.bmp\0testTID/i05_16_5.bmp\0" + 21*i;
		
		imageData       = (unsigned char*) malloc(589824);
		imageData_test  = (unsigned char*) malloc(589824);

		// read images
		LoadBitmapFile( filename,   &width,     &height,    imageData );
		LoadBitmapFile( test,       &width,     &height,    imageData_test );

		//added
		width_x_height = width*height;
		
		Orign_gray      = (unsigned char*) calloc(width_x_height, size_uchar);
		Test_gray       = (unsigned char*) calloc(width_x_height, size_uchar);
		
		// compute local window SSIM (8 x 8)
		lwHor = (int)(width -5);
		lwVer = (int)(height -5);

		gettimeofday(&tstart, NULL);

		// rgb2gray
		// y*width -> y_width
		// y_width + x -> y_width_x
		// y_width_x * 3 -> y_width_x_3
		// imageData access problem??
		for(y = 0; y < height; y++){
			y_width = y * width;
			for(x = 0; x < width; x+=2){

				y_width_x_31 = (y_width + x) * 3;

				redOriTemp      = imageData[y_width_x_31 + 0];
				greenOriTemp    = imageData[y_width_x_31 + 1];
				blueOriTemp     = imageData[y_width_x_31 + 2];
				Orign_gray[y_width + x] = 0.299 * redOriTemp + 0.587 * greenOriTemp + 0.114 * blueOriTemp + 0.5;
				
				redSampleTemp   = imageData_test[y_width_x_31 + 0];
				greenSampleTemp = imageData_test[y_width_x_31 + 1];
				blueSampleTemp  = imageData_test[y_width_x_31 + 2];
				Test_gray[y_width + x] = 0.299 * redSampleTemp + 0.587 * greenSampleTemp + 0.114 * blueSampleTemp + 0.5;
				
				y_width_x_32 = (y_width + x+1) * 3;

				redOriTemp      = imageData[y_width_x_32 + 0];
				greenOriTemp    = imageData[y_width_x_32 + 1];
				blueOriTemp     = imageData[y_width_x_32 + 2];
				Orign_gray[y_width + x+1] = 0.299 * redOriTemp + 0.587 * greenOriTemp + 0.114 * blueOriTemp + 0.5;
				
				redSampleTemp   = imageData_test[y_width_x_32 + 0];
				greenSampleTemp = imageData_test[y_width_x_32 + 1];
				blueSampleTemp  = imageData_test[y_width_x_32 + 2];
				Test_gray[y_width + x+1] = 0.299 * redSampleTemp + 0.587 * greenSampleTemp + 0.114 * blueSampleTemp + 0.5;
				
			}
		}
		
		sum_ssim = 0;
		// MSSIM

		for(y = 5; y < lwVer; y++){
			for(x = 5; x < lwHor; x++){
				mu1 = 0;
				mu2 = 0;
				sigma1_sq = 0;
				sigma2_sq = 0;
				sigma12 = 0;
				
				for(yy = 0; yy < 11; yy++) {
					yyy = (y-5+yy)*width;
					for(xx = 0; xx < 11; xx++) {
						kernel = Gaussian_kernel[xx][yy];
						xyxy = yyy + (x-5+xx);
						og = (double)Orign_gray[xyxy] * kernel;
						tg = (double)Test_gray[xyxy] * kernel;

						mu1 += og;
						mu2 += tg;

						sigma1_sq   += (double)Orign_gray[xyxy] * og;
						sigma2_sq   += (double)Test_gray[xyxy] * tg;

						sigma12     += (double)Orign_gray[xyxy] * tg;
					}
				}

				mu1_sq	= mu1*mu1;
				mu2_sq	= mu2*mu2;
				mu1_mu2	= mu1*mu2;

				sigma1_sq -= mu1_sq;
				sigma2_sq -= mu2_sq;
				sigma12 -= mu1_mu2;
				
				//printf("mu1_sq: %f \n",mu1_sq);
				//printf("mu2_sq: %f \n",mu2_sq);
				//printf("mu1_mu2: %f \n",mu1_mu2);
				
				//printf("sigma1_sq: %f \n",sigma1_sq);
				//printf("sigma2_sq: %f \n",sigma2_sq);
				//printf("sigma12: %f \n",sigma12);

				sum_ssim += ((2*mu1_mu2 + c1)*(2*sigma12 + c2))/((mu1_sq + mu2_sq + c1)*(sigma1_sq + sigma2_sq + c2));
			
			}
		}

		mssim = sum_ssim / ((width-10)*(height-10));

		gettimeofday(&tfinish, NULL);

		tsecs = (tfinish.tv_sec - tstart.tv_sec) + 1E-6 * (tfinish.tv_usec - tstart.tv_usec);

		printf("main : elapsed time - %f sec\n",tsecs);
		//printf("sum_ssim = %5.5f\n", sum_ssim);
		//printf("lwHor*lwVer = %5.5f\n", lwHor*lwVer);
		printf("MSSIM = %5.5f\n", mssim);

		free(imageData);   
		free(imageData_test);
		
		free(Orign_gray);
		free(Test_gray);
	}
}


