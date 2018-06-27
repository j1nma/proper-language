#include "include/variables.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>

/* symbol/variable table where objects of program are allocated */
variable *variableTable[MAX_VARIABLES] = {0};

/* symbol/variable table where objects' names of program are allocated */
char *variableNameTable[MAX_VARIABLES] = {0};

void addVariableNameToId(int id, char *name)
{
    variableNameTable[id] = name;
}

variable getVariableFromId(int id)
{
    if (variableTable[id] == NULL)
    {
        fprintf(stderr, "Error: '%s' variable name not found.\n", variableNameTable[id]);
        exit(1);
    }
    return *variableTable[id];
}

char *getVariableType(variableType type)
{
    switch (type)
    {
    case TYPE_INT:
        return "integer";
    case TYPE_FLOAT:
        return "float";
    case TYPE_STRING:
        return "string";
    default:
        return "unknown";
    }
    return "";
}

variable createIntVariable(int value)
{
    variable v;
    v.type = TYPE_INT;
    v.value.intValue = value;
    return v;
}

variable createFloatVariable(float value)
{
    variable v;
    v.type = TYPE_FLOAT;
    v.value.floatValue = value;
    return v;
}

variable createStringVariable(char *value)
{
    variable v;
    v.type = TYPE_STRING;
    v.value.stringValue = malloc(strlen(value) + 1);
    strcpy(v.value.stringValue, value);
    return v;
}

variable assignVariable(int id, variable v)
{

    variable *res = malloc(4 * sizeof(*variableTable[0]));
    res->type = v.type;

    switch (v.type)
    {
    case TYPE_INT:
        res->value.intValue = v.value.intValue;
        break;

    case TYPE_FLOAT:
        res->value.floatValue = v.value.floatValue;
        break;

    case TYPE_STRING:
        res->value.stringValue = malloc(strlen(v.value.stringValue) + 1);
        strcpy(res->value.stringValue, v.value.stringValue);
        break;
    }

    freeVariable(variableTable[id]);
    variableTable[id] = res;

    return *res;
}

void printVariable(variable v)
{
    switch (v.type)
    {
    case TYPE_INT:
        printf("%d", v.value.intValue);
        break;
    case TYPE_FLOAT:
        printf("%f", v.value.floatValue);
        break;
    case TYPE_STRING:
        printf("%s", v.value.stringValue);
        break;
    }

}

void sleepVariable(variable v)
{
    printf("\n");
    switch (v.type)
    {
    case TYPE_INT:
        sleep(v.value.intValue);
        break;
    case TYPE_FLOAT:
        sleep(v.value.floatValue);
        break;
    }
}

void readVariable(variableType type, int id)
{
    if (type == TYPE_INT || type == TYPE_FLOAT)
    {
        double num;

        /* lg double [footnote] number with up to six digits of precision */
        scanf("%lg", &num);

        while (getchar() != '\n')
            ;

        if (ABS(num - (long)num) < FLOAT_ERROR)
        {
            assignVariable(id, createIntVariable((int)num));
        }
        else
        {
            assignVariable(id, createFloatVariable(num));
        }
    }
    else if (type == TYPE_STRING)
    {
        char *str = malloc(READ_STRING_SIZE);

        /* The buffer length is 1024, which includes room for the possible 
        1023 characters plus the null terminator: */
        scanf("%1023[^\n]", str);

        while (getchar() != '\n')
            ;

        assignVariable(id, createStringVariable(str));

        free(str);
    }
}

void freeVariable(variable *v)
{
    if (v == NULL)
        return;

    switch (v->type)
    {
    case TYPE_STRING:
        free(v->value.stringValue);
        break;
    default:
        /* nothing to be freed for TYPE_INT and TYPE_INT */
        break;
    }
}

