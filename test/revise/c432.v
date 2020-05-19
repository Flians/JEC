// Benchmark "c432." written by ABC on Wed May 06 16:49:41 2020

module c432 ( 
    G1gat, G4gat, G8gat, G11gat, G14gat, G17gat, G21gat, G24gat, G27gat,
    G30gat, G34gat, G37gat, G40gat, G43gat, G47gat, G50gat, G53gat, G56gat,
    G60gat, G63gat, G66gat, G69gat, G73gat, G76gat, G79gat, G82gat, G86gat,
    G89gat, G92gat, G95gat, G99gat, G102gat, G105gat, G108gat, G112gat,
    G115gat,
    G223gat, G329gat, G370gat, G421gat, G430gat, G431gat, G432gat  );
  input  G1gat, G4gat, G8gat, G11gat, G14gat, G17gat, G21gat, G24gat,
    G27gat, G30gat, G34gat, G37gat, G40gat, G43gat, G47gat, G50gat, G53gat,
    G56gat, G60gat, G63gat, G66gat, G69gat, G73gat, G76gat, G79gat, G82gat,
    G86gat, G89gat, G92gat, G95gat, G99gat, G102gat, G105gat, G108gat,
    G112gat, G115gat;
  output G223gat, G329gat, G370gat, G421gat, G430gat, G431gat, G432gat;
  wire n43, n44, n45, n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56,
    n57, n58, n59, n60, n61, n62, n63, n64, n65, n66, n67, n69, n70, n71,
    n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85,
    n86, n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99,
    n100, n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111,
    n112, n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123,
    n124, n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135,
    n136, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147, n148,
    n150, n151, n153, n154, n155, n156, n157, n158, n159, n160, n161, n162,
    n163, n164, n165, n166, n167, n168, n169, n170, n171, n172, n173, n174,
    n175, n176, n177, n178, n179, n180, n181, n182, n183, n184, n185, n186,
    n187, n188, n189, n191, n192, n193, n195, n196, n197, n198, n199, n200,
    n201, n202, n203, n204, n205, n206, n207, n208, n209, n210, n211, n212,
    n213, n214, n215, n217, n218, n219, n221, n222, n223, n224, n225, n226,
    n227, n228, n230, n231, n232, n233, n235, n237, n238, n239, n240, n241,
    n242, n244, n246, n247, n248, n249, n250, n251, n252, n253, n254, n255,
    n256, n257, n258, n259, n260, n262, n264, n265, n266, n267, n268, n269,
    n270, n271, n272, n273, n274, n275, n276, n277, n278, n279, n280, n281,
    n282, n283, n284, n285, n286, n287, n290, n291, n292, n293, n295, n296,
    n297, n298, n299, n300, n301, n302, n303, n304, n305, n306, n307, n308,
    n310, n311, n312, n313, n314, n315, n316, n317, n318, n319, n320, n322,
    n323, n324, n325, n326, n327, n328, n329;
  jnot g000(.din(G76gat), .dout(n43));
  jand g001(.dina(G82gat), .dinb(n43), .dout(n44));
  jnot g002(.din(G24gat), .dout(n45));
  jand g003(.dina(G30gat), .dinb(n45), .dout(n46));
  jnot g004(.din(G11gat), .dout(n47));
  jand g005(.dina(G17gat), .dinb(n47), .dout(n48));
  jcb  g006(.dina(n48), .dinb(n46), .dout(n49));
  jcb  g007(.dina(n49), .dinb(n44), .dout(n50));
  jnot g008(.din(G37gat), .dout(n51));
  jand g009(.dina(G43gat), .dinb(n51), .dout(n52));
  jnot g010(.din(G63gat), .dout(n53));
  jand g011(.dina(G69gat), .dinb(n53), .dout(n54));
  jcb  g012(.dina(n54), .dinb(n52), .dout(n55));
  jnot g013(.din(G102gat), .dout(n56));
  jand g014(.dina(G108gat), .dinb(n56), .dout(n57));
  jnot g015(.din(G50gat), .dout(n58));
  jand g016(.dina(G56gat), .dinb(n58), .dout(n59));
  jcb  g017(.dina(n59), .dinb(n57), .dout(n60));
  jnot g018(.din(G89gat), .dout(n61));
  jand g019(.dina(G95gat), .dinb(n61), .dout(n62));
  jnot g020(.din(G1gat), .dout(n63));
  jand g021(.dina(G4gat), .dinb(n63), .dout(n64));
  jcb  g022(.dina(n64), .dinb(n62), .dout(n65));
  jcb  g023(.dina(n65), .dinb(n60), .dout(n66));
  jcb  g024(.dina(n66), .dinb(n55), .dout(n67));
  jcb  g025(.dina(n67), .dinb(n50), .dout(G223gat));
  jnot g026(.din(G112gat), .dout(n69));
  jnot g027(.din(n44), .dout(n70));
  jnot g028(.din(G30gat), .dout(n71));
  jcb  g029(.dina(n71), .dinb(G24gat), .dout(n72));
  jnot g030(.din(G17gat), .dout(n73));
  jcb  g031(.dina(n73), .dinb(G11gat), .dout(n74));
  jand g032(.dina(n74), .dinb(n72), .dout(n75));
  jand g033(.dina(n75), .dinb(n70), .dout(n76));
  jnot g034(.din(G43gat), .dout(n77));
  jcb  g035(.dina(n77), .dinb(G37gat), .dout(n78));
  jnot g036(.din(G69gat), .dout(n79));
  jcb  g037(.dina(n79), .dinb(G63gat), .dout(n80));
  jand g038(.dina(n80), .dinb(n78), .dout(n81));
  jnot g039(.din(G108gat), .dout(n82));
  jcb  g040(.dina(n82), .dinb(G102gat), .dout(n83));
  jnot g041(.din(G56gat), .dout(n84));
  jcb  g042(.dina(n84), .dinb(G50gat), .dout(n85));
  jand g043(.dina(n85), .dinb(n83), .dout(n86));
  jnot g044(.din(G95gat), .dout(n87));
  jcb  g045(.dina(n87), .dinb(G89gat), .dout(n88));
  jnot g046(.din(G4gat), .dout(n89));
  jcb  g047(.dina(n89), .dinb(G1gat), .dout(n90));
  jand g048(.dina(n90), .dinb(n88), .dout(n91));
  jand g049(.dina(n91), .dinb(n86), .dout(n92));
  jand g050(.dina(n92), .dinb(n81), .dout(n93));
  jand g051(.dina(n93), .dinb(n76), .dout(n94));
  jcb  g052(.dina(n94), .dinb(n56), .dout(n95));
  jand g053(.dina(n95), .dinb(G108gat), .dout(n96));
  jand g054(.dina(n96), .dinb(n69), .dout(n97));
  jnot g055(.din(G8gat), .dout(n98));
  jcb  g056(.dina(n94), .dinb(n63), .dout(n99));
  jand g057(.dina(n99), .dinb(G4gat), .dout(n100));
  jand g058(.dina(n100), .dinb(n98), .dout(n101));
  jcb  g059(.dina(n101), .dinb(n97), .dout(n102));
  jnot g060(.din(G99gat), .dout(n103));
  jcb  g061(.dina(n94), .dinb(n61), .dout(n104));
  jand g062(.dina(n104), .dinb(G95gat), .dout(n105));
  jand g063(.dina(n105), .dinb(n103), .dout(n106));
  jnot g064(.din(G73gat), .dout(n107));
  jcb  g065(.dina(n94), .dinb(n53), .dout(n108));
  jand g066(.dina(n108), .dinb(G69gat), .dout(n109));
  jand g067(.dina(n109), .dinb(n107), .dout(n110));
  jcb  g068(.dina(n110), .dinb(n106), .dout(n111));
  jcb  g069(.dina(n111), .dinb(n102), .dout(n112));
  jxor g070(.dina(n94), .dinb(n72), .dout(n113));
  jcb  g071(.dina(n113), .dinb(n71), .dout(n114));
  jcb  g072(.dina(n114), .dinb(G34gat), .dout(n115));
  jnot g073(.din(n115), .dout(n116));
  jnot g074(.din(G60gat), .dout(n117));
  jcb  g075(.dina(n94), .dinb(n58), .dout(n118));
  jand g076(.dina(n118), .dinb(G56gat), .dout(n119));
  jand g077(.dina(n119), .dinb(n117), .dout(n120));
  jxor g078(.dina(n94), .dinb(n52), .dout(n121));
  jnot g079(.din(G47gat), .dout(n122));
  jand g080(.dina(n122), .dinb(G43gat), .dout(n123));
  jand g081(.dina(n123), .dinb(n121), .dout(n124));
  jcb  g082(.dina(n124), .dinb(n120), .dout(n125));
  jnot g083(.din(G86gat), .dout(n126));
  jcb  g084(.dina(n94), .dinb(n43), .dout(n127));
  jand g085(.dina(n127), .dinb(G82gat), .dout(n128));
  jand g086(.dina(n128), .dinb(n126), .dout(n129));
  jnot g087(.din(G21gat), .dout(n130));
  jcb  g088(.dina(n94), .dinb(n47), .dout(n131));
  jand g089(.dina(n131), .dinb(G17gat), .dout(n132));
  jand g090(.dina(n132), .dinb(n130), .dout(n133));
  jcb  g091(.dina(n133), .dinb(n129), .dout(n134));
  jcb  g092(.dina(n134), .dinb(n125), .dout(n135));
  jcb  g093(.dina(n135), .dinb(n116), .dout(n136));
  jcb  g094(.dina(n136), .dinb(n112), .dout(G329gat));
  jand g095(.dina(G223gat), .dinb(G89gat), .dout(n138));
  jcb  g096(.dina(n138), .dinb(n87), .dout(n139));
  jand g097(.dina(G329gat), .dinb(G99gat), .dout(n140));
  jcb  g098(.dina(n140), .dinb(n139), .dout(n141));
  jcb  g099(.dina(n141), .dinb(G105gat), .dout(n142));
  jnot g100(.din(n142), .dout(n143));
  jand g101(.dina(G223gat), .dinb(G50gat), .dout(n144));
  jcb  g102(.dina(n144), .dinb(n84), .dout(n145));
  jcb  g103(.dina(n145), .dinb(G60gat), .dout(n146));
  jand g104(.dina(G329gat), .dinb(n146), .dout(n147));
  jnot g105(.din(n147), .dout(n148));
  jnot g106(.din(G66gat), .dout(n150));
  jand g107(.dina(n119), .dinb(n150), .dout(n151));
  jand g108(.dina(n151), .dinb(n148), .dout(n153));
  jnot g109(.din(G79gat), .dout(n154));
  jand g110(.dina(G223gat), .dinb(G102gat), .dout(n155));
  jcb  g111(.dina(n155), .dinb(n82), .dout(n156));
  jcb  g112(.dina(n156), .dinb(G112gat), .dout(n157));
  jand g113(.dina(G223gat), .dinb(G1gat), .dout(n158));
  jcb  g114(.dina(n158), .dinb(n89), .dout(n159));
  jcb  g115(.dina(n159), .dinb(G8gat), .dout(n160));
  jand g116(.dina(n160), .dinb(n157), .dout(n161));
  jcb  g117(.dina(n139), .dinb(G99gat), .dout(n162));
  jand g118(.dina(G223gat), .dinb(G63gat), .dout(n163));
  jcb  g119(.dina(n163), .dinb(n79), .dout(n164));
  jcb  g120(.dina(n164), .dinb(G73gat), .dout(n165));
  jand g121(.dina(n165), .dinb(n162), .dout(n166));
  jand g122(.dina(n166), .dinb(n161), .dout(n167));
  jxor g123(.dina(n94), .dinb(n78), .dout(n168));
  jnot g124(.din(n123), .dout(n169));
  jcb  g125(.dina(n169), .dinb(n168), .dout(n170));
  jand g126(.dina(n170), .dinb(n146), .dout(n171));
  jnot g127(.din(G82gat), .dout(n172));
  jand g128(.dina(G223gat), .dinb(G76gat), .dout(n173));
  jcb  g129(.dina(n173), .dinb(n172), .dout(n174));
  jcb  g130(.dina(n174), .dinb(G86gat), .dout(n175));
  jand g131(.dina(G223gat), .dinb(G11gat), .dout(n176));
  jcb  g132(.dina(n176), .dinb(n73), .dout(n177));
  jcb  g133(.dina(n177), .dinb(G21gat), .dout(n178));
  jand g134(.dina(n178), .dinb(n175), .dout(n179));
  jand g135(.dina(n179), .dinb(n171), .dout(n180));
  jand g136(.dina(n180), .dinb(n115), .dout(n181));
  jand g137(.dina(n181), .dinb(n167), .dout(n182));
  jcb  g138(.dina(n182), .dinb(n107), .dout(n183));
  jand g139(.dina(n183), .dinb(n109), .dout(n184));
  jand g140(.dina(n184), .dinb(n154), .dout(n185));
  jcb  g141(.dina(n185), .dinb(n153), .dout(n186));
  jcb  g142(.dina(n186), .dinb(n143), .dout(n187));
  jand g143(.dina(G329gat), .dinb(n170), .dout(n188));
  jnot g144(.din(n188), .dout(n189));
  jnot g145(.din(G53gat), .dout(n191));
  jand g146(.dina(n191), .dinb(G43gat), .dout(n192));
  jand g147(.dina(n192), .dinb(n121), .dout(n193));
  jand g148(.dina(n193), .dinb(n189), .dout(n195));
  jcb  g149(.dina(n182), .dinb(n130), .dout(n196));
  jand g150(.dina(n196), .dinb(n132), .dout(n197));
  jnot g151(.din(G27gat), .dout(n198));
  jcb  g152(.dina(G329gat), .dinb(G21gat), .dout(n199));
  jand g153(.dina(n199), .dinb(n198), .dout(n200));
  jand g154(.dina(n200), .dinb(n197), .dout(n201));
  jcb  g155(.dina(n201), .dinb(n195), .dout(n202));
  jcb  g156(.dina(n182), .dinb(n126), .dout(n203));
  jand g157(.dina(n203), .dinb(n128), .dout(n204));
  jnot g158(.din(G92gat), .dout(n205));
  jcb  g159(.dina(G329gat), .dinb(G86gat), .dout(n206));
  jand g160(.dina(n206), .dinb(n205), .dout(n207));
  jand g161(.dina(n207), .dinb(n204), .dout(n208));
  jnot g162(.din(G14gat), .dout(n209));
  jcb  g163(.dina(n182), .dinb(n98), .dout(n210));
  jand g164(.dina(n210), .dinb(n100), .dout(n211));
  jand g165(.dina(n211), .dinb(n209), .dout(n212));
  jcb  g166(.dina(n212), .dinb(n208), .dout(n213));
  jnot g167(.din(G34gat), .dout(n214));
  jcb  g168(.dina(n182), .dinb(n214), .dout(n215));
  jnot g169(.din(G40gat), .dout(n217));
  jnot g170(.din(n114), .dout(n218));
  jand g171(.dina(n218), .dinb(n217), .dout(n219));
  jand g172(.dina(n219), .dinb(n215), .dout(n221));
  jnot g173(.din(G115gat), .dout(n222));
  jcb  g174(.dina(n182), .dinb(n69), .dout(n223));
  jand g175(.dina(n223), .dinb(n96), .dout(n224));
  jand g176(.dina(n224), .dinb(n222), .dout(n225));
  jcb  g177(.dina(n225), .dinb(n221), .dout(n226));
  jcb  g178(.dina(n226), .dinb(n213), .dout(n227));
  jcb  g179(.dina(n227), .dinb(n202), .dout(n228));
  jcb  g180(.dina(n228), .dinb(n187), .dout(G370gat));
  jand g181(.dina(G329gat), .dinb(G8gat), .dout(n230));
  jcb  g182(.dina(n230), .dinb(n159), .dout(n231));
  jand g183(.dina(G370gat), .dinb(G14gat), .dout(n232));
  jcb  g184(.dina(n232), .dinb(n231), .dout(n233));
  jnot g185(.din(n151), .dout(n235));
  jcb  g186(.dina(n235), .dinb(n147), .dout(n237));
  jand g187(.dina(G329gat), .dinb(G73gat), .dout(n238));
  jcb  g188(.dina(n238), .dinb(n164), .dout(n239));
  jcb  g189(.dina(n239), .dinb(G79gat), .dout(n240));
  jand g190(.dina(n240), .dinb(n237), .dout(n241));
  jand g191(.dina(n241), .dinb(n142), .dout(n242));
  jnot g192(.din(n193), .dout(n244));
  jcb  g193(.dina(n244), .dinb(n188), .dout(n246));
  jand g194(.dina(G329gat), .dinb(G21gat), .dout(n247));
  jcb  g195(.dina(n247), .dinb(n177), .dout(n248));
  jand g196(.dina(n182), .dinb(n130), .dout(n249));
  jcb  g197(.dina(n249), .dinb(G27gat), .dout(n250));
  jcb  g198(.dina(n250), .dinb(n248), .dout(n251));
  jand g199(.dina(n251), .dinb(n246), .dout(n252));
  jand g200(.dina(G329gat), .dinb(G86gat), .dout(n253));
  jcb  g201(.dina(n253), .dinb(n174), .dout(n254));
  jand g202(.dina(n182), .dinb(n126), .dout(n255));
  jcb  g203(.dina(n255), .dinb(G92gat), .dout(n256));
  jcb  g204(.dina(n256), .dinb(n254), .dout(n257));
  jcb  g205(.dina(n231), .dinb(G14gat), .dout(n258));
  jand g206(.dina(n258), .dinb(n257), .dout(n259));
  jand g207(.dina(G329gat), .dinb(G34gat), .dout(n260));
  jnot g208(.din(n219), .dout(n262));
  jcb  g209(.dina(n262), .dinb(n260), .dout(n264));
  jand g210(.dina(G329gat), .dinb(G112gat), .dout(n265));
  jcb  g211(.dina(n265), .dinb(n156), .dout(n266));
  jcb  g212(.dina(n266), .dinb(G115gat), .dout(n267));
  jand g213(.dina(n267), .dinb(n264), .dout(n268));
  jand g214(.dina(n268), .dinb(n259), .dout(n269));
  jand g215(.dina(n269), .dinb(n252), .dout(n270));
  jand g216(.dina(n270), .dinb(n242), .dout(n271));
  jcb  g217(.dina(n271), .dinb(n150), .dout(n272));
  jand g218(.dina(G329gat), .dinb(G60gat), .dout(n273));
  jcb  g219(.dina(n273), .dinb(n145), .dout(n274));
  jnot g220(.din(n274), .dout(n275));
  jand g221(.dina(n275), .dinb(n272), .dout(n276));
  jcb  g222(.dina(n271), .dinb(n191), .dout(n277));
  jand g223(.dina(G329gat), .dinb(G47gat), .dout(n278));
  jand g224(.dina(G223gat), .dinb(G37gat), .dout(n279));
  jcb  g225(.dina(n279), .dinb(n77), .dout(n280));
  jcb  g226(.dina(n280), .dinb(n278), .dout(n281));
  jnot g227(.din(n281), .dout(n282));
  jand g228(.dina(n282), .dinb(n277), .dout(n283));
  jcb  g229(.dina(n283), .dinb(n276), .dout(n284));
  jcb  g230(.dina(n271), .dinb(n198), .dout(n285));
  jand g231(.dina(n285), .dinb(n197), .dout(n286));
  jcb  g232(.dina(n271), .dinb(n217), .dout(n287));
  jcb  g233(.dina(n114), .dinb(n260), .dout(n290));
  jnot g234(.din(n290), .dout(n291));
  jand g235(.dina(n291), .dinb(n287), .dout(n292));
  jcb  g236(.dina(n292), .dinb(n286), .dout(n293));
  jcb  g237(.dina(n293), .dinb(n284), .dout(G430gat));
  jcb  g238(.dina(n271), .dinb(n205), .dout(n295));
  jand g239(.dina(n295), .dinb(n204), .dout(n296));
  jcb  g240(.dina(n271), .dinb(n222), .dout(n297));
  jand g241(.dina(n297), .dinb(n224), .dout(n298));
  jcb  g242(.dina(n298), .dinb(n296), .dout(n299));
  jnot g243(.din(n141), .dout(n300));
  jnot g244(.din(G105gat), .dout(n301));
  jcb  g245(.dina(n271), .dinb(n301), .dout(n302));
  jand g246(.dina(n302), .dinb(n300), .dout(n303));
  jcb  g247(.dina(n271), .dinb(n154), .dout(n304));
  jand g248(.dina(n304), .dinb(n184), .dout(n305));
  jcb  g249(.dina(n305), .dinb(n303), .dout(n306));
  jcb  g250(.dina(n306), .dinb(n299), .dout(n307));
  jcb  g251(.dina(n307), .dinb(G430gat), .dout(n308));
  jand g252(.dina(n308), .dinb(n233), .dout(G421gat));
  jand g253(.dina(G370gat), .dinb(G66gat), .dout(n310));
  jcb  g254(.dina(n274), .dinb(n310), .dout(n311));
  jand g255(.dina(G370gat), .dinb(G53gat), .dout(n312));
  jcb  g256(.dina(n281), .dinb(n312), .dout(n313));
  jand g257(.dina(n313), .dinb(n311), .dout(n314));
  jand g258(.dina(n296), .dinb(n314), .dout(n315));
  jand g259(.dina(G370gat), .dinb(G40gat), .dout(n316));
  jcb  g260(.dina(n290), .dinb(n316), .dout(n317));
  jand g261(.dina(n305), .dinb(n317), .dout(n318));
  jand g262(.dina(n318), .dinb(n314), .dout(n319));
  jcb  g263(.dina(n319), .dinb(n293), .dout(n320));
  jcb  g264(.dina(n320), .dinb(n315), .dout(G431gat));
  jand g265(.dina(n303), .dinb(n317), .dout(n322));
  jand g266(.dina(G370gat), .dinb(G92gat), .dout(n323));
  jcb  g267(.dina(n323), .dinb(n254), .dout(n324));
  jand g268(.dina(n324), .dinb(n313), .dout(n325));
  jand g269(.dina(n325), .dinb(n322), .dout(n326));
  jand g270(.dina(n317), .dinb(n283), .dout(n327));
  jcb  g271(.dina(n327), .dinb(n286), .dout(n328));
  jcb  g272(.dina(n328), .dinb(n319), .dout(n329));
  jcb  g273(.dina(n329), .dinb(n326), .dout(G432gat));
endmodule


