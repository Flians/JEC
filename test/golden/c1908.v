// Benchmark "c1908" written by ABC on Wed May 27 22:04:46 2020

module gf_c1908 ( 
    G101, G104, G107, G110, G113, G116, G119, G122, G125, G128, G131, G134,
    G137, G140, G143, G146, G210, G214, G217, G221, G224, G227, G234, G237,
    G469, G472, G475, G478, G898, G900, G902, G952, G953,
    G3, G6, G9, G12, G30, G45, G48, G15, G18, G21, G24, G27, G33, G36, G39,
    G42, G75, G51, G54, G60, G63, G66, G69, G72, G57  );
  input  G101, G104, G107, G110, G113, G116, G119, G122, G125, G128,
    G131, G134, G137, G140, G143, G146, G210, G214, G217, G221, G224, G227,
    G234, G237, G469, G472, G475, G478, G898, G900, G902, G952, G953;
  output G3, G6, G9, G12, G30, G45, G48, G15, G18, G21, G24, G27, G33, G36,
    G39, G42, G75, G51, G54, G60, G63, G66, G69, G72, G57;
  wire n58, n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71,
    n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85,
    n86, n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99,
    n100, n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111,
    n112, n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123,
    n124, n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135,
    n136, n137, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147,
    n148, n149, n150, n151, n152, n153, n154, n155, n156, n157, n159, n160,
    n161, n162, n163, n164, n165, n166, n168, n169, n170, n171, n173, n174,
    n175, n177, n178, n179, n180, n181, n182, n183, n184, n186, n187, n188,
    n189, n191, n192, n194, n195, n196, n197, n198, n199, n201, n203, n204,
    n206, n207, n208, n210, n211, n213, n214, n215, n216, n217, n218, n220,
    n222, n223, n224, n226, n228, n229, n230, n231, n232, n233, n234, n235,
    n236, n237, n238, n239, n240, n241, n242, n243, n244, n245, n246, n247,
    n248, n249, n250, n251, n252, n253, n254, n255, n256, n257, n258, n259,
    n260, n261, n262, n263, n265, n266, n267, n268, n270, n271, n272, n274,
    n275, n276, n277, n278, n279, n280, n281, n282, n283, n284, n285, n286,
    n287, n288, n289, n290, n291, n292, n293, n294, n295, n296, n297, n298,
    n299, n300, n301, n302, n303, n304, n305, n306, n307, n308, n309, n310,
    n311, n312, n313, n314, n315, n316, n317, n318, n319, n320, n321, n322,
    n323, n324, n325, n326, n327, n328, n329, n330, n331, n332, n333, n334,
    n335, n336, n337, n338, n339, n340, n341, n342, n343, n344, n345, n346,
    n348, n349, n350, n352, n353, n354, n356, n357, n358, n359, n360, n362,
    n363, n364, n365, n366, n367, n369, n370, n371;
  jnot g000(.din(G902), .dout(n58));
  jnot g001(.din(G221), .dout(n59));
  jnot g002(.din(G234), .dout(n60));
  jor  g003(.dina(G953), .dinb(n60), .dout(n61));
  jor  g004(.dina(n61), .dinb(n59), .dout(n62));
  jnot g005(.din(G110), .dout(n63));
  jxor g006(.dina(G119), .dinb(n63), .dout(n64));
  jxor g007(.dina(n64), .dinb(n62), .dout(n65));
  jxor g008(.dina(G140), .dinb(G125), .dout(n66));
  jxor g009(.dina(n66), .dinb(G146), .dout(n67));
  jxor g010(.dina(G137), .dinb(G128), .dout(n68));
  jxor g011(.dina(n68), .dinb(n67), .dout(n69));
  jxor g012(.dina(n69), .dinb(n65), .dout(n70));
  jand g013(.dina(n70), .dinb(n58), .dout(n71));
  jand g014(.dina(n58), .dinb(G234), .dout(n72));
  jnot g015(.din(n72), .dout(n73));
  jand g016(.dina(n73), .dinb(G217), .dout(n74));
  jnot g017(.din(n74), .dout(n75));
  jxor g018(.dina(n75), .dinb(n71), .dout(n76));
  jxor g019(.dina(G143), .dinb(G128), .dout(n77));
  jxor g020(.dina(n77), .dinb(G146), .dout(n78));
  jxor g021(.dina(G137), .dinb(G134), .dout(n79));
  jxor g022(.dina(n79), .dinb(G131), .dout(n80));
  jxor g023(.dina(n80), .dinb(n78), .dout(n81));
  jnot g024(.din(G113), .dout(n82));
  jxor g025(.dina(G119), .dinb(G116), .dout(n83));
  jxor g026(.dina(n83), .dinb(n82), .dout(n84));
  jnot g027(.din(G210), .dout(n85));
  jor  g028(.dina(G953), .dinb(G237), .dout(n86));
  jor  g029(.dina(n86), .dinb(n85), .dout(n87));
  jxor g030(.dina(n87), .dinb(G101), .dout(n88));
  jxor g031(.dina(n88), .dinb(n84), .dout(n89));
  jxor g032(.dina(n89), .dinb(n81), .dout(n90));
  jand g033(.dina(n90), .dinb(n58), .dout(n91));
  jxor g034(.dina(n91), .dinb(G472), .dout(n92));
  jand g035(.dina(n92), .dinb(n76), .dout(n93));
  jor  g036(.dina(G902), .dinb(G237), .dout(n94));
  jand g037(.dina(n94), .dinb(G214), .dout(n95));
  jnot g038(.din(n95), .dout(n96));
  jnot g039(.din(G101), .dout(n97));
  jxor g040(.dina(G107), .dinb(G104), .dout(n98));
  jxor g041(.dina(n98), .dinb(n97), .dout(n99));
  jxor g042(.dina(n99), .dinb(n84), .dout(n100));
  jxor g043(.dina(G122), .dinb(G110), .dout(n101));
  jxor g044(.dina(n101), .dinb(n100), .dout(n102));
  jnot g045(.din(G953), .dout(n103));
  jand g046(.dina(n103), .dinb(G224), .dout(n104));
  jxor g047(.dina(n78), .dinb(G125), .dout(n105));
  jxor g048(.dina(n105), .dinb(n104), .dout(n106));
  jxor g049(.dina(n106), .dinb(n102), .dout(n107));
  jand g050(.dina(n107), .dinb(n58), .dout(n108));
  jand g051(.dina(n94), .dinb(G210), .dout(n109));
  jxor g052(.dina(n109), .dinb(n108), .dout(n110));
  jand g053(.dina(n110), .dinb(n96), .dout(n111));
  jand g054(.dina(n73), .dinb(G221), .dout(n112));
  jnot g055(.din(n112), .dout(n113));
  jand g056(.dina(n103), .dinb(G227), .dout(n114));
  jxor g057(.dina(G140), .dinb(n63), .dout(n115));
  jxor g058(.dina(n115), .dinb(n114), .dout(n116));
  jxor g059(.dina(n116), .dinb(n99), .dout(n117));
  jxor g060(.dina(n117), .dinb(n81), .dout(n118));
  jand g061(.dina(n118), .dinb(n58), .dout(n119));
  jxor g062(.dina(n119), .dinb(G469), .dout(n120));
  jand g063(.dina(n120), .dinb(n113), .dout(n121));
  jand g064(.dina(n121), .dinb(n111), .dout(n122));
  jor  g065(.dina(n103), .dinb(G898), .dout(n123));
  jnot g066(.din(n123), .dout(n124));
  jand g067(.dina(G237), .dinb(G234), .dout(n125));
  jnot g068(.din(n125), .dout(n126));
  jand g069(.dina(n126), .dinb(G902), .dout(n127));
  jand g070(.dina(n127), .dinb(n124), .dout(n128));
  jand g071(.dina(n126), .dinb(G952), .dout(n129));
  jand g072(.dina(n129), .dinb(n103), .dout(n130));
  jor  g073(.dina(n130), .dinb(n128), .dout(n131));
  jnot g074(.din(G478), .dout(n132));
  jxor g075(.dina(n77), .dinb(G134), .dout(n133));
  jand g076(.dina(n103), .dinb(G234), .dout(n134));
  jand g077(.dina(n134), .dinb(G217), .dout(n135));
  jxor g078(.dina(G122), .dinb(G116), .dout(n136));
  jxor g079(.dina(n136), .dinb(G107), .dout(n137));
  jxor g080(.dina(n137), .dinb(n135), .dout(n138));
  jxor g081(.dina(n138), .dinb(n133), .dout(n139));
  jand g082(.dina(n139), .dinb(n58), .dout(n140));
  jxor g083(.dina(n140), .dinb(n132), .dout(n141));
  jnot g084(.din(G475), .dout(n142));
  jxor g085(.dina(G122), .dinb(G113), .dout(n143));
  jxor g086(.dina(n143), .dinb(G104), .dout(n144));
  jnot g087(.din(G214), .dout(n145));
  jor  g088(.dina(n86), .dinb(n145), .dout(n146));
  jnot g089(.din(G131), .dout(n147));
  jxor g090(.dina(G143), .dinb(n147), .dout(n148));
  jxor g091(.dina(n148), .dinb(n146), .dout(n149));
  jxor g092(.dina(n149), .dinb(n67), .dout(n150));
  jxor g093(.dina(n150), .dinb(n144), .dout(n151));
  jand g094(.dina(n151), .dinb(n58), .dout(n152));
  jxor g095(.dina(n152), .dinb(n142), .dout(n153));
  jand g096(.dina(n153), .dinb(n141), .dout(n154));
  jand g097(.dina(n154), .dinb(n131), .dout(n155));
  jand g098(.dina(n155), .dinb(n122), .dout(n156));
  jand g099(.dina(n156), .dinb(n93), .dout(n157));
  jxor g100(.dina(n157), .dinb(G101), .dout(G3));
  jnot g101(.din(G472), .dout(n159));
  jxor g102(.dina(n91), .dinb(n159), .dout(n160));
  jand g103(.dina(n160), .dinb(n76), .dout(n161));
  jand g104(.dina(n161), .dinb(n122), .dout(n162));
  jxor g105(.dina(n152), .dinb(G475), .dout(n163));
  jand g106(.dina(n163), .dinb(n141), .dout(n164));
  jand g107(.dina(n164), .dinb(n131), .dout(n165));
  jand g108(.dina(n165), .dinb(n162), .dout(n166));
  jxor g109(.dina(n166), .dinb(G104), .dout(G6));
  jxor g110(.dina(n140), .dinb(G478), .dout(n168));
  jand g111(.dina(n153), .dinb(n168), .dout(n169));
  jand g112(.dina(n169), .dinb(n131), .dout(n170));
  jand g113(.dina(n170), .dinb(n162), .dout(n171));
  jxor g114(.dina(n171), .dinb(G107), .dout(G9));
  jxor g115(.dina(n74), .dinb(n71), .dout(n173));
  jand g116(.dina(n160), .dinb(n173), .dout(n174));
  jand g117(.dina(n174), .dinb(n156), .dout(n175));
  jxor g118(.dina(n175), .dinb(G110), .dout(G12));
  jand g119(.dina(n92), .dinb(n173), .dout(n177));
  jand g120(.dina(n177), .dinb(n122), .dout(n178));
  jor  g121(.dina(n103), .dinb(G900), .dout(n179));
  jnot g122(.din(n179), .dout(n180));
  jand g123(.dina(n180), .dinb(n127), .dout(n181));
  jor  g124(.dina(n181), .dinb(n130), .dout(n182));
  jand g125(.dina(n182), .dinb(n169), .dout(n183));
  jand g126(.dina(n183), .dinb(n178), .dout(n184));
  jxor g127(.dina(n184), .dinb(G128), .dout(G30));
  jand g128(.dina(n163), .dinb(n168), .dout(n186));
  jand g129(.dina(n186), .dinb(n93), .dout(n187));
  jand g130(.dina(n187), .dinb(n182), .dout(n188));
  jand g131(.dina(n188), .dinb(n122), .dout(n189));
  jxor g132(.dina(n189), .dinb(G143), .dout(G45));
  jand g133(.dina(n182), .dinb(n164), .dout(n191));
  jand g134(.dina(n191), .dinb(n178), .dout(n192));
  jxor g135(.dina(n192), .dinb(G146), .dout(G48));
  jnot g136(.din(G469), .dout(n194));
  jxor g137(.dina(n119), .dinb(n194), .dout(n195));
  jand g138(.dina(n195), .dinb(n113), .dout(n196));
  jand g139(.dina(n196), .dinb(n111), .dout(n197));
  jand g140(.dina(n197), .dinb(n93), .dout(n198));
  jand g141(.dina(n198), .dinb(n165), .dout(n199));
  jxor g142(.dina(n199), .dinb(G113), .dout(G15));
  jand g143(.dina(n198), .dinb(n170), .dout(n201));
  jxor g144(.dina(n201), .dinb(G116), .dout(G18));
  jand g145(.dina(n177), .dinb(n155), .dout(n203));
  jand g146(.dina(n203), .dinb(n197), .dout(n204));
  jxor g147(.dina(n204), .dinb(G119), .dout(G21));
  jand g148(.dina(n197), .dinb(n161), .dout(n206));
  jand g149(.dina(n206), .dinb(n131), .dout(n207));
  jand g150(.dina(n207), .dinb(n186), .dout(n208));
  jxor g151(.dina(n208), .dinb(G122), .dout(G24));
  jand g152(.dina(n191), .dinb(n174), .dout(n210));
  jand g153(.dina(n210), .dinb(n197), .dout(n211));
  jxor g154(.dina(n211), .dinb(G125), .dout(G27));
  jnot g155(.din(n109), .dout(n213));
  jxor g156(.dina(n213), .dinb(n108), .dout(n214));
  jand g157(.dina(n214), .dinb(n96), .dout(n215));
  jand g158(.dina(n215), .dinb(n121), .dout(n216));
  jand g159(.dina(n216), .dinb(n93), .dout(n217));
  jand g160(.dina(n217), .dinb(n191), .dout(n218));
  jxor g161(.dina(n218), .dinb(G131), .dout(G33));
  jand g162(.dina(n217), .dinb(n183), .dout(n220));
  jxor g163(.dina(n220), .dinb(G134), .dout(G36));
  jand g164(.dina(n177), .dinb(n154), .dout(n222));
  jand g165(.dina(n222), .dinb(n182), .dout(n223));
  jand g166(.dina(n223), .dinb(n216), .dout(n224));
  jxor g167(.dina(n224), .dinb(G137), .dout(G39));
  jand g168(.dina(n216), .dinb(n210), .dout(n226));
  jxor g169(.dina(n226), .dinb(G140), .dout(G42));
  jor  g170(.dina(n171), .dinb(n157), .dout(n228));
  jor  g171(.dina(n228), .dinb(n166), .dout(n229));
  jor  g172(.dina(n229), .dinb(n208), .dout(n230));
  jor  g173(.dina(n204), .dinb(n201), .dout(n231));
  jor  g174(.dina(n231), .dinb(n175), .dout(n232));
  jor  g175(.dina(n232), .dinb(n199), .dout(n233));
  jor  g176(.dina(n233), .dinb(n230), .dout(n234));
  jor  g177(.dina(n226), .dinb(n224), .dout(n235));
  jor  g178(.dina(n235), .dinb(n192), .dout(n236));
  jor  g179(.dina(n220), .dinb(n218), .dout(n237));
  jor  g180(.dina(n211), .dinb(n189), .dout(n238));
  jor  g181(.dina(n238), .dinb(n184), .dout(n239));
  jor  g182(.dina(n239), .dinb(n237), .dout(n240));
  jor  g183(.dina(n240), .dinb(n236), .dout(n241));
  jor  g184(.dina(n241), .dinb(n234), .dout(n242));
  jand g185(.dina(n195), .dinb(n214), .dout(n243));
  jxor g186(.dina(n112), .dinb(n95), .dout(n244));
  jand g187(.dina(n244), .dinb(n243), .dout(n245));
  jor  g188(.dina(n245), .dinb(n216), .dout(n246));
  jand g189(.dina(n246), .dinb(n161), .dout(n247));
  jand g190(.dina(n113), .dinb(n96), .dout(n248));
  jand g191(.dina(n248), .dinb(n243), .dout(n249));
  jxor g192(.dina(n160), .dinb(n76), .dout(n250));
  jand g193(.dina(n250), .dinb(n249), .dout(n251));
  jor  g194(.dina(n251), .dinb(n206), .dout(n252));
  jor  g195(.dina(n252), .dinb(n247), .dout(n253));
  jand g196(.dina(n253), .dinb(n154), .dout(n254));
  jand g197(.dina(n254), .dinb(n130), .dout(n255));
  jor  g198(.dina(n255), .dinb(n242), .dout(n256));
  jand g199(.dina(n256), .dinb(G952), .dout(n257));
  jor  g200(.dina(n153), .dinb(n141), .dout(n258));
  jor  g201(.dina(n154), .dinb(n130), .dout(n259));
  jand g202(.dina(n259), .dinb(n258), .dout(n260));
  jand g203(.dina(n260), .dinb(n161), .dout(n261));
  jand g204(.dina(n261), .dinb(n249), .dout(n262));
  jor  g205(.dina(n262), .dinb(G953), .dout(n263));
  jor  g206(.dina(n263), .dinb(n257), .dout(G75));
  jor  g207(.dina(n103), .dinb(G952), .dout(n265));
  jand g208(.dina(n242), .dinb(G210), .dout(n266));
  jand g209(.dina(n266), .dinb(G902), .dout(n267));
  jxor g210(.dina(n267), .dinb(n107), .dout(n268));
  jand g211(.dina(n268), .dinb(n265), .dout(G51));
  jand g212(.dina(n242), .dinb(G469), .dout(n270));
  jand g213(.dina(n270), .dinb(G902), .dout(n271));
  jxor g214(.dina(n271), .dinb(n118), .dout(n272));
  jand g215(.dina(n272), .dinb(n265), .dout(G54));
  jand g216(.dina(G902), .dinb(G475), .dout(n274));
  jand g217(.dina(n274), .dinb(n242), .dout(n275));
  jor  g218(.dina(n275), .dinb(n151), .dout(n276));
  jnot g219(.din(n151), .dout(n277));
  jnot g220(.din(n131), .dout(n278));
  jor  g221(.dina(n92), .dinb(n173), .dout(n279));
  jor  g222(.dina(n214), .dinb(n95), .dout(n280));
  jor  g223(.dina(n120), .dinb(n112), .dout(n281));
  jor  g224(.dina(n281), .dinb(n280), .dout(n282));
  jor  g225(.dina(n282), .dinb(n279), .dout(n283));
  jor  g226(.dina(n283), .dinb(n278), .dout(n284));
  jor  g227(.dina(n284), .dinb(n258), .dout(n285));
  jor  g228(.dina(n195), .dinb(n112), .dout(n286));
  jor  g229(.dina(n286), .dinb(n280), .dout(n287));
  jor  g230(.dina(n279), .dinb(n287), .dout(n288));
  jnot g231(.din(n165), .dout(n289));
  jor  g232(.dina(n289), .dinb(n288), .dout(n290));
  jor  g233(.dina(n160), .dinb(n173), .dout(n291));
  jor  g234(.dina(n163), .dinb(n168), .dout(n292));
  jor  g235(.dina(n292), .dinb(n278), .dout(n293));
  jor  g236(.dina(n293), .dinb(n287), .dout(n294));
  jor  g237(.dina(n294), .dinb(n291), .dout(n295));
  jor  g238(.dina(n163), .dinb(n141), .dout(n296));
  jor  g239(.dina(n296), .dinb(n278), .dout(n297));
  jor  g240(.dina(n297), .dinb(n288), .dout(n298));
  jand g241(.dina(n298), .dinb(n295), .dout(n299));
  jand g242(.dina(n299), .dinb(n290), .dout(n300));
  jand g243(.dina(n300), .dinb(n285), .dout(n301));
  jnot g244(.din(n199), .dout(n302));
  jor  g245(.dina(n92), .dinb(n76), .dout(n303));
  jor  g246(.dina(n303), .dinb(n294), .dout(n304));
  jor  g247(.dina(n282), .dinb(n291), .dout(n305));
  jor  g248(.dina(n305), .dinb(n297), .dout(n306));
  jor  g249(.dina(n160), .dinb(n76), .dout(n307));
  jor  g250(.dina(n307), .dinb(n293), .dout(n308));
  jor  g251(.dina(n308), .dinb(n282), .dout(n309));
  jand g252(.dina(n309), .dinb(n306), .dout(n310));
  jand g253(.dina(n310), .dinb(n304), .dout(n311));
  jand g254(.dina(n311), .dinb(n302), .dout(n312));
  jand g255(.dina(n312), .dinb(n301), .dout(n313));
  jnot g256(.din(n192), .dout(n314));
  jor  g257(.dina(n110), .dinb(n95), .dout(n315));
  jor  g258(.dina(n315), .dinb(n286), .dout(n316));
  jnot g259(.din(n182), .dout(n317));
  jor  g260(.dina(n307), .dinb(n292), .dout(n318));
  jor  g261(.dina(n318), .dinb(n317), .dout(n319));
  jor  g262(.dina(n319), .dinb(n316), .dout(n320));
  jor  g263(.dina(n153), .dinb(n168), .dout(n321));
  jor  g264(.dina(n317), .dinb(n321), .dout(n322));
  jor  g265(.dina(n322), .dinb(n303), .dout(n323));
  jor  g266(.dina(n316), .dinb(n323), .dout(n324));
  jand g267(.dina(n324), .dinb(n320), .dout(n325));
  jand g268(.dina(n325), .dinb(n314), .dout(n326));
  jor  g269(.dina(n316), .dinb(n291), .dout(n327));
  jor  g270(.dina(n327), .dinb(n322), .dout(n328));
  jnot g271(.din(n183), .dout(n329));
  jor  g272(.dina(n327), .dinb(n329), .dout(n330));
  jand g273(.dina(n330), .dinb(n328), .dout(n331));
  jor  g274(.dina(n307), .dinb(n287), .dout(n332));
  jor  g275(.dina(n329), .dinb(n332), .dout(n333));
  jor  g276(.dina(n258), .dinb(n291), .dout(n334));
  jor  g277(.dina(n334), .dinb(n317), .dout(n335));
  jor  g278(.dina(n335), .dinb(n287), .dout(n336));
  jor  g279(.dina(n323), .dinb(n282), .dout(n337));
  jand g280(.dina(n337), .dinb(n336), .dout(n338));
  jand g281(.dina(n338), .dinb(n333), .dout(n339));
  jand g282(.dina(n339), .dinb(n331), .dout(n340));
  jand g283(.dina(n340), .dinb(n326), .dout(n341));
  jand g284(.dina(n341), .dinb(n313), .dout(n342));
  jnot g285(.din(n274), .dout(n343));
  jor  g286(.dina(n343), .dinb(n342), .dout(n344));
  jor  g287(.dina(n344), .dinb(n277), .dout(n345));
  jand g288(.dina(n345), .dinb(n265), .dout(n346));
  jand g289(.dina(n346), .dinb(n276), .dout(G60));
  jand g290(.dina(n242), .dinb(G478), .dout(n348));
  jand g291(.dina(n348), .dinb(G902), .dout(n349));
  jxor g292(.dina(n349), .dinb(n139), .dout(n350));
  jand g293(.dina(n350), .dinb(n265), .dout(G63));
  jand g294(.dina(n242), .dinb(G217), .dout(n352));
  jand g295(.dina(n352), .dinb(G902), .dout(n353));
  jxor g296(.dina(n353), .dinb(n70), .dout(n354));
  jand g297(.dina(n354), .dinb(n265), .dout(G66));
  jor  g298(.dina(n124), .dinb(n102), .dout(n356));
  jor  g299(.dina(n313), .dinb(G953), .dout(n357));
  jand g300(.dina(G898), .dinb(G224), .dout(n358));
  jor  g301(.dina(n358), .dinb(n103), .dout(n359));
  jand g302(.dina(n359), .dinb(n357), .dout(n360));
  jxor g303(.dina(n360), .dinb(n356), .dout(G69));
  jor  g304(.dina(n341), .dinb(G953), .dout(n362));
  jand g305(.dina(G900), .dinb(G227), .dout(n363));
  jor  g306(.dina(n363), .dinb(n103), .dout(n364));
  jand g307(.dina(n364), .dinb(n362), .dout(n365));
  jxor g308(.dina(n81), .dinb(n66), .dout(n366));
  jor  g309(.dina(n366), .dinb(n180), .dout(n367));
  jxor g310(.dina(n367), .dinb(n365), .dout(G72));
  jand g311(.dina(G902), .dinb(G472), .dout(n369));
  jand g312(.dina(n369), .dinb(n242), .dout(n370));
  jxor g313(.dina(n370), .dinb(n90), .dout(n371));
  jand g314(.dina(n371), .dinb(n265), .dout(G57));
endmodule