void theShiningASCII(void)
{
    printf("...........-::````.s-.--::`.--..``````````````-:```` ``-`sNMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNmdhysooo+++++++:`..-/sho`` `.``````````````````````````..`.+mds/-\n");
    printf("...........-::``.`.s-..-/:`.--.```````````````--```````:.dMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNmdhysooooo+/```.`/y+`.``.```.````````````````````..`..`:hs-..\n");
    printf("...........-/:``.`.o:.-:/:`.-:.```````````````--```````:/NMMMMMMMMNmNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMNNNNNNNNNNNNNNNmhyso+++/`...`+y/-.` ..``.``````````````````````````-yy-..\n");
    printf("...........-::````.o:.-://`.--.```````````````.-````` .::MMMMMMNNNmdNmdddddddhddmNmddmmmdddhhhhhhhdddddhyyyddmNNNNmmdhsoo:```.`:hs:`. ..``.```````````````````````.``.os:..\n");
    printf("...........-:/.```.o:.-://`.--.```````````````.:``````.:+MNMMNNmddhmdyso++osoyhhmysysso+//:::::::://+oso+++++oydmmmmhhysy:``..`-hd/`.``.``.```````````````````````....:o/-:\n");
    printf("...........-:/`````+:.-://`.--.```````````````./``````.:yMMMNdhyooohs+////+++yhdyo/:--..---..---.-------::::::/+oymNmdhy+.``...-ydo..``-``.````````````````````````.`.-+++/\n");
    printf("...........-:/.````o:..://`.--.```````````````./``````-:dMNmhso+//sh+/::////oddy/:..........`..............---:::/ohNNmd:``....-ydy..``..`.`````````````````````````.../o/.\n");
    printf("........`..-:/.````o:`-:/+`.---.``````````````./``````:/mNdyo+///:+yo/////:/hmy/-..````...`...```..........----::::/odNm-``.--.-yhy:..`..`.````````````````````````....:/-`\n");
    printf("............:/.````+:`--/o`.---.``````````````./``````:oNhyo+//////+so/+/::omh+-....`````....```.............--::::/::hm-`..--.-+hh+`.``.`.``````````````````````..........\n");
    printf("............-:.````+:`-::o.`---```````````````./``````-ydsoo+///////+syo:::hh++:-...``````````````````........--::///-.s-`..--.-/yhs`-``.`.``````````````````````..........\n");
    printf("...........--:-````/:`.::o.`-:-.```````````````/``````+dhso+++///////oo+o++do:::-.``` ````````````````......-----:////-:.`...---:ohd+:``...````````````````````..........``\n");
    printf("...........----````//`.::o.`--:.```````````````:``````yNmhsoo++//////+///+yd/---.`      `````````````........-----::/+//`....--:-+yddo. ``.````````````````````...........`\n");
    printf("............-:.````//`.:-+.`--:.```````````````:`````.dNmdhyso++///://::::+d/....`     `````````````......--------:://+/`.-``..--:hdds.```.````````````````````............\n");
    printf("............-:-````//`.:-+.`:--.```````````````:`````.dNNmdhyoo+//////:::/oho:--.``   ````````..````....----------:::/++..-`..-:--yddy:```.````````````````````............\n");
    printf("............---````:/..:-+.`:::..``````````````:.````.dMMNmdhsso+++/+/:---/s:+-..`.```.....``...```......----------:::/+.`-....-.-odds+```.```````````````````.............\n");
    printf("............---````:/..::+.`:::.```````````````:.````-mNMNNmhyso+++//::---:s:::``   ``````......``.......---------::://+:`-`-..-.:/shso.``.``````````````````.............`\n");
    printf("............:--``.`-/..:-+.`:::..``````````````:.````/NMNNNmdysoo+++/::::::s/-/.```    ````......``.............--:::::/+`-.-..:.--:yoo:``..`````````````````.............`\n");
    printf("...........-:--.`.`-/..:-+-`-::..``````````````:.````oNMMNNmdys+++/+/::::::oo:/:.````` ````......``....-.........-----::+.-.-.---:--s+o/``..``..```````````````............\n");
    printf("...........-:--`..`-/..::o-`-::..``````````````:.````sNMMNNdhyso++///::----/o/:/-..``````..``..--.....-----......------:+-:.-.-:----s/o+.`..``..`````````````..............\n");
    printf("...........-::-`..`-/`.::o-`-::..``````````````:.```.sNNNmdhyssoo+//:://////+o++/--::::--::::---------://::::-------::/:/-:.-.---:--o:++.`...`...........```...............\n");
    printf("`..........-::-`..`-+..::o:`-::..``````````````:-```.sNmdhyyssoooo//+osyyyysyhhyysosssoo+++++//:::::///+++//+++//++osyhhs/:.-`.--:--o-/+.`..```..````````````..............\n");
    printf("...........-::-.```.+..::o:`-::..``````````````:-```.shyyyssoooosssyhdddddddmmNNNNmNNmdhhyyssoo+////++++osyyhddddmmddhhhds/.-`.--:-.o-:+-`.````..``````````````............\n");
    printf("...........-:/:.``..+..-:o:`.-:..``````````````--`.`.syoossoosssydmNNmmmmdddmNNNNNNNNNNNmmddhyso+++osssshdmmmNNmmmhyssssyy+.-`.--:-.o-./.`..``````````````````.............\n");
    printf("...........-:/:.`.`.+-.-:o:`.---.``````````````:-```./s++oosssyydmmmmmmmmmmddmdmNNNNNmmNNNNmmho/:://oyhddddhhhhhsssssyyyhs/.-`.--::.+-`.``..``````````````````.............\n");
    printf("..........--:/:.`.`./-.-:o/`.---.``````````````--```.:+o+ooosyhdmNNNNNNNNNNNmmhyhdNMNNNmNNmdhs/:--::+hddhhhdmmdhhmNNNNmmms:.-`.--:-.+-````..````````````````````.`.........\n");
    printf("...........-:/:.`.`.+:.-:o/`.-:-..`````````````.-```-//soossyhmNNNNNNNNNNmdy/:.`-yNNNNmhhdhyyo/:-.--/ydhhhdhs+:--sNNNNNNmy:..`.--:-.+-````..`````````````````...`````......\n");
    printf("...........-:/:.`.`./:.-:o+`.---...````````````.:```./:/ooooshhdddddhyyyso+///::/syhyso+/ossoo/:--.-:////+++:---:sysssydmy:.-`.:-:-.+-````.``````````.```````...`````......\n");
    printf("...........-:/:.`.`./:.-:++`.:--...``````````.`.:```-:--/+oooooooooooo+++++/////+ossyso++++++//:-----:::://:/://///:/+oos+-.-`.--:-.+-````.``````````.```````...`````......\n");
    printf("...........-:/:.`.``//.--/+`.:--...``````````.`./```::--:++++//+++++++osssssssssssso++///++/////:-----:/:/+oooooooooo+///:-..`.-.--./-``.`.``````````..``````...````.......\n");
    printf("...........-:::.`..`//`--//`.:-:...````````````./```::--:+++++++++//::---::///////:--:://////////:-...:::::::/++++/:---:/:-..`.:--..+-````.``````````..``````...````.......\n");
    printf("...........--:--...`//...:/.`/--...````````````./```::-:/ooo+o+++/////:-----....--....-::///////::..``.-:/::--------..-:/:-..`.:--..+-````.``````````..``````...````......`\n");
    printf(".......-...----...``/+...:/.`/:-...````````````./.``::-/+oso+++///////:::-..```...-----://////:/:-.` ``.://:::--------.:/:-.-`.:---./-````..````````````````.....``````....\n");
    printf(".......-...--::-..``/o..--/.`::-....`````````...:.``:::/+oso++++////::::--....```.-:////:::--:/:-.` ````-//:/+//:-------:-..:`.:---./-````..```````````````````````````....\n");
    printf("............--:-`..`:o..--/.`::-....`````````.`./..`:::oosso++++////:::::-----:/+oyyyyo//+++++oo+/----..-///+yhs+/::----:.--:`./-:-./-````..```````````````````````````....\n");
    printf("...........--:/-`..`:o-.--/.`--:....```````.`.../..`//+hyossoo++/////::::::://oshmdhhdhyydNNNNmddhsoo+++sdmdyyhdyo+/:::-:`-.-`./.--./-````..`````````````````````````......\n");
    printf("........-..--/::...`:o-.--:.`-::.``....``......./-.`/+ymhssssoooo++///////++oshddhyyyhmmmmddmNNNNmmmmdddmNmmhooyhyo+/::--`-.. .:.--`/-````..`````````````````````````......\n");
    printf("...........--+/:`..`-o-.-:/.`-::..``...``....`../-`./+ymdyyyssssoo+++++++oosydmdyyhyhyhhdddddmmNMNNNNNNNNmhhsoooyyso/:::.`.`. .:---.+:````..```````````````````````````....\n");
    printf("...........--:/:...`-o-.--:.`-::...`..`````.``../-`./+odmdhhyysssosoooooosshdmdhhhhhhhdhhhhhhyhdmNNNNNNNmhyysssyyhys+///..... `:-:-./: ````.```````````````````````````....\n");
    printf("............-:+:...`-o-.--:.`.-:...`..`````.``../-`./++hmmddyyyyysyysssssyhmmddhhhhdhdhdhhyhhyyhddmmmmdhyyyhyhhdhdhso+//``...``/-:-.+: ````.````````````````..`````````....\n");
    printf("............::/:`..`-o:.--/.`.::......````..`.../-..+++hNmmmhhyyyyyyssssyhddhhdhdhhhhhhhhhhhyyyyyyyyyhhhhyysshhhyhdyso+/``...``/-:-./:````...```````````````...``````......\n");
    printf("............::/:`..`-o:`--/.`.::.....`````....../-`.+o+yNmmmddhysyyssssshddhhhhhhhhdmdddmhyhhysyysosysshshmdhyyhhddhsooo.`..-``--:-./:````...``````````````````````.......`\n");
    printf("............-://...`.o:..-:.`.:-.....```.....`..:-`./o+smmmmmdhysssssooshdhyyssydmNNNd+./.`.-``.-` `.``.`oNNmdyyyhhs++oo``-..``--:-./:````...```````````````......`......``\n");
    printf(".........-..-://.....+:..-:.`.::.....`````...`..::`.+o+omNNNmmhhyyyso++oyyyyhhdNMMNNdh+.:-``.```.  `.`-:/hNMNdhysso+/+so` --.``----`/:````...```````````````...........````\n");
    printf(".........--.-://.....+:..-:-`.::.`......`.......::`-so+omNNNNmdddhyyo+++ssosssymMNNmdmmddddhhsssyssydhdmmNMNdoo+++///oho`.--.``:-:-./:````..`````````````````````......````\n");
    printf(".........----://.....+/..-:-..::-.......`.......::`-oo+omNNNNNmmdhhyso+/++/+++oymdhhdhddhhhddmmmmmmddddmhsymho+/////+yd+`.--.``:-:-./:````..`````````````````````......````\n");
    printf(".........----:+/--...+/.-:::..:--.....`........./:`-ooo+mMMNNNmdddhhhs+//+////ooo:.--:/oo///:/+/++//:/:-.-ohsoo///:/ohm/``...``--:-./:````..````````````......``........```\n");
    printf("..........---+s/-....+/.--/:../::...............::`-soo+mMMMMNNmmddddhs+////://oo//-`` `` `.``.`..`.`.```:ys+++//://ymm:``..-``-:--.//````..``````````........``...........\n");
    printf(".........----/so-....+/.-://..//:...............::`:o+++mMMMMMNNmmdmmmdys///////+ooo+:-:-`.:..:-::-:-:-:+++//+///:/odNm+``..-``:-::.//````..`````````.........``...........\n");
    printf(".........----:so-....++.-://..//:...............:/./o+osNMMMMMMMNNmmmmddyo+/++///+oso+++//::::::::::::///+++++////+yNNN+``..-.`--::.+/````..``````````........`............\n");
    printf("...........--:o+:..../+.--:/..//:...............-/./ooodNMMMMMMMMNNmmmmmdhs++/++//+oooooo+//:-://////++++oo++//++osdNNN/``.--``--/:.+/````..`````````````.....`............\n");
    printf("...........--:+o:.-../+---:/..//:...............-/.+o+odNMMMMMMMMMMNNNNmmdho+/++///++ossssssooo+++++ossssoo////+oydNNNN:``.-:.`-:/:.++````..````````````...................\n");
    printf("...........--:+o/.-..:+---:/.`/::..............--:-o++yhNMMMMMMMMMMMMNNNNmdhys++//::/+oooooosssssssssso++/////++shmNMNN:``---.`-:/:-++```...``````.``......................\n");
    printf("...........--:++/....:+-.-:/..:::..............--:-o/+ssNMMMMMMMMMMMMMMMMNNNmhss++/::////+/+++ooosooo++/////:/+sydNMMNy-``.:-.`::/:-++```...``````.````....................\n");
    printf(".--....---.--:/+/.-..:o-.--/.`:/:..............----:+osyNMMMMMMMMMMMMMMMMMMNNmdysso+//://:::/::///++/://///+//oymNNMMh/.``.:-.`::+/.+/```...```````````..`.................\n");
    printf(".-.....---.---/+/....-o-.--/.`:/:...............-../osodMMMMMMMMMMMMMMMMMMMMMNNmdhyys+////:::::::///:///////+ohdNMMMNs:.``.:-.`::+:-+/```...```````````..``................\n");
    printf(".--....---.---:+/....-o-..-:.`:+:......```......--.+osyNMMMMMMMMMMMMMMMMMMMMMMMNNmhhdysoo+//++++++////++++++oydNMMMMNo.```.:-.`::/:-+/```....``````````..``..............``\n");
    printf(".-----...---:::+/....-o-.--:.`:/:......``.......-:.o+shMMMMMMMMMMMMMMMMMMMMMMMMMMMNmNmmhhysoosysssssso+oosyhdNNMMMMMNs.```.:-.`::/:.++`````..`````````....................`\n");
    printf("...---...---::/o+....-o-.--:.`:/:......``.......-/-ssssNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNmmmdhhhhdddddhhhhdmNMMMMMMMMN+.```.:-.`::/:.//```....````````.....................`\n");
    printf("....--...----::o+-....+-..-:.`-::-.....``.......--:ooooMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNmmmmNNNNNNNNNNMMMMMMMMMNs..``.::.`::/:.::.``....``````.......................`\n");
    printf("...--.-------::oo:.-..+:.--:..-::...............::/ssosMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN+-```::.`::/:./:.`.....```.``.......................`\n");
    printf("...---.-----::+oo:.-..+:.--:-.-/:-..............--/osooMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMmo.`.::.`/:::.+/.``..-.```..........................`\n");
    printf("...---...---::/oo:.-..+/-----..+:-..............--:os++MMMMMMMMMMMMMMNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMmo:..::.`/:::.++..``.-...`...........................\n");
    printf("...----------:+oo:.-..+/--::-../:-..............-//oo/+MMMMMMMMMMMMMMNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN+`-.-::.`:://-/+..``.-.`.............................\n");
    printf(".-.---------:::so/.-..++---/:..+:-..............-/++o//MMMMMMMMMMMMMMMNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd.```-/:..////-++..`..-...............................\n");
    printf(".-----------:::so/.-..+o--://..+:-..............-::++:/MMMMMMMMMMMMMMMMNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd.```./:-.///:-+o.....-...............................\n");
    printf("------------+:/s+/---./o--://../:-.............---/s/:+MMMMMMMMMMMMMNNNNMMNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMm.```-::-.:+/:-+o.....:-..............................\n");
    printf("-----------:::/oo+---./s:-:/+-./::..............--/o::oMMMMMMMMMMMMMMMMNNNNNNmmdmNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd.``.-//-.:++:-+o.....:-..............................\n");
    printf("------------:+/+o+---./s:--/+-.+::..............--:/::oNMMMMMMMMMMMMMMMNNNNNNNmmmmNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd.``..//-.://:.+o.....--..............................\n");
    printf("-----------://:/so---./s/--/+-.+//.............--./+:/+mMMMMMMMMMMMMMMMmNmNNNNmmmmmNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMy```..//-.://:.+o..`..--............................``\n");
    printf("-----------:////so---./y+--:/-.///..............--/+:/+mMMMMMMMMMMMMMMMNMNNNNNNNmNNmmmmmNNNMMMMMMMMMMMMMMMMMMMMMMMMNm+```..//..:///-+o..`..--.............................`\n");
    printf("--------:----//+yo---.:y+--:/-.//:..............-./+://dMMMMMMMMMMMMMMMMMMMMNNNNmNNmdddddmmmNNNNNNMMMMMMMMMNmMMMMMMNy-``...//..:/+:-+o.``..--..............................\n");
    printf("-------:::---//+ys::--:y+--:/-.///..............-./+//-hMMMMMMMMMMMMMMMMMMNMMNmNNmmmmmhhhdmmmmNNNNMMMMMMMNNmmMMMMMMM/```..-/:..:++:-+s.``..--`.............................\n");
    printf("\n");
}
