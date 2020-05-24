// Benchmark "c880" written by ABC on Sun May 24 21:38:44 2020

module c880 ( 
    G1gat, G8gat, G13gat, G17gat, G26gat, G29gat, G36gat, G42gat, G51gat,
    G55gat, G59gat, G68gat, G72gat, G73gat, G74gat, G75gat, G80gat, G85gat,
    G86gat, G87gat, G88gat, G89gat, G90gat, G91gat, G96gat, G101gat,
    G106gat, G111gat, G116gat, G121gat, G126gat, G130gat, G135gat, G138gat,
    G143gat, G146gat, G149gat, G152gat, G153gat, G156gat, G159gat, G165gat,
    G171gat, G177gat, G183gat, G189gat, G195gat, G201gat, G207gat, G210gat,
    G219gat, G228gat, G237gat, G246gat, G255gat, G259gat, G260gat, G261gat,
    G267gat, G268gat,
    G388gat, G389gat, G390gat, G391gat, G418gat, G419gat, G420gat, G421gat,
    G422gat, G423gat, G446gat, G447gat, G448gat, G449gat, G450gat, G767gat,
    G768gat, G850gat, G863gat, G864gat, G865gat, G866gat, G874gat, G878gat,
    G879gat, G880gat  );
  input  G1gat, G8gat, G13gat, G17gat, G26gat, G29gat, G36gat, G42gat,
    G51gat, G55gat, G59gat, G68gat, G72gat, G73gat, G74gat, G75gat, G80gat,
    G85gat, G86gat, G87gat, G88gat, G89gat, G90gat, G91gat, G96gat,
    G101gat, G106gat, G111gat, G116gat, G121gat, G126gat, G130gat, G135gat,
    G138gat, G143gat, G146gat, G149gat, G152gat, G153gat, G156gat, G159gat,
    G165gat, G171gat, G177gat, G183gat, G189gat, G195gat, G201gat, G207gat,
    G210gat, G219gat, G228gat, G237gat, G246gat, G255gat, G259gat, G260gat,
    G261gat, G267gat, G268gat;
  output G388gat, G389gat, G390gat, G391gat, G418gat, G419gat, G420gat,
    G421gat, G422gat, G423gat, G446gat, G447gat, G448gat, G449gat, G450gat,
    G767gat, G768gat, G850gat, G863gat, G864gat, G865gat, G866gat, G874gat,
    G878gat, G879gat, G880gat;
  wire n86, n88, n92, n93, n95, n96, n97, n98, n99, n101, n102, n103, n105,
    n106, n107, n109, n111, n113, n115, n117, n118, n119, n121, n122, n125,
    n126, n127, n128, n129, n130, n131, n132, n134, n135, n136, n137, n138,
    n139, n140, n141, n143, n144, n145, n146, n147, n148, n149, n150, n151,
    n152, n153, n154, n155, n156, n157, n158, n159, n160, n161, n162, n163,
    n164, n165, n166, n167, n168, n169, n170, n171, n172, n173, n174, n175,
    n176, n177, n178, n179, n180, n181, n182, n183, n184, n185, n186, n187,
    n188, n190, n191, n192, n193, n194, n195, n196, n197, n198, n199, n200,
    n201, n202, n203, n204, n205, n206, n207, n208, n209, n210, n211, n212,
    n213, n214, n215, n216, n217, n218, n219, n220, n221, n222, n223, n224,
    n225, n226, n227, n228, n229, n230, n231, n232, n233, n234, n235, n236,
    n237, n238, n239, n240, n241, n242, n243, n244, n245, n246, n247, n248,
    n249, n250, n252, n253, n254, n255, n256, n257, n258, n259, n260, n261,
    n262, n263, n264, n265, n266, n267, n268, n269, n270, n271, n273, n274,
    n275, n276, n277, n278, n279, n280, n281, n282, n283, n284, n285, n286,
    n287, n288, n289, n291, n292, n293, n294, n295, n296, n297, n298, n299,
    n300, n301, n302, n303, n304, n305, n306, n307, n308, n309, n310, n311,
    n312, n313, n314, n315, n316, n317, n318, n319, n320, n321, n322, n323,
    n324, n325, n326, n327, n328, n329, n330, n331, n332, n333, n334, n335,
    n336, n337, n338, n339, n340, n341, n343, n344, n345, n346, n347, n348,
    n349, n350, n351, n352, n353, n354, n355, n356, n357, n358, n359, n360,
    n361, n363, n364, n365, n366, n367, n368, n369, n370, n371, n372, n373,
    n374, n375, n376, n377, n378, n379, n380, n381, n383, n384, n385, n386,
    n387, n388, n389, n390, n391, n392, n393, n394, n395, n396, n397, n398,
    n399, n400, n401, n402, n403, n405, n406, n407, n408, n409, n410, n411,
    n412, n413, n414, n415, n416, n417, n418, n419, n420, n421, n422, n423,
    n424, n425;
  jand g000(.dina(G75gat), .dinb(G29gat), .dout(n86));
  jand g001(.dina(n86), .dinb(G42gat), .dout(G388gat));
  jand g002(.dina(G36gat), .dinb(G29gat), .dout(n88));
  jand g003(.dina(n88), .dinb(G80gat), .dout(G389gat));
  jand g004(.dina(n88), .dinb(G42gat), .dout(G390gat));
  jand g005(.dina(G86gat), .dinb(G85gat), .dout(G391gat));
  jand g006(.dina(G8gat), .dinb(G1gat), .dout(n92));
  jand g007(.dina(G17gat), .dinb(G13gat), .dout(n93));
  jand g008(.dina(n93), .dinb(n92), .dout(G418gat));
  jnot g009(.din(n93), .dout(n95));
  jnot g010(.din(G1gat), .dout(n96));
  jnot g011(.din(G26gat), .dout(n97));
  jor  g012(.dina(n97), .dinb(n96), .dout(n98));
  jor  g013(.dina(n98), .dinb(n95), .dout(n99));
  jor  g014(.dina(n99), .dinb(G390gat), .dout(G419gat));
  jnot g015(.din(G80gat), .dout(n101));
  jand g016(.dina(G75gat), .dinb(G59gat), .dout(n102));
  jnot g017(.din(n102), .dout(n103));
  jor  g018(.dina(n103), .dinb(n101), .dout(G420gat));
  jnot g019(.din(G36gat), .dout(n105));
  jnot g020(.din(G59gat), .dout(n106));
  jor  g021(.dina(n106), .dinb(n105), .dout(n107));
  jor  g022(.dina(n107), .dinb(n101), .dout(G421gat));
  jnot g023(.din(G42gat), .dout(n109));
  jor  g024(.dina(n107), .dinb(n109), .dout(G422gat));
  jor  g025(.dina(G88gat), .dinb(G87gat), .dout(n111));
  jand g026(.dina(n111), .dinb(G90gat), .dout(G423gat));
  jnot g027(.din(G390gat), .dout(n113));
  jor  g028(.dina(n99), .dinb(n113), .dout(G446gat));
  jand g029(.dina(G26gat), .dinb(G1gat), .dout(n115));
  jand g030(.dina(n115), .dinb(G51gat), .dout(G447gat));
  jand g031(.dina(G55gat), .dinb(G13gat), .dout(n117));
  jand g032(.dina(n117), .dinb(n92), .dout(n118));
  jand g033(.dina(G68gat), .dinb(G29gat), .dout(n119));
  jand g034(.dina(n119), .dinb(n118), .dout(G448gat));
  jand g035(.dina(G68gat), .dinb(G59gat), .dout(n121));
  jand g036(.dina(n121), .dinb(G74gat), .dout(n122));
  jand g037(.dina(n122), .dinb(n118), .dout(G449gat));
  jand g038(.dina(n111), .dinb(G89gat), .dout(G450gat));
  jxor g039(.dina(G96gat), .dinb(G91gat), .dout(n125));
  jxor g040(.dina(n125), .dinb(G130gat), .dout(n126));
  jxor g041(.dina(G126gat), .dinb(G121gat), .dout(n127));
  jxor g042(.dina(n127), .dinb(n126), .dout(n128));
  jxor g043(.dina(G116gat), .dinb(G111gat), .dout(n129));
  jxor g044(.dina(n129), .dinb(G135gat), .dout(n130));
  jxor g045(.dina(G106gat), .dinb(G101gat), .dout(n131));
  jxor g046(.dina(n131), .dinb(n130), .dout(n132));
  jxor g047(.dina(n132), .dinb(n128), .dout(G767gat));
  jxor g048(.dina(G165gat), .dinb(G159gat), .dout(n134));
  jxor g049(.dina(n134), .dinb(G130gat), .dout(n135));
  jxor g050(.dina(G201gat), .dinb(G195gat), .dout(n136));
  jxor g051(.dina(n136), .dinb(n135), .dout(n137));
  jxor g052(.dina(G189gat), .dinb(G183gat), .dout(n138));
  jxor g053(.dina(n138), .dinb(G207gat), .dout(n139));
  jxor g054(.dina(G177gat), .dinb(G171gat), .dout(n140));
  jxor g055(.dina(n140), .dinb(n139), .dout(n141));
  jxor g056(.dina(n141), .dinb(n137), .dout(G768gat));
  jnot g057(.din(G261gat), .dout(n143));
  jand g058(.dina(n102), .dinb(G42gat), .dout(n144));
  jnot g059(.din(n144), .dout(n145));
  jand g060(.dina(G51gat), .dinb(G17gat), .dout(n146));
  jand g061(.dina(n146), .dinb(n92), .dout(n147));
  jand g062(.dina(n147), .dinb(n145), .dout(n148));
  jand g063(.dina(G156gat), .dinb(G59gat), .dout(n149));
  jxor g064(.dina(G42gat), .dinb(G17gat), .dout(n150));
  jand g065(.dina(n150), .dinb(n149), .dout(n151));
  jand g066(.dina(n151), .dinb(G447gat), .dout(n152));
  jor  g067(.dina(n152), .dinb(n148), .dout(n153));
  jand g068(.dina(n153), .dinb(G126gat), .dout(n154));
  jnot g069(.din(G156gat), .dout(n155));
  jor  g070(.dina(n155), .dinb(n106), .dout(n156));
  jand g071(.dina(n156), .dinb(G447gat), .dout(n157));
  jand g072(.dina(n157), .dinb(G17gat), .dout(n158));
  jor  g073(.dina(n158), .dinb(n96), .dout(n159));
  jand g074(.dina(n159), .dinb(G153gat), .dout(n160));
  jand g075(.dina(n86), .dinb(G80gat), .dout(n161));
  jand g076(.dina(n161), .dinb(G447gat), .dout(n162));
  jnot g077(.din(G268gat), .dout(n163));
  jand g078(.dina(n163), .dinb(G55gat), .dout(n164));
  jand g079(.dina(n164), .dinb(n162), .dout(n165));
  jor  g080(.dina(n165), .dinb(n160), .dout(n166));
  jor  g081(.dina(n166), .dinb(n154), .dout(n167));
  jxor g082(.dina(n167), .dinb(G201gat), .dout(n168));
  jnot g083(.din(n168), .dout(n169));
  jor  g084(.dina(n169), .dinb(n143), .dout(n170));
  jor  g085(.dina(n168), .dinb(G261gat), .dout(n171));
  jand g086(.dina(n171), .dinb(G219gat), .dout(n172));
  jand g087(.dina(n172), .dinb(n170), .dout(n173));
  jand g088(.dina(n168), .dinb(G228gat), .dout(n174));
  jand g089(.dina(G237gat), .dinb(G201gat), .dout(n175));
  jor  g090(.dina(n175), .dinb(G246gat), .dout(n176));
  jand g091(.dina(n176), .dinb(n167), .dout(n177));
  jand g092(.dina(G72gat), .dinb(G42gat), .dout(n178));
  jand g093(.dina(n178), .dinb(G73gat), .dout(n179));
  jand g094(.dina(n179), .dinb(n121), .dout(n180));
  jand g095(.dina(n180), .dinb(n118), .dout(n181));
  jand g096(.dina(n181), .dinb(G201gat), .dout(n182));
  jand g097(.dina(G210gat), .dinb(G121gat), .dout(n183));
  jand g098(.dina(G267gat), .dinb(G255gat), .dout(n184));
  jor  g099(.dina(n184), .dinb(n183), .dout(n185));
  jor  g100(.dina(n185), .dinb(n182), .dout(n186));
  jor  g101(.dina(n186), .dinb(n177), .dout(n187));
  jor  g102(.dina(n187), .dinb(n174), .dout(n188));
  jor  g103(.dina(n188), .dinb(n173), .dout(G850gat));
  jand g104(.dina(n159), .dinb(G143gat), .dout(n190));
  jand g105(.dina(n153), .dinb(G111gat), .dout(n191));
  jor  g106(.dina(n191), .dinb(n165), .dout(n192));
  jor  g107(.dina(n192), .dinb(n190), .dout(n193));
  jxor g108(.dina(n193), .dinb(G183gat), .dout(n194));
  jnot g109(.din(n194), .dout(n195));
  jand g110(.dina(n167), .dinb(G201gat), .dout(n196));
  jnot g111(.din(n196), .dout(n197));
  jnot g112(.din(G201gat), .dout(n198));
  jnot g113(.din(n154), .dout(n199));
  jnot g114(.din(G153gat), .dout(n200));
  jnot g115(.din(G17gat), .dout(n201));
  jnot g116(.din(G51gat), .dout(n202));
  jor  g117(.dina(n98), .dinb(n202), .dout(n203));
  jor  g118(.dina(n149), .dinb(n203), .dout(n204));
  jor  g119(.dina(n204), .dinb(n201), .dout(n205));
  jand g120(.dina(n205), .dinb(G1gat), .dout(n206));
  jor  g121(.dina(n206), .dinb(n200), .dout(n207));
  jnot g122(.din(n165), .dout(n208));
  jand g123(.dina(n208), .dinb(n207), .dout(n209));
  jand g124(.dina(n209), .dinb(n199), .dout(n210));
  jand g125(.dina(n210), .dinb(n198), .dout(n211));
  jor  g126(.dina(n211), .dinb(n143), .dout(n212));
  jand g127(.dina(n212), .dinb(n197), .dout(n213));
  jand g128(.dina(n159), .dinb(G146gat), .dout(n214));
  jand g129(.dina(n153), .dinb(G116gat), .dout(n215));
  jor  g130(.dina(n215), .dinb(n165), .dout(n216));
  jor  g131(.dina(n216), .dinb(n214), .dout(n217));
  jor  g132(.dina(n217), .dinb(G189gat), .dout(n218));
  jand g133(.dina(n159), .dinb(G149gat), .dout(n219));
  jand g134(.dina(n153), .dinb(G121gat), .dout(n220));
  jor  g135(.dina(n220), .dinb(n165), .dout(n221));
  jor  g136(.dina(n221), .dinb(n219), .dout(n222));
  jor  g137(.dina(n222), .dinb(G195gat), .dout(n223));
  jand g138(.dina(n223), .dinb(n218), .dout(n224));
  jnot g139(.din(n224), .dout(n225));
  jor  g140(.dina(n225), .dinb(n213), .dout(n226));
  jand g141(.dina(n217), .dinb(G189gat), .dout(n227));
  jand g142(.dina(n222), .dinb(G195gat), .dout(n228));
  jand g143(.dina(n228), .dinb(n218), .dout(n229));
  jor  g144(.dina(n229), .dinb(n227), .dout(n230));
  jnot g145(.din(n230), .dout(n231));
  jand g146(.dina(n231), .dinb(n226), .dout(n232));
  jor  g147(.dina(n232), .dinb(n195), .dout(n233));
  jor  g148(.dina(n167), .dinb(G201gat), .dout(n234));
  jand g149(.dina(n234), .dinb(G261gat), .dout(n235));
  jor  g150(.dina(n235), .dinb(n196), .dout(n236));
  jand g151(.dina(n224), .dinb(n236), .dout(n237));
  jor  g152(.dina(n230), .dinb(n237), .dout(n238));
  jor  g153(.dina(n238), .dinb(n194), .dout(n239));
  jand g154(.dina(n239), .dinb(G219gat), .dout(n240));
  jand g155(.dina(n240), .dinb(n233), .dout(n241));
  jand g156(.dina(n194), .dinb(G228gat), .dout(n242));
  jand g157(.dina(G237gat), .dinb(G183gat), .dout(n243));
  jor  g158(.dina(n243), .dinb(G246gat), .dout(n244));
  jand g159(.dina(n244), .dinb(n193), .dout(n245));
  jand g160(.dina(n181), .dinb(G183gat), .dout(n246));
  jand g161(.dina(G210gat), .dinb(G106gat), .dout(n247));
  jor  g162(.dina(n247), .dinb(n246), .dout(n248));
  jor  g163(.dina(n248), .dinb(n245), .dout(n249));
  jor  g164(.dina(n249), .dinb(n242), .dout(n250));
  jor  g165(.dina(n250), .dinb(n241), .dout(G863gat));
  jxor g166(.dina(n217), .dinb(G189gat), .dout(n252));
  jnot g167(.din(n252), .dout(n253));
  jand g168(.dina(n223), .dinb(n236), .dout(n254));
  jor  g169(.dina(n254), .dinb(n228), .dout(n255));
  jnot g170(.din(n255), .dout(n256));
  jor  g171(.dina(n256), .dinb(n253), .dout(n257));
  jor  g172(.dina(n255), .dinb(n252), .dout(n258));
  jand g173(.dina(n258), .dinb(G219gat), .dout(n259));
  jand g174(.dina(n259), .dinb(n257), .dout(n260));
  jand g175(.dina(n252), .dinb(G228gat), .dout(n261));
  jand g176(.dina(G237gat), .dinb(G189gat), .dout(n262));
  jor  g177(.dina(n262), .dinb(G246gat), .dout(n263));
  jand g178(.dina(n263), .dinb(n217), .dout(n264));
  jand g179(.dina(n181), .dinb(G189gat), .dout(n265));
  jand g180(.dina(G210gat), .dinb(G111gat), .dout(n266));
  jand g181(.dina(G259gat), .dinb(G255gat), .dout(n267));
  jor  g182(.dina(n267), .dinb(n266), .dout(n268));
  jor  g183(.dina(n268), .dinb(n265), .dout(n269));
  jor  g184(.dina(n269), .dinb(n264), .dout(n270));
  jor  g185(.dina(n270), .dinb(n261), .dout(n271));
  jor  g186(.dina(n271), .dinb(n260), .dout(G864gat));
  jxor g187(.dina(n222), .dinb(G195gat), .dout(n273));
  jnot g188(.din(n273), .dout(n274));
  jor  g189(.dina(n274), .dinb(n213), .dout(n275));
  jor  g190(.dina(n273), .dinb(n236), .dout(n276));
  jand g191(.dina(n276), .dinb(G219gat), .dout(n277));
  jand g192(.dina(n277), .dinb(n275), .dout(n278));
  jand g193(.dina(n273), .dinb(G228gat), .dout(n279));
  jand g194(.dina(G237gat), .dinb(G195gat), .dout(n280));
  jor  g195(.dina(n280), .dinb(G246gat), .dout(n281));
  jand g196(.dina(n281), .dinb(n222), .dout(n282));
  jand g197(.dina(n181), .dinb(G195gat), .dout(n283));
  jand g198(.dina(G210gat), .dinb(G116gat), .dout(n284));
  jand g199(.dina(G260gat), .dinb(G255gat), .dout(n285));
  jor  g200(.dina(n285), .dinb(n284), .dout(n286));
  jor  g201(.dina(n286), .dinb(n283), .dout(n287));
  jor  g202(.dina(n287), .dinb(n282), .dout(n288));
  jor  g203(.dina(n288), .dinb(n279), .dout(n289));
  jor  g204(.dina(n289), .dinb(n278), .dout(G865gat));
  jand g205(.dina(n153), .dinb(G91gat), .dout(n291));
  jand g206(.dina(n157), .dinb(G55gat), .dout(n292));
  jand g207(.dina(n292), .dinb(G143gat), .dout(n293));
  jand g208(.dina(G138gat), .dinb(G8gat), .dout(n294));
  jand g209(.dina(n163), .dinb(G17gat), .dout(n295));
  jand g210(.dina(n295), .dinb(n162), .dout(n296));
  jor  g211(.dina(n296), .dinb(n294), .dout(n297));
  jor  g212(.dina(n297), .dinb(n293), .dout(n298));
  jor  g213(.dina(n298), .dinb(n291), .dout(n299));
  jand g214(.dina(n299), .dinb(G159gat), .dout(n300));
  jor  g215(.dina(n299), .dinb(G159gat), .dout(n301));
  jand g216(.dina(n193), .dinb(G183gat), .dout(n302));
  jor  g217(.dina(n193), .dinb(G183gat), .dout(n303));
  jand g218(.dina(n238), .dinb(n303), .dout(n304));
  jor  g219(.dina(n304), .dinb(n302), .dout(n305));
  jnot g220(.din(G165gat), .dout(n306));
  jand g221(.dina(n153), .dinb(G96gat), .dout(n307));
  jand g222(.dina(n292), .dinb(G146gat), .dout(n308));
  jand g223(.dina(G138gat), .dinb(G51gat), .dout(n309));
  jor  g224(.dina(n309), .dinb(n296), .dout(n310));
  jor  g225(.dina(n310), .dinb(n308), .dout(n311));
  jor  g226(.dina(n311), .dinb(n307), .dout(n312));
  jnot g227(.din(n312), .dout(n313));
  jand g228(.dina(n313), .dinb(n306), .dout(n314));
  jnot g229(.din(n314), .dout(n315));
  jand g230(.dina(n153), .dinb(G101gat), .dout(n316));
  jand g231(.dina(n292), .dinb(G149gat), .dout(n317));
  jand g232(.dina(G138gat), .dinb(G17gat), .dout(n318));
  jor  g233(.dina(n318), .dinb(n296), .dout(n319));
  jor  g234(.dina(n319), .dinb(n317), .dout(n320));
  jor  g235(.dina(n320), .dinb(n316), .dout(n321));
  jor  g236(.dina(n321), .dinb(G171gat), .dout(n322));
  jand g237(.dina(n153), .dinb(G106gat), .dout(n323));
  jand g238(.dina(n292), .dinb(G153gat), .dout(n324));
  jand g239(.dina(G152gat), .dinb(G138gat), .dout(n325));
  jor  g240(.dina(n325), .dinb(n296), .dout(n326));
  jor  g241(.dina(n326), .dinb(n324), .dout(n327));
  jor  g242(.dina(n327), .dinb(n323), .dout(n328));
  jor  g243(.dina(n328), .dinb(G177gat), .dout(n329));
  jand g244(.dina(n329), .dinb(n322), .dout(n330));
  jand g245(.dina(n330), .dinb(n315), .dout(n331));
  jand g246(.dina(n331), .dinb(n305), .dout(n332));
  jand g247(.dina(n312), .dinb(G165gat), .dout(n333));
  jand g248(.dina(n321), .dinb(G171gat), .dout(n334));
  jand g249(.dina(n328), .dinb(G177gat), .dout(n335));
  jand g250(.dina(n335), .dinb(n322), .dout(n336));
  jor  g251(.dina(n336), .dinb(n334), .dout(n337));
  jand g252(.dina(n337), .dinb(n315), .dout(n338));
  jor  g253(.dina(n338), .dinb(n333), .dout(n339));
  jor  g254(.dina(n339), .dinb(n332), .dout(n340));
  jand g255(.dina(n340), .dinb(n301), .dout(n341));
  jor  g256(.dina(n341), .dinb(n300), .dout(G866gat));
  jnot g257(.din(n302), .dout(n343));
  jnot g258(.din(n303), .dout(n344));
  jor  g259(.dina(n232), .dinb(n344), .dout(n345));
  jand g260(.dina(n345), .dinb(n343), .dout(n346));
  jxor g261(.dina(n328), .dinb(G177gat), .dout(n347));
  jnot g262(.din(n347), .dout(n348));
  jor  g263(.dina(n348), .dinb(n346), .dout(n349));
  jor  g264(.dina(n347), .dinb(n305), .dout(n350));
  jand g265(.dina(n350), .dinb(G219gat), .dout(n351));
  jand g266(.dina(n351), .dinb(n349), .dout(n352));
  jand g267(.dina(n347), .dinb(G228gat), .dout(n353));
  jand g268(.dina(G237gat), .dinb(G177gat), .dout(n354));
  jor  g269(.dina(n354), .dinb(G246gat), .dout(n355));
  jand g270(.dina(n355), .dinb(n328), .dout(n356));
  jand g271(.dina(n181), .dinb(G177gat), .dout(n357));
  jand g272(.dina(G210gat), .dinb(G101gat), .dout(n358));
  jor  g273(.dina(n358), .dinb(n357), .dout(n359));
  jor  g274(.dina(n359), .dinb(n356), .dout(n360));
  jor  g275(.dina(n360), .dinb(n353), .dout(n361));
  jor  g276(.dina(n361), .dinb(n352), .dout(G874gat));
  jnot g277(.din(n331), .dout(n363));
  jor  g278(.dina(n363), .dinb(n346), .dout(n364));
  jnot g279(.din(n339), .dout(n365));
  jand g280(.dina(n365), .dinb(n364), .dout(n366));
  jxor g281(.dina(n299), .dinb(G159gat), .dout(n367));
  jnot g282(.din(n367), .dout(n368));
  jor  g283(.dina(n368), .dinb(n366), .dout(n369));
  jor  g284(.dina(n367), .dinb(n340), .dout(n370));
  jand g285(.dina(n370), .dinb(G219gat), .dout(n371));
  jand g286(.dina(n371), .dinb(n369), .dout(n372));
  jand g287(.dina(n367), .dinb(G228gat), .dout(n373));
  jand g288(.dina(G237gat), .dinb(G159gat), .dout(n374));
  jor  g289(.dina(n374), .dinb(G246gat), .dout(n375));
  jand g290(.dina(n375), .dinb(n299), .dout(n376));
  jand g291(.dina(n181), .dinb(G159gat), .dout(n377));
  jand g292(.dina(G268gat), .dinb(G210gat), .dout(n378));
  jor  g293(.dina(n378), .dinb(n377), .dout(n379));
  jor  g294(.dina(n379), .dinb(n376), .dout(n380));
  jor  g295(.dina(n380), .dinb(n373), .dout(n381));
  jor  g296(.dina(n381), .dinb(n372), .dout(G878gat));
  jxor g297(.dina(n312), .dinb(G165gat), .dout(n383));
  jnot g298(.din(n383), .dout(n384));
  jnot g299(.din(n337), .dout(n385));
  jnot g300(.din(n330), .dout(n386));
  jor  g301(.dina(n386), .dinb(n346), .dout(n387));
  jand g302(.dina(n387), .dinb(n385), .dout(n388));
  jor  g303(.dina(n388), .dinb(n384), .dout(n389));
  jand g304(.dina(n330), .dinb(n305), .dout(n390));
  jor  g305(.dina(n390), .dinb(n337), .dout(n391));
  jor  g306(.dina(n391), .dinb(n383), .dout(n392));
  jand g307(.dina(n392), .dinb(G219gat), .dout(n393));
  jand g308(.dina(n393), .dinb(n389), .dout(n394));
  jand g309(.dina(n383), .dinb(G228gat), .dout(n395));
  jand g310(.dina(G237gat), .dinb(G165gat), .dout(n396));
  jor  g311(.dina(n396), .dinb(G246gat), .dout(n397));
  jand g312(.dina(n397), .dinb(n312), .dout(n398));
  jand g313(.dina(n181), .dinb(G165gat), .dout(n399));
  jand g314(.dina(G210gat), .dinb(G91gat), .dout(n400));
  jor  g315(.dina(n400), .dinb(n399), .dout(n401));
  jor  g316(.dina(n401), .dinb(n398), .dout(n402));
  jor  g317(.dina(n402), .dinb(n395), .dout(n403));
  jor  g318(.dina(n403), .dinb(n394), .dout(G879gat));
  jxor g319(.dina(n321), .dinb(G171gat), .dout(n405));
  jnot g320(.din(n405), .dout(n406));
  jnot g321(.din(n335), .dout(n407));
  jnot g322(.din(n329), .dout(n408));
  jor  g323(.dina(n408), .dinb(n346), .dout(n409));
  jand g324(.dina(n409), .dinb(n407), .dout(n410));
  jor  g325(.dina(n410), .dinb(n406), .dout(n411));
  jand g326(.dina(n329), .dinb(n305), .dout(n412));
  jor  g327(.dina(n412), .dinb(n335), .dout(n413));
  jor  g328(.dina(n413), .dinb(n405), .dout(n414));
  jand g329(.dina(n414), .dinb(G219gat), .dout(n415));
  jand g330(.dina(n415), .dinb(n411), .dout(n416));
  jand g331(.dina(n405), .dinb(G228gat), .dout(n417));
  jand g332(.dina(G237gat), .dinb(G171gat), .dout(n418));
  jor  g333(.dina(n418), .dinb(G246gat), .dout(n419));
  jand g334(.dina(n419), .dinb(n321), .dout(n420));
  jand g335(.dina(n181), .dinb(G171gat), .dout(n421));
  jand g336(.dina(G210gat), .dinb(G96gat), .dout(n422));
  jor  g337(.dina(n422), .dinb(n421), .dout(n423));
  jor  g338(.dina(n423), .dinb(n420), .dout(n424));
  jor  g339(.dina(n424), .dinb(n417), .dout(n425));
  jor  g340(.dina(n425), .dinb(n416), .dout(G880gat));
endmodule


