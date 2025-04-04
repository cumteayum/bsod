#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using namespace cv;
using namespace std;
vector<Vec3b> gruvbox_palette = {
    {54, 56, 60},    // Dark0
    {84, 92, 102},   // Dark4
    {147, 174, 189}, // Light4
    {199, 241, 251}, // Light0
    {33, 153, 215},  // Yellow
    {29, 36, 204},   // Red
    {26, 151, 152},  // Green
    {136, 133, 69},  // Aqua
    {134, 98, 177}   // Purple
};
Vec3b findClosestColor(Vec3b pixel) {
    Vec3b closestColor;
    double minDist = DBL_MAX;
    for (const auto& color : gruvbox_palette) {
        double dist = norm(pixel, color);
        if (dist < minDist) {
            minDist = dist;
            closestColor = color;
        }
    }
    return closestColor;
}
void applyGruvbox(const string& inputPath, const string& outputPath) {
    Mat image = imread(inputPath);
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!\n";
        return;
    }
    Mat output = image.clone();
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            output.at<Vec3b>(y, x) = findClosestColor(image.at<Vec3b>(y, x));
        }
    }
    imwrite(outputPath, output);
    cout << "Saved Gruvbox image to " << outputPath << endl;
}
int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: ./gruvbox_filter <input.jpg> <output.jpg>\n";
        return -1;
    }

    applyGruvbox(argv[1], argv[2]);
    return 0;
}
