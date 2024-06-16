#include <iostream>
#include <vector>
using namespace std;

struct Box
{
    float x_tl;
    float y_tl;
    float x_br;
    float y_br;
    float score; /* [0, 1]*/

    Box(float _x_tl, float _y_tl, float _x_br, float _y_br, float _score)
        : x_tl(_x_tl), y_tl(_y_tl), x_br(_x_br), y_br(_y_br), score(_score)
    {}
};

float iou(const Box& box_one, const Box& box_two)
{
    /* Assume the box is axis-aligned. */
    /*
        ------------------->x
        |   TL1-------
        |    |      |
        |    |      |
        |    | TL2--|-----
        |    |  | I |    |
        |    ---|----BR1 |
        |       |        |
        |       |        |
        |      |--------BR2
        y
    */
    float iou = 0.0f;

    float x_tl_i = max<float>(box_one.x_tl, box_two.x_tl);
    float y_tl_i = max<float>(box_one.y_tl, box_two.y_tl);
    float x_br_i = min<float>(box_one.x_br, box_two.x_br);
    float y_br_i = min<float>(box_one.y_br, box_two.y_br);

    float inter = max<float>(0.0f, x_br_i - x_tl_i) * max<float>(0.0f, y_br_i - y_tl_i);
    float box_one_area = abs((box_one.x_br - box_one.x_tl) * (box_one.y_br - box_one.y_tl));
    float box_two_area = abs((box_two.x_br - box_two.x_tl) * (box_two.y_br - box_two.y_tl));

    if (abs(box_one_area) > 1e-9 && abs(box_two_area) > 1e-9)
    {
        iou = inter / (box_one_area + box_two_area - inter);
    }

    return iou;
}

void nms(std::vector<Box>& boxes, float& iou_thres, std::vector<Box>& keeped_boxes)
{
    /* sort the boxes by its score in non-ascending order in in-place way. */
    std::sort(boxes.begin(), boxes.end(), [](const Box& lhs, const Box& rhs){
        return lhs.score > rhs.score;
        });

    std::vector<bool> is_keeped(boxes.size(), true);

    std::vector<std::vector<float>> iou_matrix(boxes.size(), std::vector<float>(boxes.size(), 0.0f));

    for (int i = 0; i < boxes.size(); ++i)
    {
     for (int j = i; j < boxes.size(); ++j)
     {
        if (i == j)
        {
          iou_matrix[i][j] = 1.0f;
          continue;
        }

        iou_matrix[i][j] = iou(boxes[i], boxes[j]);
        iou_matrix[j][i] = iou_matrix[i][j];
     }
    }


    for (int i = 0; i < boxes.size(); ++i)
    {
        /* Note: Skip if the current box is excluded! */
        if (!is_keeped[i]) continue;

        /* The key Check all the other non-excluded boxes with box i of smaller score*/
        for (int j = i + 1; iou_matrix[i].size(); ++j)
        {
            if (!is_keeped[j]) continue;

            if (iou_matrix[i][j] > iou_thres)
            {
                is_keeped[j] = false;
            }
        }
    }

    keeped_boxes.clear();

    for (int i = 0; i < is_keeped.size(); ++i)
    {
        if (is_keeped[i])
        {
            keeped_boxes.push_back(boxes[i]);
        }
    }
}

int main()
{
    Box box_one(0.0, 0.0, 1.0, 1.0, 0.5);
    Box box_two(0.5, 0.5, 1.5, 1.5, 0.8);

    std::cout << "IOU " << iou(box_one, box_two);

    return 0;
}
