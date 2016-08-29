/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 #include <stdio.h>
 #include <cs50.h>
 //#include <string.h>
 
 bool isJpegBeginning(char *buffer);
 void jpegNumber(char *filename, int counter);

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    FILE* img;
    char buffer[512];
    int count = 0;
    bool passedGarbage = false;
    while (fread(buffer, 512, 1, file) == 1) {
        if (isJpegBeginning(buffer)) {
            if (passedGarbage) {
                fclose(img);
            }
            passedGarbage = true;
            char fileName[12];
            jpegNumber(fileName, count);
            img = fopen(fileName, "a");
            
            fwrite(buffer, 512, 1, img);
            count++;
        } else if (passedGarbage) {
            fwrite(buffer, 512, 1, img);
        } else {
            
        }
    }
    fclose(img);
    fclose(file);
}

bool isJpegBeginning(char *buffer) {
    if (buffer[0] == (char) 0xff && buffer[1] == (char) 0xd8 && buffer[2] == (char) 0xff) {
        return true;
    } else {
        return false;
    }
}

void jpegNumber(char *filename, int counter) {
    // Bad function, I know, but  ¯\_(ツ)_/¯
    if (counter < 10) {
        sprintf(filename, "00%i.jpg", counter);
    } else {
        sprintf(filename, "0%i.jpg", counter);
    }
}