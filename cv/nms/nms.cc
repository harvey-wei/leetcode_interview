#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#define eps (std::numeric_limits<float>::epsilon())
struct Box
{
	/**
	 *  o--------> x
	 *  |
	 *  |
	 *  |y
	 */
	float x_tl;
	float y_tl;
	float x_br;
	float y_br;
	float conf_score;

	Box(float _x_tl, float _y_tl, float _x_br, float _y_br, float _conf_score)
		: x_tl(_x_tl), y_tl(_y_tl), x_br(_x_br), y_br(_y_br)
	{}
};


float iou(const Box& box_one, const Box& box_two)
{
	float x_tl_i = std::max<float>(box_one.x_tl, box_two.x_tl);
	float y_tl_i = std::max<float>(box_one.y_tl, box_two.y_tl);

	float x_br_i = std::min<float>(box_one.x_br, box_two.x_br);
	float y_br_i = std::min<float>(box_one.y_br, box_two.y_br);

	float iou = 0.0f;
	float x_len_i = std::abs(x_br_i - x_tl_i);
	float y_len_i = std::abs(y_br_i - y_tl_i);

	/* if (std::abs(x_br_i - x_tl_i) > eps && std::abs(y_br_i - y_tl_i) > eps) */
	if (x_len_i > eps && y_len_i > eps)
	{
		float inter = x_len_i * y_len_i;
		float uni = std::abs((box_one.x_br - box_one.x_tl) * (box_one.y_br - box_one.y_tl))
				+ std::abs((box_two.x_br - box_two.x_tl) * (box_two.y_br - box_two.y_tl)) - inter;

		iou = inter / (uni + eps);
	}

	return iou;
}

void nms(std::vector<Box>& boxes, const float& iou_thres, std::vector<Box>& keeped_boxes)
{
	/* sort the box in non-increasing order of conf_score */
	std::sort(boxes.begin(), boxes.end(),
			[](const Box& lhs, const Box& rhs)
			{
				// larger score is placed in front.
				return lhs.conf_score > rhs.conf_score;
			});

	/* Compute IOU. */
	int box_cnt = boxes.size();
	std::vector<std::vector<float>> iou_mat(box_cnt, std::vector<float>(box_cnt, 0.0f));
	for (int r = 0; r < box_cnt; ++r)
	{
		for (int c = r + 1; c < box_cnt; ++r)
		{
			iou_mat[r][c] = iou(boxes[r], boxes[c]);
		}
	}

	std::vector<bool> is_excluded(boxes.size(), false);

	/* Iterate the box in increasing order of confidence score. */
	for (int i = 0; i < box_cnt; ++i)
	{
		if (is_excluded[i]) continue;

		/* Check all boxes with samller score*/
		for (int j = i + 1; j < box_cnt; ++j)
		{
			if (is_excluded[j]) continue;

			if (iou_mat[i][j] > iou_thres)
			{
				is_excluded[j] = true;
			}
		}
	}

	keeped_boxes.clear();
	for (int i = 0; i < box_cnt; ++i)
	{
		if (!is_excluded[i])
		{
			keeped_boxes.emplace_back(std::move(boxes[i]));
		}
	}
}

int main()
{
	return 0;
}
