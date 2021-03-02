#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#if defined(ABC_NAMESPACE)
namespace ABC_NAMESPACE
{
#elif defined(__cplusplus)
extern "C"
{
#endif

    // procedures to start and stop the ABC framework
    // (should be called before and after the ABC procedures are called)
    void Abc_Start();
    void Abc_Stop();

    // procedures to get the ABC framework and execute commands in it
    typedef struct Abc_Frame_t_ Abc_Frame_t;

    Abc_Frame_t *Abc_FrameGetGlobalFrame();
    int Cmd_CommandExecute(Abc_Frame_t *pAbc, const char *sCommand);

#if defined(ABC_NAMESPACE)
}
using namespace ABC_NAMESPACE;
#elif defined(__cplusplus)
}
#endif

void cec_by_abc(char *abcrc, char *genlib, char *golden, char *revise, double *runtimes)
{
    // variables
    Abc_Frame_t *pAbc;
    char Command[1000];
    clock_t clkRead, clkMiter, clkCec, clk;

    // start the ABC framework
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    // load the abc.rc file
    sprintf(Command, "source %s", abcrc);
    if (Cmd_CommandExecute(pAbc, Command))
    {
        fprintf(stderr, "Cannot execute command \"%s\".\n", Command);
    }

    // read the library file
    clk = clock();
    sprintf(Command, "read_library %s", genlib);
    if (Cmd_CommandExecute(pAbc, Command))
    {
        fprintf(stderr, "Cannot execute command \"%s\".\n", Command);
    }
    // read the golden file
    sprintf(Command, "r -m %s", golden);
    if (Cmd_CommandExecute(pAbc, Command))
    {
        fprintf(stderr, "Cannot execute command \"%s\".\n", Command);
    }
    // read the revised file
    sprintf(Command, "r -m %s", revise);
    if (Cmd_CommandExecute(pAbc, Command))
    {
        fprintf(stderr, "Cannot execute command \"%s\".\n", Command);
    }
    clkRead = clock() - clk;

    /*
    // build the miter
clk = clock();
    sprintf( Command, "miter %s %s", golden, revise );
    if ( Cmd_CommandExecute( pAbc, Command ) )
    {
        fprintf( stderr, "Cannot execute command \"%s\".\n", Command );
    }
clkMiter = clock() - clk;
*/
    // perform verification
    clk = clock();
    sprintf(Command, "cec %s %s", golden, revise);
    if (Cmd_CommandExecute(pAbc, Command))
    {
        fprintf(stderr, "Cannot execute command \"%s\".\n", Command);
    }
    clkCec = clock() - clk;

    // stop the ABC framework
    Abc_Stop();
    runtimes[0] = (double)(clkRead) / CLOCKS_PER_SEC;
    runtimes[1] = (double)(clkCec) / CLOCKS_PER_SEC;
}

void evaluate(char *abcrc, char *genlib, char *root_path, int batch)
{
    char *cases[] = {
        "c1355",
        "c1908",
        "c3540",
        "c432",
        "c499",
        "c5315",
        "c6288",
        "c7552",
        "c880",
        // "adder",
        // "bar",
        // "decoder",
        // "divisor",
        // "log2",
        // "max",
        // "multiplier",
        // "sin"
    };
    const int cases_size = sizeof(cases) / sizeof(cases[0]);
    double avg[cases_size][2];
    char golden[1000], revise[1000];
    double *runtimes = (double *)malloc(sizeof(double) * 2);

    for (int i = 0; i < batch; ++i)
    {
        printf(">>> Iterator #%d\n", i + 1);
        for (size_t j = 0; j < cases_size; ++j)
        {
            printf("    >>> case %s\n", cases[j]);
            sprintf(golden, "%s/golden/gf_abc_%s.v", root_path, cases[j]);
            sprintf(revise, "%s/revise/rf_abc_%s.v", root_path, cases[j]);
            cec_by_abc(abcrc, genlib, golden, revise, runtimes);
            if (i == 0)
            {
                avg[j][0] = runtimes[0];
                avg[j][1] = runtimes[1];
            }
            else
            {
                avg[j][0] += runtimes[0];
                avg[j][1] += runtimes[1];
            }
            runtimes[0] = 0.0;
            runtimes[1] = 0.0;
        }
    }
    free(runtimes);
    printf(">>> Iterator over!\n");
    for (size_t j = 0; j < cases_size; ++j)
    {
        printf("%s\t%0.6f\t%0.6f\n", cases[j], avg[j][0] / batch, avg[j][1] / batch);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        evaluate(argv[1], argv[2], argv[3], atoi(argv[4]));
    }
    else
    {
        printf("Please input three parameters, like \"./cec_abc <abc.rc> <library.genlib> <the root of the golden and revised files> <batch>\".\n");
    }
    return 0;
}