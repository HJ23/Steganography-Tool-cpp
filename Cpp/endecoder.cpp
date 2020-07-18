#include "../Sources/endecoder.h"

// this method gets character and converts it to binary

int* ascii_2_binary(char a) {
	int *tmp=new int[8]();
	
    for (int x = 0; x < 8; x++) {
        tmp[7 - x] = a & 1;
        a = a >> 1;
    }
    
    return tmp;
}

// this one converts binary to character

char binary_2_ascii(int* tmp) {
    int ret = 0;
    for (int x = 0; x < 8; x++)
        ret += tmp[7 - x] << x;
    return ret;
}

// initialize all pixels for text embedding
void encoder::initialize() {
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            (image.at<cv::Vec3b>(x, y)[0] % 2 ? image.at<cv::Vec3b>(x, y)[0] -= 1 : image.at<cv::Vec3b>(x, y)[0] += 0);
            (image.at<cv::Vec3b>(x, y)[1] % 2 ? image.at<cv::Vec3b>(x, y)[1] -= 1 : image.at<cv::Vec3b>(x, y)[1] += 0);
            (image.at<cv::Vec3b>(x, y)[2] % 2 ? image.at<cv::Vec3b>(x, y)[2] -= 1 : image.at<cv::Vec3b>(x, y)[2] += 0);
        }
    }
}

// check for some credentials

encoder::encoder(const std::string &text, const std::string &image_path) {
    image = imread(image_path, cv::IMREAD_COLOR);
    try {
        if (image.empty())
            throw IMAGE_NULL_EXCEPTION();
        
        if ((image.rows * image.cols) < (3 * text.size()))
            throw Text_SO_BIG();
        else {
            this->text = text;
            initialize();
        }
    }
    catch (IMAGE_NULL_EXCEPTION e) {
        e.show_error();
        exit(0);
    }
    catch (Text_SO_BIG e) {
        e.show_error();
        exit(0);
    }

}

encoder::~encoder() {
    image.release();
}

// start embedding here

void encoder::start() {
    int k = 0, z = 0;
    clock_t start = clock();
    
    int *abin = ascii_2_binary(text[z]);
    
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            if (k == 9) {
                k = 0;
                z++;
                if (z == text.size())
                    goto A;
                else 
                    abin=ascii_2_binary(text[z]);
                    
            } else {
                image.at<cv::Vec3b>(x, y)[0] += abin[8 - k];
                image.at<cv::Vec3b>(x, y)[1] += abin[7 - k];
                image.at<cv::Vec3b>(x, y)[2] += abin[6 - k];
                k += 3;
            }
        }
    }
    
    A:
      std::cout << "*******************************************************************" << std::endl;
      std::cout << "Encoding finished successfully duration :" << (float(clock() - start) / CLOCKS_PER_SEC) << std::endl;
      std::cout << "*******************************************************************" << std::endl;
}


// check decoding finished ?

bool summation(int* bit) {
    int sum = 0;
    for (int x = 0; x < 9; x++)
        sum += bit[x];
    if (sum == 0)
        return false;
    else
        return true;
}


// save encoded image file

void encoder::save(std::string image_path) {
    try {
        if (image.empty())
            throw IMAGE_NULL_EXCEPTION();
        else if (!(image_path[image_path.size() - 1] == 'g' && image_path[image_path.size() - 2] == 'n' &&
                   image_path[image_path.size() - 3] == 'p' && image_path[image_path.size() - 4] == '.'))
            throw IMAGE_EXTENSION_ERROR();
            
        else {
            imwrite(image_path, image);
            std::cout << "Image saved in indicated path " << std::endl;
        }

    } catch (IMAGE_NULL_EXCEPTION e) {
        e.show_error();
        exit(0);
    }
    catch (IMAGE_EXTENSION_ERROR e) {
        e.show_error();
    }
}

// get image and decode

decoder::decoder(const std::string &image_path) {
    image = imread(image_path, cv::IMREAD_COLOR);
    try {
        if (image.empty())
            throw IMAGE_NULL_EXCEPTION();

    } catch (IMAGE_NULL_EXCEPTION e) {
        e.show_error();
        exit(0);
    }

}

void decoder::start() {
    int k = 0;
    text = "";
    int *rgb=new int[8];
    
    clock_t start = clock();
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            if (k == 9) {
                k = 0;
                if (!summation(rgb))
                    goto A;
                else
                    text += binary_2_ascii(rgb);

            } else {
                rgb[8 - k] = image.at<cv::Vec3b>(x, y)[0] % 2;
                rgb[7 - k] = image.at<cv::Vec3b>(x, y)[1] % 2;
                rgb[6 - k] = image.at<cv::Vec3b>(x, y)[2] % 2;
                k += 3;
            }
        }
    }
    A:
      std::cout << "*******************************************************************" << std::endl;
      std::cout << "Decoding finished successfully  duration :" << (float(clock() - start) / CLOCKS_PER_SEC) << std::endl;
      std::cout << "*******************************************************************" << std::endl;
    return;

}

inline void decoder::show() {
    std::cout << text<<std::endl;
}

decoder::~decoder() {
    image.release();
} 
