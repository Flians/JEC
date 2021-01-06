#include "util.h"

void Util::unique_element_in_vector(vector<Node *> &v)
{
    sort(v.begin(), v.end(), [](const Node *A, const Node *B) {
        if (A->id == B->id)
        {
            return A->outs.size() > B->outs.size();
        }
        else
        {
            return A->id < B->id;
        }
    });
    vector<Node *>::iterator vector_iterator = unique(v.begin(), v.end());
    if (vector_iterator != v.end())
    {
        v.erase(vector_iterator, v.end());
    }
}