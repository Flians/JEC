// Benchmark "c1355" written by ABC on Sun May 24 21:31:58 2020

module rf_c1355 ( 
    G1gat, G8gat, G15gat, G22gat, G29gat, G36gat, G43gat, G50gat, G57gat,
    G64gat, G71gat, G78gat, G85gat, G92gat, G99gat, G106gat, G113gat,
    G120gat, G127gat, G134gat, G141gat, G148gat, G155gat, G162gat, G169gat,
    G176gat, G183gat, G190gat, G197gat, G204gat, G211gat, G218gat, G225gat,
    G226gat, G227gat, G228gat, G229gat, G230gat, G231gat, G232gat, G233gat,
    G1324gat, G1325gat, G1326gat, G1327gat, G1328gat, G1329gat, G1330gat,
    G1331gat, G1332gat, G1333gat, G1334gat, G1335gat, G1336gat, G1337gat,
    G1338gat, G1339gat, G1340gat, G1341gat, G1342gat, G1343gat, G1344gat,
    G1345gat, G1346gat, G1347gat, G1348gat, G1349gat, G1350gat, G1351gat,
    G1352gat, G1353gat, G1354gat, G1355gat  );
  input  G1gat, G8gat, G15gat, G22gat, G29gat, G36gat, G43gat, G50gat,
    G57gat, G64gat, G71gat, G78gat, G85gat, G92gat, G99gat, G106gat,
    G113gat, G120gat, G127gat, G134gat, G141gat, G148gat, G155gat, G162gat,
    G169gat, G176gat, G183gat, G190gat, G197gat, G204gat, G211gat, G218gat,
    G225gat, G226gat, G227gat, G228gat, G229gat, G230gat, G231gat, G232gat,
    G233gat;
  output G1324gat, G1325gat, G1326gat, G1327gat, G1328gat, G1329gat, G1330gat,
    G1331gat, G1332gat, G1333gat, G1334gat, G1335gat, G1336gat, G1337gat,
    G1338gat, G1339gat, G1340gat, G1341gat, G1342gat, G1343gat, G1344gat,
    G1345gat, G1346gat, G1347gat, G1348gat, G1349gat, G1350gat, G1351gat,
    G1352gat, G1353gat, G1354gat, G1355gat;
  wire n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
    n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
    n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111, n112,
    n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123, n124,
    n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135, n136,
    n137, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147, n148,
    n149, n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
    n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171, n172,
    n173, n174, n176, n177, n178, n179, n181, n182, n183, n184, n186, n187,
    n188, n189, n191, n192, n193, n194, n195, n196, n197, n198, n199, n200,
    n201, n203, n205, n207, n209, n210, n211, n212, n213, n214, n215, n216,
    n217, n218, n219, n221, n223, n225, n227, n228, n229, n231, n233, n235,
    n237, n238, n239, n240, n241, n242, n243, n244, n245, n246, n247, n248,
    n250, n252, n254, n256, n257, n258, n259, n261, n263, n265, n267, n268,
    n269, n270, n272, n274, n276, n278, n279, n280, n282, n284, n286;
  jand g000(.dina(G233gat), .dinb(G225gat), .dout(n73));
  jxor g001(.dina(G134gat), .dinb(G127gat), .dout(n74));
  jxor g002(.dina(G120gat), .dinb(G113gat), .dout(n75));
  jxor g003(.dina(n75), .dinb(n74), .dout(n76));
  jxor g004(.dina(n76), .dinb(n73), .dout(n77));
  jxor g005(.dina(G85gat), .dinb(G57gat), .dout(n78));
  jxor g006(.dina(G29gat), .dinb(G1gat), .dout(n79));
  jxor g007(.dina(n79), .dinb(n78), .dout(n80));
  jxor g008(.dina(G162gat), .dinb(G155gat), .dout(n81));
  jxor g009(.dina(G148gat), .dinb(G141gat), .dout(n82));
  jxor g010(.dina(n82), .dinb(n81), .dout(n83));
  jxor g011(.dina(n83), .dinb(n80), .dout(n84));
  jxor g012(.dina(n84), .dinb(n77), .dout(n85));
  jnot g013(.din(G225gat), .dout(n86));
  jnot g014(.din(G233gat), .dout(n87));
  jor  g015(.dina(n87), .dinb(n86), .dout(n88));
  jxor g016(.dina(n76), .dinb(n88), .dout(n89));
  jxor g017(.dina(n84), .dinb(n89), .dout(n90));
  jnot g018(.din(G226gat), .dout(n91));
  jor  g019(.dina(n87), .dinb(n91), .dout(n92));
  jxor g020(.dina(G218gat), .dinb(G211gat), .dout(n93));
  jxor g021(.dina(G204gat), .dinb(G197gat), .dout(n94));
  jxor g022(.dina(n94), .dinb(n93), .dout(n95));
  jxor g023(.dina(n95), .dinb(n92), .dout(n96));
  jxor g024(.dina(G190gat), .dinb(G183gat), .dout(n97));
  jxor g025(.dina(G176gat), .dinb(G169gat), .dout(n98));
  jxor g026(.dina(n98), .dinb(n97), .dout(n99));
  jxor g027(.dina(G92gat), .dinb(G64gat), .dout(n100));
  jxor g028(.dina(G36gat), .dinb(G8gat), .dout(n101));
  jxor g029(.dina(n101), .dinb(n100), .dout(n102));
  jxor g030(.dina(n102), .dinb(n99), .dout(n103));
  jxor g031(.dina(n103), .dinb(n96), .dout(n104));
  jxor g032(.dina(n104), .dinb(n90), .dout(n105));
  jnot g033(.din(G227gat), .dout(n106));
  jor  g034(.dina(n87), .dinb(n106), .dout(n107));
  jxor g035(.dina(n107), .dinb(n76), .dout(n108));
  jxor g036(.dina(G99gat), .dinb(G71gat), .dout(n109));
  jxor g037(.dina(G43gat), .dinb(G15gat), .dout(n110));
  jxor g038(.dina(n110), .dinb(n109), .dout(n111));
  jxor g039(.dina(n111), .dinb(n99), .dout(n112));
  jxor g040(.dina(n112), .dinb(n108), .dout(n113));
  jnot g041(.din(G228gat), .dout(n114));
  jor  g042(.dina(n87), .dinb(n114), .dout(n115));
  jxor g043(.dina(n115), .dinb(n83), .dout(n116));
  jxor g044(.dina(G106gat), .dinb(G78gat), .dout(n117));
  jxor g045(.dina(G50gat), .dinb(G22gat), .dout(n118));
  jxor g046(.dina(n118), .dinb(n117), .dout(n119));
  jxor g047(.dina(n119), .dinb(n95), .dout(n120));
  jxor g048(.dina(n120), .dinb(n116), .dout(n121));
  jand g049(.dina(n121), .dinb(n113), .dout(n122));
  jand g050(.dina(n122), .dinb(n105), .dout(n123));
  jxor g051(.dina(n121), .dinb(n113), .dout(n124));
  jand g052(.dina(n104), .dinb(n90), .dout(n125));
  jand g053(.dina(n125), .dinb(n124), .dout(n126));
  jor  g054(.dina(n126), .dinb(n123), .dout(n127));
  jand g055(.dina(G233gat), .dinb(G229gat), .dout(n128));
  jxor g056(.dina(G50gat), .dinb(G43gat), .dout(n129));
  jxor g057(.dina(G36gat), .dinb(G29gat), .dout(n130));
  jxor g058(.dina(n130), .dinb(n129), .dout(n131));
  jxor g059(.dina(n131), .dinb(n128), .dout(n132));
  jxor g060(.dina(G22gat), .dinb(G15gat), .dout(n133));
  jxor g061(.dina(G8gat), .dinb(G1gat), .dout(n134));
  jxor g062(.dina(n134), .dinb(n133), .dout(n135));
  jxor g063(.dina(G197gat), .dinb(G169gat), .dout(n136));
  jxor g064(.dina(G141gat), .dinb(G113gat), .dout(n137));
  jxor g065(.dina(n137), .dinb(n136), .dout(n138));
  jxor g066(.dina(n138), .dinb(n135), .dout(n139));
  jxor g067(.dina(n139), .dinb(n132), .dout(n140));
  jnot g068(.din(G230gat), .dout(n141));
  jor  g069(.dina(n87), .dinb(n141), .dout(n142));
  jxor g070(.dina(G106gat), .dinb(G99gat), .dout(n143));
  jxor g071(.dina(G92gat), .dinb(G85gat), .dout(n144));
  jxor g072(.dina(n144), .dinb(n143), .dout(n145));
  jxor g073(.dina(n145), .dinb(n142), .dout(n146));
  jxor g074(.dina(G78gat), .dinb(G71gat), .dout(n147));
  jxor g075(.dina(G64gat), .dinb(G57gat), .dout(n148));
  jxor g076(.dina(n148), .dinb(n147), .dout(n149));
  jxor g077(.dina(G204gat), .dinb(G176gat), .dout(n150));
  jxor g078(.dina(G148gat), .dinb(G120gat), .dout(n151));
  jxor g079(.dina(n151), .dinb(n150), .dout(n152));
  jxor g080(.dina(n152), .dinb(n149), .dout(n153));
  jxor g081(.dina(n153), .dinb(n146), .dout(n154));
  jand g082(.dina(n154), .dinb(n140), .dout(n155));
  jnot g083(.din(G232gat), .dout(n156));
  jor  g084(.dina(n87), .dinb(n156), .dout(n157));
  jxor g085(.dina(n157), .dinb(n131), .dout(n158));
  jxor g086(.dina(G218gat), .dinb(G190gat), .dout(n159));
  jxor g087(.dina(G162gat), .dinb(G134gat), .dout(n160));
  jxor g088(.dina(n160), .dinb(n159), .dout(n161));
  jxor g089(.dina(n161), .dinb(n145), .dout(n162));
  jxor g090(.dina(n162), .dinb(n158), .dout(n163));
  jand g091(.dina(G233gat), .dinb(G231gat), .dout(n164));
  jxor g092(.dina(n164), .dinb(n135), .dout(n165));
  jxor g093(.dina(G211gat), .dinb(G183gat), .dout(n166));
  jxor g094(.dina(G155gat), .dinb(G127gat), .dout(n167));
  jxor g095(.dina(n167), .dinb(n166), .dout(n168));
  jxor g096(.dina(n168), .dinb(n149), .dout(n169));
  jxor g097(.dina(n169), .dinb(n165), .dout(n170));
  jand g098(.dina(n170), .dinb(n163), .dout(n171));
  jand g099(.dina(n171), .dinb(n155), .dout(n172));
  jand g100(.dina(n172), .dinb(n127), .dout(n173));
  jand g101(.dina(n173), .dinb(n85), .dout(n174));
  jxor g102(.dina(n174), .dinb(G1gat), .dout(G1324gat));
  jand g103(.dina(G233gat), .dinb(G226gat), .dout(n176));
  jxor g104(.dina(n95), .dinb(n176), .dout(n177));
  jxor g105(.dina(n103), .dinb(n177), .dout(n178));
  jand g106(.dina(n173), .dinb(n178), .dout(n179));
  jxor g107(.dina(n179), .dinb(G8gat), .dout(G1325gat));
  jand g108(.dina(G233gat), .dinb(G227gat), .dout(n181));
  jxor g109(.dina(n181), .dinb(n76), .dout(n182));
  jxor g110(.dina(n112), .dinb(n182), .dout(n183));
  jand g111(.dina(n173), .dinb(n183), .dout(n184));
  jxor g112(.dina(n184), .dinb(G15gat), .dout(G1326gat));
  jand g113(.dina(G233gat), .dinb(G228gat), .dout(n186));
  jxor g114(.dina(n186), .dinb(n83), .dout(n187));
  jxor g115(.dina(n120), .dinb(n187), .dout(n188));
  jand g116(.dina(n173), .dinb(n188), .dout(n189));
  jxor g117(.dina(n189), .dinb(G22gat), .dout(G1327gat));
  jand g118(.dina(G233gat), .dinb(G232gat), .dout(n191));
  jxor g119(.dina(n191), .dinb(n131), .dout(n192));
  jxor g120(.dina(n162), .dinb(n192), .dout(n193));
  jnot g121(.din(G231gat), .dout(n194));
  jor  g122(.dina(n87), .dinb(n194), .dout(n195));
  jxor g123(.dina(n195), .dinb(n135), .dout(n196));
  jxor g124(.dina(n169), .dinb(n196), .dout(n197));
  jand g125(.dina(n197), .dinb(n193), .dout(n198));
  jand g126(.dina(n198), .dinb(n155), .dout(n199));
  jand g127(.dina(n199), .dinb(n127), .dout(n200));
  jand g128(.dina(n200), .dinb(n85), .dout(n201));
  jxor g129(.dina(n201), .dinb(G29gat), .dout(G1328gat));
  jand g130(.dina(n200), .dinb(n178), .dout(n203));
  jxor g131(.dina(n203), .dinb(G36gat), .dout(G1329gat));
  jand g132(.dina(n200), .dinb(n183), .dout(n205));
  jxor g133(.dina(n205), .dinb(G43gat), .dout(G1330gat));
  jand g134(.dina(n200), .dinb(n188), .dout(n207));
  jxor g135(.dina(n207), .dinb(G50gat), .dout(G1331gat));
  jnot g136(.din(G229gat), .dout(n209));
  jor  g137(.dina(n87), .dinb(n209), .dout(n210));
  jxor g138(.dina(n131), .dinb(n210), .dout(n211));
  jxor g139(.dina(n139), .dinb(n211), .dout(n212));
  jand g140(.dina(G233gat), .dinb(G230gat), .dout(n213));
  jxor g141(.dina(n145), .dinb(n213), .dout(n214));
  jxor g142(.dina(n153), .dinb(n214), .dout(n215));
  jand g143(.dina(n215), .dinb(n212), .dout(n216));
  jand g144(.dina(n216), .dinb(n171), .dout(n217));
  jand g145(.dina(n217), .dinb(n127), .dout(n218));
  jand g146(.dina(n218), .dinb(n85), .dout(n219));
  jxor g147(.dina(n219), .dinb(G57gat), .dout(G1332gat));
  jand g148(.dina(n218), .dinb(n178), .dout(n221));
  jxor g149(.dina(n221), .dinb(G64gat), .dout(G1333gat));
  jand g150(.dina(n218), .dinb(n183), .dout(n223));
  jxor g151(.dina(n223), .dinb(G71gat), .dout(G1334gat));
  jand g152(.dina(n218), .dinb(n188), .dout(n225));
  jxor g153(.dina(n225), .dinb(G78gat), .dout(G1335gat));
  jand g154(.dina(n216), .dinb(n198), .dout(n227));
  jand g155(.dina(n227), .dinb(n127), .dout(n228));
  jand g156(.dina(n228), .dinb(n85), .dout(n229));
  jxor g157(.dina(n229), .dinb(G85gat), .dout(G1336gat));
  jand g158(.dina(n228), .dinb(n178), .dout(n231));
  jxor g159(.dina(n231), .dinb(G92gat), .dout(G1337gat));
  jand g160(.dina(n228), .dinb(n183), .dout(n233));
  jxor g161(.dina(n233), .dinb(G99gat), .dout(G1338gat));
  jand g162(.dina(n228), .dinb(n188), .dout(n235));
  jxor g163(.dina(n235), .dinb(G106gat), .dout(G1339gat));
  jxor g164(.dina(n154), .dinb(n212), .dout(n237));
  jand g165(.dina(n197), .dinb(n163), .dout(n238));
  jand g166(.dina(n238), .dinb(n237), .dout(n239));
  jxor g167(.dina(n197), .dinb(n163), .dout(n240));
  jand g168(.dina(n154), .dinb(n212), .dout(n241));
  jand g169(.dina(n241), .dinb(n240), .dout(n242));
  jor  g170(.dina(n242), .dinb(n239), .dout(n243));
  jand g171(.dina(n104), .dinb(n85), .dout(n244));
  jand g172(.dina(n121), .dinb(n183), .dout(n245));
  jand g173(.dina(n245), .dinb(n244), .dout(n246));
  jand g174(.dina(n246), .dinb(n243), .dout(n247));
  jand g175(.dina(n247), .dinb(n140), .dout(n248));
  jxor g176(.dina(n248), .dinb(G113gat), .dout(G1340gat));
  jand g177(.dina(n247), .dinb(n215), .dout(n250));
  jxor g178(.dina(n250), .dinb(G120gat), .dout(G1341gat));
  jand g179(.dina(n247), .dinb(n170), .dout(n252));
  jxor g180(.dina(n252), .dinb(G127gat), .dout(G1342gat));
  jand g181(.dina(n247), .dinb(n193), .dout(n254));
  jxor g182(.dina(n254), .dinb(G134gat), .dout(G1343gat));
  jand g183(.dina(n188), .dinb(n113), .dout(n256));
  jand g184(.dina(n256), .dinb(n244), .dout(n257));
  jand g185(.dina(n257), .dinb(n243), .dout(n258));
  jand g186(.dina(n258), .dinb(n140), .dout(n259));
  jxor g187(.dina(n259), .dinb(G141gat), .dout(G1344gat));
  jand g188(.dina(n258), .dinb(n215), .dout(n261));
  jxor g189(.dina(n261), .dinb(G148gat), .dout(G1345gat));
  jand g190(.dina(n258), .dinb(n170), .dout(n263));
  jxor g191(.dina(n263), .dinb(G155gat), .dout(G1346gat));
  jand g192(.dina(n258), .dinb(n193), .dout(n265));
  jxor g193(.dina(n265), .dinb(G162gat), .dout(G1347gat));
  jand g194(.dina(n178), .dinb(n90), .dout(n267));
  jand g195(.dina(n245), .dinb(n267), .dout(n268));
  jand g196(.dina(n268), .dinb(n243), .dout(n269));
  jand g197(.dina(n269), .dinb(n140), .dout(n270));
  jxor g198(.dina(n270), .dinb(G169gat), .dout(G1348gat));
  jand g199(.dina(n269), .dinb(n215), .dout(n272));
  jxor g200(.dina(n272), .dinb(G176gat), .dout(G1349gat));
  jand g201(.dina(n269), .dinb(n170), .dout(n274));
  jxor g202(.dina(n274), .dinb(G183gat), .dout(G1350gat));
  jand g203(.dina(n269), .dinb(n193), .dout(n276));
  jxor g204(.dina(n276), .dinb(G190gat), .dout(G1351gat));
  jand g205(.dina(n256), .dinb(n267), .dout(n278));
  jand g206(.dina(n278), .dinb(n243), .dout(n279));
  jand g207(.dina(n279), .dinb(n140), .dout(n280));
  jxor g208(.dina(n280), .dinb(G197gat), .dout(G1352gat));
  jand g209(.dina(n279), .dinb(n215), .dout(n282));
  jxor g210(.dina(n282), .dinb(G204gat), .dout(G1353gat));
  jand g211(.dina(n279), .dinb(n170), .dout(n284));
  jxor g212(.dina(n284), .dinb(G211gat), .dout(G1354gat));
  jand g213(.dina(n279), .dinb(n193), .dout(n286));
  jxor g214(.dina(n286), .dinb(G218gat), .dout(G1355gat));
endmodule


