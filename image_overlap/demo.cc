#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> padding2D(vector<vector<int>>& img, int ph, int pw) {
		// padding ph lines of 0 on top and bottom, pw lines of 0 on left and right
        int new_height = img.size() + 2*ph;
        int new_width = img[0].size()+2*pw;
        vector<vector<int>> ret(new_height, vector<int>(new_width, 0));
		/* Maybe this could be improved? */
        for(int i = ph; i < ph+img.size(); i++)
            for(int j = pw; j < pw+img[0].size(); j++)
                ret[i][j] = img[i-ph][j-pw];
        return ret;
    }
    vector<vector<int>> conv2D(vector<vector<int>>& img, vector<vector<int>>& kernal, int step = 1)
    {
        int out_h = img.size() - kernal.size() + 1;
        int out_w = img[0].size() - kernal[0].size() + 1;
        vector<vector<int>> ret(out_h, vector<int>(out_w, 0));
        for(int i = 0; i < out_h; i++) {
            for(int j = 0; j < out_w; j++) {
                // compute ret[i][j]
                for(int muli = 0; muli < kernal.size(); muli++) {
                    for(int mulj = 0; mulj < kernal[0].size(); mulj++) {
						/* By skipping 0 multiplcation, time increased from 376ms to 252ms */
                        if(img[i * step + muli][j * step + mulj]==0 || kernal[muli][mulj]==0)
                            continue;
                        ret[i][j] += img[i * step + muli][j * step + mulj] * kernal[muli][mulj];
                    }
                }
            }
        }
        return ret;
    }
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        // use 2d convonlution, e.g. A conv B, B as kernal
        // first padding
        int ph = B.size()-1;
        int pw = B[0].size()-1;
        vector<vector<int>> padded_img = padding2D(A, ph, pw);

        // then conv2D
        vector<vector<int>> img = conv2D(padded_img, B);

        int ans = 0;
        for(int i = 0; i < img.size(); i++)
            for(int j = 0; j < img[0].size(); j++)
                if(ans < img[i][j])
                    ans = img[i][j];
        return ans;
    }
};

int main()
{
    return 0;
}
