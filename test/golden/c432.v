// Benchmark "c432" written by ABC on Sun May 24 21:28:03 2020

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
    n57, n58, n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n70, n71,
    n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85,
    n86, n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99,
    n100, n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111,
    n112, n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123,
    n124, n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135,
    n137, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147, n148,
    n149, n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
    n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171, n172,
    n173, n174, n175, n176, n177, n178, n179, n180, n181, n182, n183, n184,
    n185, n186, n187, n188, n189, n190, n191, n192, n193, n194, n195, n196,
    n197, n198, n199, n200, n201, n202, n203, n204, n205, n206, n207, n208,
    n209, n210, n211, n212, n213, n214, n216, n217, n218, n219, n220, n221,
    n222, n223, n224, n225, n226, n227, n228, n229, n230, n231, n232, n233,
    n234, n235, n236, n237, n238, n239, n240, n241, n242, n243, n244, n245,
    n246, n247, n248, n249, n250, n251, n252, n253, n254, n255, n256, n257,
    n258, n259, n260, n261, n263, n264, n265, n266, n267, n268, n269, n270,
    n271, n272, n273, n274, n275, n276, n277, n278, n279, n281, n282, n283,
    n284, n285, n286, n287, n288, n289, n290, n291, n292, n294, n295, n296,
    n297;
  jnot g000(.din(G102gat), .dout(n43));
  jand g001(.dina(G108gat), .dinb(n43), .dout(n44));
  jnot g002(.din(G43gat), .dout(n45));
  jor  g003(.dina(n45), .dinb(G37gat), .dout(n46));
  jnot g004(.din(n46), .dout(n47));
  jor  g005(.dina(n47), .dinb(n44), .dout(n48));
  jnot g006(.din(G63gat), .dout(n49));
  jand g007(.dina(G69gat), .dinb(n49), .dout(n50));
  jnot g008(.din(G11gat), .dout(n51));
  jand g009(.dina(G17gat), .dinb(n51), .dout(n52));
  jor  g010(.dina(n52), .dinb(n50), .dout(n53));
  jnot g011(.din(G24gat), .dout(n54));
  jand g012(.dina(G30gat), .dinb(n54), .dout(n55));
  jnot g013(.din(G50gat), .dout(n56));
  jand g014(.dina(G56gat), .dinb(n56), .dout(n57));
  jor  g015(.dina(n57), .dinb(n55), .dout(n58));
  jor  g016(.dina(n58), .dinb(n53), .dout(n59));
  jnot g017(.din(G1gat), .dout(n60));
  jand g018(.dina(G4gat), .dinb(n60), .dout(n61));
  jnot g019(.din(G89gat), .dout(n62));
  jand g020(.dina(G95gat), .dinb(n62), .dout(n63));
  jnot g021(.din(G76gat), .dout(n64));
  jand g022(.dina(G82gat), .dinb(n64), .dout(n65));
  jor  g023(.dina(n65), .dinb(n63), .dout(n66));
  jor  g024(.dina(n66), .dinb(n61), .dout(n67));
  jor  g025(.dina(n67), .dinb(n59), .dout(n68));
  jor  g026(.dina(n68), .dinb(n48), .dout(G223gat));
  jnot g027(.din(G21gat), .dout(n70));
  jnot g028(.din(n44), .dout(n71));
  jand g029(.dina(n46), .dinb(n71), .dout(n72));
  jnot g030(.din(G69gat), .dout(n73));
  jor  g031(.dina(n73), .dinb(G63gat), .dout(n74));
  jnot g032(.din(G17gat), .dout(n75));
  jor  g033(.dina(n75), .dinb(G11gat), .dout(n76));
  jand g034(.dina(n76), .dinb(n74), .dout(n77));
  jnot g035(.din(G30gat), .dout(n78));
  jor  g036(.dina(n78), .dinb(G24gat), .dout(n79));
  jnot g037(.din(G56gat), .dout(n80));
  jor  g038(.dina(n80), .dinb(G50gat), .dout(n81));
  jand g039(.dina(n81), .dinb(n79), .dout(n82));
  jand g040(.dina(n82), .dinb(n77), .dout(n83));
  jnot g041(.din(G4gat), .dout(n84));
  jor  g042(.dina(n84), .dinb(G1gat), .dout(n85));
  jnot g043(.din(G95gat), .dout(n86));
  jor  g044(.dina(n86), .dinb(G89gat), .dout(n87));
  jnot g045(.din(G82gat), .dout(n88));
  jor  g046(.dina(n88), .dinb(G76gat), .dout(n89));
  jand g047(.dina(n89), .dinb(n87), .dout(n90));
  jand g048(.dina(n90), .dinb(n85), .dout(n91));
  jand g049(.dina(n91), .dinb(n83), .dout(n92));
  jand g050(.dina(n92), .dinb(n72), .dout(n93));
  jor  g051(.dina(n93), .dinb(n51), .dout(n94));
  jand g052(.dina(n94), .dinb(G17gat), .dout(n95));
  jand g053(.dina(n95), .dinb(n70), .dout(n96));
  jnot g054(.din(G99gat), .dout(n97));
  jor  g055(.dina(n93), .dinb(n62), .dout(n98));
  jand g056(.dina(n98), .dinb(G95gat), .dout(n99));
  jand g057(.dina(n99), .dinb(n97), .dout(n100));
  jor  g058(.dina(n100), .dinb(n96), .dout(n101));
  jnot g059(.din(G73gat), .dout(n102));
  jor  g060(.dina(n93), .dinb(n49), .dout(n103));
  jand g061(.dina(n103), .dinb(G69gat), .dout(n104));
  jand g062(.dina(n104), .dinb(n102), .dout(n105));
  jnot g063(.din(G34gat), .dout(n106));
  jor  g064(.dina(n93), .dinb(n54), .dout(n107));
  jand g065(.dina(n107), .dinb(G30gat), .dout(n108));
  jand g066(.dina(n108), .dinb(n106), .dout(n109));
  jor  g067(.dina(n109), .dinb(n105), .dout(n110));
  jnot g068(.din(G112gat), .dout(n111));
  jor  g069(.dina(n93), .dinb(n43), .dout(n112));
  jand g070(.dina(n112), .dinb(G108gat), .dout(n113));
  jand g071(.dina(n113), .dinb(n111), .dout(n114));
  jor  g072(.dina(n114), .dinb(n110), .dout(n115));
  jor  g073(.dina(n115), .dinb(n101), .dout(n116));
  jnot g074(.din(G60gat), .dout(n117));
  jxor g075(.dina(n93), .dinb(n57), .dout(n118));
  jand g076(.dina(n118), .dinb(G56gat), .dout(n119));
  jand g077(.dina(n119), .dinb(n117), .dout(n120));
  jnot g078(.din(G86gat), .dout(n121));
  jor  g079(.dina(n93), .dinb(n64), .dout(n122));
  jand g080(.dina(n122), .dinb(G82gat), .dout(n123));
  jand g081(.dina(n123), .dinb(n121), .dout(n124));
  jnot g082(.din(G8gat), .dout(n125));
  jor  g083(.dina(n93), .dinb(n60), .dout(n126));
  jand g084(.dina(n126), .dinb(G4gat), .dout(n127));
  jand g085(.dina(n127), .dinb(n125), .dout(n128));
  jnot g086(.din(G47gat), .dout(n129));
  jor  g087(.dina(n93), .dinb(n47), .dout(n130));
  jand g088(.dina(n130), .dinb(G43gat), .dout(n131));
  jand g089(.dina(n131), .dinb(n129), .dout(n132));
  jor  g090(.dina(n132), .dinb(n128), .dout(n133));
  jor  g091(.dina(n133), .dinb(n124), .dout(n134));
  jor  g092(.dina(n134), .dinb(n120), .dout(n135));
  jor  g093(.dina(n135), .dinb(n116), .dout(G329gat));
  jand g094(.dina(G223gat), .dinb(G89gat), .dout(n137));
  jor  g095(.dina(n137), .dinb(n86), .dout(n138));
  jand g096(.dina(G329gat), .dinb(G99gat), .dout(n139));
  jor  g097(.dina(n139), .dinb(n138), .dout(n140));
  jor  g098(.dina(n140), .dinb(G105gat), .dout(n141));
  jnot g099(.din(n141), .dout(n142));
  jand g100(.dina(G329gat), .dinb(G47gat), .dout(n143));
  jnot g101(.din(n143), .dout(n144));
  jnot g102(.din(G53gat), .dout(n145));
  jand g103(.dina(n131), .dinb(n145), .dout(n146));
  jand g104(.dina(n146), .dinb(n144), .dout(n147));
  jor  g105(.dina(n147), .dinb(n142), .dout(n148));
  jnot g106(.din(G40gat), .dout(n149));
  jand g107(.dina(G223gat), .dinb(G11gat), .dout(n150));
  jor  g108(.dina(n150), .dinb(n75), .dout(n151));
  jor  g109(.dina(n151), .dinb(G21gat), .dout(n152));
  jor  g110(.dina(n138), .dinb(G99gat), .dout(n153));
  jand g111(.dina(n153), .dinb(n152), .dout(n154));
  jand g112(.dina(G223gat), .dinb(G63gat), .dout(n155));
  jor  g113(.dina(n155), .dinb(n73), .dout(n156));
  jor  g114(.dina(n156), .dinb(G73gat), .dout(n157));
  jand g115(.dina(G223gat), .dinb(G24gat), .dout(n158));
  jor  g116(.dina(n158), .dinb(n78), .dout(n159));
  jor  g117(.dina(n159), .dinb(G34gat), .dout(n160));
  jand g118(.dina(n160), .dinb(n157), .dout(n161));
  jnot g119(.din(G108gat), .dout(n162));
  jand g120(.dina(G223gat), .dinb(G102gat), .dout(n163));
  jor  g121(.dina(n163), .dinb(n162), .dout(n164));
  jor  g122(.dina(n164), .dinb(G112gat), .dout(n165));
  jand g123(.dina(n165), .dinb(n161), .dout(n166));
  jand g124(.dina(n166), .dinb(n154), .dout(n167));
  jnot g125(.din(n120), .dout(n168));
  jand g126(.dina(G223gat), .dinb(G76gat), .dout(n169));
  jor  g127(.dina(n169), .dinb(n88), .dout(n170));
  jor  g128(.dina(n170), .dinb(G86gat), .dout(n171));
  jand g129(.dina(G223gat), .dinb(G1gat), .dout(n172));
  jor  g130(.dina(n172), .dinb(n84), .dout(n173));
  jor  g131(.dina(n173), .dinb(G8gat), .dout(n174));
  jand g132(.dina(G223gat), .dinb(n46), .dout(n175));
  jor  g133(.dina(n175), .dinb(n45), .dout(n176));
  jor  g134(.dina(n176), .dinb(G47gat), .dout(n177));
  jand g135(.dina(n177), .dinb(n174), .dout(n178));
  jand g136(.dina(n178), .dinb(n171), .dout(n179));
  jand g137(.dina(n179), .dinb(n168), .dout(n180));
  jand g138(.dina(n180), .dinb(n167), .dout(n181));
  jor  g139(.dina(n181), .dinb(n106), .dout(n182));
  jand g140(.dina(n182), .dinb(n108), .dout(n183));
  jand g141(.dina(n183), .dinb(n149), .dout(n184));
  jnot g142(.din(G66gat), .dout(n185));
  jor  g143(.dina(n181), .dinb(n117), .dout(n186));
  jand g144(.dina(n186), .dinb(n119), .dout(n187));
  jand g145(.dina(n187), .dinb(n185), .dout(n188));
  jor  g146(.dina(n188), .dinb(n184), .dout(n189));
  jnot g147(.din(G14gat), .dout(n190));
  jor  g148(.dina(n181), .dinb(n125), .dout(n191));
  jand g149(.dina(n191), .dinb(n127), .dout(n192));
  jand g150(.dina(n192), .dinb(n190), .dout(n193));
  jnot g151(.din(G92gat), .dout(n194));
  jor  g152(.dina(n181), .dinb(n121), .dout(n195));
  jand g153(.dina(n195), .dinb(n123), .dout(n196));
  jand g154(.dina(n196), .dinb(n194), .dout(n197));
  jor  g155(.dina(n197), .dinb(n193), .dout(n198));
  jor  g156(.dina(n198), .dinb(n189), .dout(n199));
  jnot g157(.din(G79gat), .dout(n200));
  jor  g158(.dina(n181), .dinb(n102), .dout(n201));
  jand g159(.dina(n201), .dinb(n104), .dout(n202));
  jand g160(.dina(n202), .dinb(n200), .dout(n203));
  jnot g161(.din(G115gat), .dout(n204));
  jor  g162(.dina(n181), .dinb(n111), .dout(n205));
  jand g163(.dina(n205), .dinb(n113), .dout(n206));
  jand g164(.dina(n206), .dinb(n204), .dout(n207));
  jor  g165(.dina(n207), .dinb(n203), .dout(n208));
  jnot g166(.din(G27gat), .dout(n209));
  jor  g167(.dina(n181), .dinb(n70), .dout(n210));
  jand g168(.dina(n210), .dinb(n95), .dout(n211));
  jand g169(.dina(n211), .dinb(n209), .dout(n212));
  jor  g170(.dina(n212), .dinb(n208), .dout(n213));
  jor  g171(.dina(n213), .dinb(n199), .dout(n214));
  jor  g172(.dina(n214), .dinb(n148), .dout(G370gat));
  jnot g173(.din(n147), .dout(n216));
  jand g174(.dina(n216), .dinb(n141), .dout(n217));
  jand g175(.dina(G329gat), .dinb(G34gat), .dout(n218));
  jor  g176(.dina(n218), .dinb(n159), .dout(n219));
  jor  g177(.dina(n219), .dinb(G40gat), .dout(n220));
  jnot g178(.din(n119), .dout(n221));
  jand g179(.dina(G329gat), .dinb(G60gat), .dout(n222));
  jor  g180(.dina(n222), .dinb(n221), .dout(n223));
  jor  g181(.dina(n223), .dinb(G66gat), .dout(n224));
  jand g182(.dina(n224), .dinb(n220), .dout(n225));
  jand g183(.dina(G329gat), .dinb(G8gat), .dout(n226));
  jor  g184(.dina(n226), .dinb(n173), .dout(n227));
  jor  g185(.dina(n227), .dinb(G14gat), .dout(n228));
  jand g186(.dina(G329gat), .dinb(G86gat), .dout(n229));
  jor  g187(.dina(n229), .dinb(n170), .dout(n230));
  jor  g188(.dina(n230), .dinb(G92gat), .dout(n231));
  jand g189(.dina(n231), .dinb(n228), .dout(n232));
  jand g190(.dina(n232), .dinb(n225), .dout(n233));
  jand g191(.dina(G329gat), .dinb(G73gat), .dout(n234));
  jor  g192(.dina(n234), .dinb(n156), .dout(n235));
  jor  g193(.dina(n235), .dinb(G79gat), .dout(n236));
  jand g194(.dina(G329gat), .dinb(G112gat), .dout(n237));
  jor  g195(.dina(n237), .dinb(n164), .dout(n238));
  jor  g196(.dina(n238), .dinb(G115gat), .dout(n239));
  jand g197(.dina(n239), .dinb(n236), .dout(n240));
  jand g198(.dina(G329gat), .dinb(G21gat), .dout(n241));
  jor  g199(.dina(n241), .dinb(n151), .dout(n242));
  jor  g200(.dina(n242), .dinb(G27gat), .dout(n243));
  jand g201(.dina(n243), .dinb(n240), .dout(n244));
  jand g202(.dina(n244), .dinb(n233), .dout(n245));
  jand g203(.dina(n245), .dinb(n217), .dout(n246));
  jor  g204(.dina(n246), .dinb(n209), .dout(n247));
  jand g205(.dina(n247), .dinb(n211), .dout(n248));
  jor  g206(.dina(n246), .dinb(n149), .dout(n249));
  jand g207(.dina(n249), .dinb(n183), .dout(n250));
  jor  g208(.dina(n250), .dinb(n248), .dout(n251));
  jor  g209(.dina(n246), .dinb(n145), .dout(n252));
  jand g210(.dina(n144), .dinb(n131), .dout(n253));
  jand g211(.dina(n253), .dinb(n252), .dout(n254));
  jor  g212(.dina(n246), .dinb(n185), .dout(n255));
  jand g213(.dina(G223gat), .dinb(n81), .dout(n256));
  jor  g214(.dina(n222), .dinb(n256), .dout(n257));
  jnot g215(.din(n257), .dout(n258));
  jand g216(.dina(n258), .dinb(n255), .dout(n259));
  jand g217(.dina(n259), .dinb(G56gat), .dout(n260));
  jor  g218(.dina(n260), .dinb(n254), .dout(n261));
  jor  g219(.dina(n261), .dinb(n251), .dout(G430gat));
  jand g220(.dina(G370gat), .dinb(G92gat), .dout(n263));
  jor  g221(.dina(n263), .dinb(n230), .dout(n264));
  jnot g222(.din(n264), .dout(n265));
  jnot g223(.din(n140), .dout(n266));
  jnot g224(.din(G105gat), .dout(n267));
  jor  g225(.dina(n246), .dinb(n267), .dout(n268));
  jand g226(.dina(n268), .dinb(n266), .dout(n269));
  jor  g227(.dina(n246), .dinb(n200), .dout(n270));
  jand g228(.dina(n270), .dinb(n202), .dout(n271));
  jor  g229(.dina(n246), .dinb(n204), .dout(n272));
  jand g230(.dina(n272), .dinb(n206), .dout(n273));
  jor  g231(.dina(n273), .dinb(n271), .dout(n274));
  jor  g232(.dina(n274), .dinb(n269), .dout(n275));
  jor  g233(.dina(n275), .dinb(n265), .dout(n276));
  jor  g234(.dina(n276), .dinb(G430gat), .dout(n277));
  jand g235(.dina(G370gat), .dinb(G14gat), .dout(n278));
  jor  g236(.dina(n278), .dinb(n227), .dout(n279));
  jand g237(.dina(n279), .dinb(n277), .dout(G421gat));
  jnot g238(.din(n250), .dout(n281));
  jand g239(.dina(G370gat), .dinb(G53gat), .dout(n282));
  jnot g240(.din(n253), .dout(n283));
  jor  g241(.dina(n283), .dinb(n282), .dout(n284));
  jand g242(.dina(G370gat), .dinb(G66gat), .dout(n285));
  jor  g243(.dina(n257), .dinb(n285), .dout(n286));
  jor  g244(.dina(n286), .dinb(n80), .dout(n287));
  jand g245(.dina(n287), .dinb(n284), .dout(n288));
  jand g246(.dina(n288), .dinb(n281), .dout(n289));
  jand g247(.dina(n289), .dinb(n271), .dout(n290));
  jand g248(.dina(n265), .dinb(n288), .dout(n291));
  jor  g249(.dina(n291), .dinb(n251), .dout(n292));
  jor  g250(.dina(n292), .dinb(n290), .dout(G431gat));
  jand g251(.dina(n269), .dinb(n264), .dout(n294));
  jor  g252(.dina(n294), .dinb(n254), .dout(n295));
  jand g253(.dina(n295), .dinb(n281), .dout(n296));
  jor  g254(.dina(n296), .dinb(n248), .dout(n297));
  jor  g255(.dina(n297), .dinb(n290), .dout(G432gat));
endmodule


