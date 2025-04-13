#include <vector>
#include <algorithm>


struct Box
{
    float x, y, z, l, w, h, heading;
    float score;
};


float get_iou(const Box& b1, const Box& b2)
{
    /* TODO: Implement iou of two 3D bounding boxes*/
    return 0.0f;
}

float get_F1_score(std::vector<Box>& preds, const std::vector<Box>& gts,
        const float iou_thres)
{
    /* precision = TP / (TP + FP)*/
    /* recall = TP (TP + FN) */
    /* F1-score = 2 (1 / precision + 1 / recall) */
    /* Sort the preds in decreasing order of scores. */
    std::sort(preds.begin(), preds.end(),
            [](const Box& lhs, const Box& rhs){return lhs.score > rhs.score;});

    int gt_cnt = gts.size();  // TP + FN
    int pd_cnt = preds.size(); // TP + FP

    std::vector<bool> gt_matched(gts.size(), false);

    int tp = 0;
    for (int i = 0; i < preds.size(); ++i)
    {
        float max_iou = 0;
        float max_iou_gt_idx = -1;

        for (int j = 0; j < gts.size(); ++j)
        {
            if (gt_matched[j]) continue;

            float curr_iou = get_iou(preds[i], gts[j]);

            if (curr_iou > max_iou)
            {
                max_iou = curr_iou;
                max_iou_gt_idx = j;
            }
        }

        if (max_iou > iou_thres)
        {
            /* Find one True Positive. */
            gt_matched[max_iou_gt_idx] = true;
            ++tp;
        }
    }

    /* float eps = 1e-9; */
    float precision = float(tp) / float(pd_cnt);
    float recall = float(tp) / float(gt_cnt);

    return 2.0f / (1.0f / precision + 1.0f / recall);
}

int
main()
{

}
