#include "common_header.h"

int main()
{
	int result = sample_triangle(file_path + "sample_triangle.vert", file_path + "sample_triangle.frag");
	cout << "Result:\t" << result << endl;
	return 0;
}