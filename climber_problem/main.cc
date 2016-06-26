#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vector>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

class Mount {
public:
	int left;
	int right;
	int high;
	void Set(int *in) {
		left = in[0];
		right = in[1];
		high = in[2];
	}
};

int resolve(const char* input)
{
	int n = 0, in[3], len = 0;
	const char *pos;

	//input mount's data
	pos = strchr(input, '\n');
	sscanf(input, "%d\n", &n);
	std::vector<Mount> mounts(n);
	for (int i = 0; i < n; i++) {
		sscanf(++pos, "%d,%d,%d\n", &in[0], &in[1], &in[2]);
		mounts[i].Set(in);
		if (len < in[1])
			len = in[1];
		pos = strchr(pos , '\n');
	}
	
	//generate road indicates the most high mount at every pos
	std::vector<int> road(len, 0);
	for (int i = 0; i < n; i++) {
		for (int j = mounts[i].left; j < mounts[i].right; j++) {
			const int tempHigh = mounts[i].high;
			if (road[j] < tempHigh) road[j] = tempHigh;
		}
	}
	
	//calculate vertical dis
	int vsum = 0;
	for (int i = 1; i < len; i++) {
		vsum += abs(road[i] - road[i - 1]);
	}
	vsum += (road[0] + road[len - 1]);
	//calculate horizontal dis
	return (vsum + len);
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
		"1\n0,2,3\n",
		"3\n0,2,3\n1,5,4\n3,5,1",
		"3\n0,2,3\n1,5,4\n3,4,5",
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 8, 13, 15};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
