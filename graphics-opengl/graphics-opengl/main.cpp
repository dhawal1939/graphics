#include "common_header.h"

int main()
{
	int result = sample_rectangle(file_path + "sample_rectangle.vert", file_path + "sample_rectangle.frag");
	cout << "Result:\t" << result << endl;
	return 0;
}