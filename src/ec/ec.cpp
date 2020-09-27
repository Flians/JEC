#include "ec.h"

ec::ec(const string &path_output)
{
    this->fout.open(path_output, ios::out);
    if (!this->fout.is_open())
    {
        if (libfile::createDirectory(path_output) == -1) {
            error_fout("The output file can not be open!");
        }
        this->fout.open(path_output, ios::out);
    }
}

ec::~ec()
{
    this->fout.flush();
    this->fout.close();
}

void ec::print_PIs_value(vector<Node *> &PIs, ofstream &output)
{
    for (auto pi : PIs)
    {
        output << pi->name << " " << pi->val << endl;
    }
}

void ec::print_PIs_value(vector<Node *> &PIs, FILE *output)
{
    for (auto pi : PIs)
    {
        fprintf(output, "%s %d", pi->name.c_str(), pi->val);
    }
}