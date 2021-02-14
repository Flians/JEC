// Benchmark "c1355" written by ABC on Sun May 24 21:14:33 2020

module gf_c1355 ( 
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
    n173, n174, n175, n176, n178, n179, n181, n182, n184, n185, n187, n188,
    n189, n190, n191, n193, n195, n197, n199, n200, n201, n202, n203, n205,
    n207, n209, n211, n212, n214, n216, n218, n220, n221, n222, n223, n224,
    n225, n226, n227, n228, n229, n230, n231, n233, n235, n237, n239, n240,
    n241, n243, n245, n247, n249, n250, n251, n252, n254, n256, n258, n260,
    n261, n263, n265, n267;
  jxor g000(.dina(G85gat), .dinb(G57gat), .dout(n73));
  jxor g001(.dina(G29gat), .dinb(G1gat), .dout(n74));
  jxor g002(.dina(n74), .dinb(n73), .dout(n75));
  jxor g003(.dina(G162gat), .dinb(G155gat), .dout(n76));
  jxor g004(.dina(G148gat), .dinb(G141gat), .dout(n77));
  jxor g005(.dina(n77), .dinb(n76), .dout(n78));
  jxor g006(.dina(n78), .dinb(n75), .dout(n79));
  jand g007(.dina(G233gat), .dinb(G225gat), .dout(n80));
  jnot g008(.din(n80), .dout(n81));
  jxor g009(.dina(G134gat), .dinb(G127gat), .dout(n82));
  jxor g010(.dina(G120gat), .dinb(G113gat), .dout(n83));
  jxor g011(.dina(n83), .dinb(n82), .dout(n84));
  jxor g012(.dina(n84), .dinb(n81), .dout(n85));
  jxor g013(.dina(n85), .dinb(n79), .dout(n86));
  jnot g014(.din(n86), .dout(n87));
  jxor g015(.dina(G218gat), .dinb(G190gat), .dout(n88));
  jxor g016(.dina(G162gat), .dinb(G134gat), .dout(n89));
  jxor g017(.dina(n89), .dinb(n88), .dout(n90));
  jxor g018(.dina(G106gat), .dinb(G99gat), .dout(n91));
  jxor g019(.dina(G92gat), .dinb(G85gat), .dout(n92));
  jxor g020(.dina(n92), .dinb(n91), .dout(n93));
  jxor g021(.dina(n93), .dinb(n90), .dout(n94));
  jnot g022(.din(G232gat), .dout(n95));
  jnot g023(.din(G233gat), .dout(n96));
  jor  g024(.dina(n96), .dinb(n95), .dout(n97));
  jxor g025(.dina(G50gat), .dinb(G43gat), .dout(n98));
  jxor g026(.dina(G36gat), .dinb(G29gat), .dout(n99));
  jxor g027(.dina(n99), .dinb(n98), .dout(n100));
  jxor g028(.dina(n100), .dinb(n97), .dout(n101));
  jxor g029(.dina(n101), .dinb(n94), .dout(n102));
  jxor g030(.dina(G211gat), .dinb(G183gat), .dout(n103));
  jxor g031(.dina(G155gat), .dinb(G127gat), .dout(n104));
  jxor g032(.dina(n104), .dinb(n103), .dout(n105));
  jxor g033(.dina(G78gat), .dinb(G71gat), .dout(n106));
  jxor g034(.dina(G64gat), .dinb(G57gat), .dout(n107));
  jxor g035(.dina(n107), .dinb(n106), .dout(n108));
  jxor g036(.dina(n108), .dinb(n105), .dout(n109));
  jnot g037(.din(G231gat), .dout(n110));
  jor  g038(.dina(n96), .dinb(n110), .dout(n111));
  jxor g039(.dina(G22gat), .dinb(G15gat), .dout(n112));
  jxor g040(.dina(G8gat), .dinb(G1gat), .dout(n113));
  jxor g041(.dina(n113), .dinb(n112), .dout(n114));
  jxor g042(.dina(n114), .dinb(n111), .dout(n115));
  jxor g043(.dina(n115), .dinb(n109), .dout(n116));
  jnot g044(.din(n116), .dout(n117));
  jand g045(.dina(n117), .dinb(n102), .dout(n118));
  jxor g046(.dina(G92gat), .dinb(G64gat), .dout(n119));
  jxor g047(.dina(G36gat), .dinb(G8gat), .dout(n120));
  jxor g048(.dina(n120), .dinb(n119), .dout(n121));
  jxor g049(.dina(G190gat), .dinb(G183gat), .dout(n122));
  jxor g050(.dina(G176gat), .dinb(G169gat), .dout(n123));
  jxor g051(.dina(n123), .dinb(n122), .dout(n124));
  jxor g052(.dina(n124), .dinb(n121), .dout(n125));
  jand g053(.dina(G233gat), .dinb(G226gat), .dout(n126));
  jnot g054(.din(n126), .dout(n127));
  jxor g055(.dina(G218gat), .dinb(G211gat), .dout(n128));
  jxor g056(.dina(G204gat), .dinb(G197gat), .dout(n129));
  jxor g057(.dina(n129), .dinb(n128), .dout(n130));
  jxor g058(.dina(n130), .dinb(n127), .dout(n131));
  jxor g059(.dina(n131), .dinb(n125), .dout(n132));
  jxor g060(.dina(n132), .dinb(n86), .dout(n133));
  jxor g061(.dina(G99gat), .dinb(G71gat), .dout(n134));
  jxor g062(.dina(G43gat), .dinb(G15gat), .dout(n135));
  jxor g063(.dina(n135), .dinb(n134), .dout(n136));
  jxor g064(.dina(n136), .dinb(n124), .dout(n137));
  jnot g065(.din(G227gat), .dout(n138));
  jor  g066(.dina(n96), .dinb(n138), .dout(n139));
  jxor g067(.dina(n139), .dinb(n84), .dout(n140));
  jxor g068(.dina(n140), .dinb(n137), .dout(n141));
  jxor g069(.dina(G106gat), .dinb(G78gat), .dout(n142));
  jxor g070(.dina(G50gat), .dinb(G22gat), .dout(n143));
  jxor g071(.dina(n143), .dinb(n142), .dout(n144));
  jxor g072(.dina(n144), .dinb(n130), .dout(n145));
  jnot g073(.din(G228gat), .dout(n146));
  jor  g074(.dina(n96), .dinb(n146), .dout(n147));
  jxor g075(.dina(n147), .dinb(n78), .dout(n148));
  jxor g076(.dina(n148), .dinb(n145), .dout(n149));
  jand g077(.dina(n149), .dinb(n141), .dout(n150));
  jand g078(.dina(n150), .dinb(n133), .dout(n151));
  jxor g079(.dina(n149), .dinb(n141), .dout(n152));
  jand g080(.dina(n152), .dinb(n86), .dout(n153));
  jand g081(.dina(n153), .dinb(n132), .dout(n154));
  jor  g082(.dina(n154), .dinb(n151), .dout(n155));
  jxor g083(.dina(G197gat), .dinb(G169gat), .dout(n156));
  jxor g084(.dina(G141gat), .dinb(G113gat), .dout(n157));
  jxor g085(.dina(n157), .dinb(n156), .dout(n158));
  jxor g086(.dina(n158), .dinb(n114), .dout(n159));
  jand g087(.dina(G233gat), .dinb(G229gat), .dout(n160));
  jnot g088(.din(n160), .dout(n161));
  jxor g089(.dina(n161), .dinb(n100), .dout(n162));
  jxor g090(.dina(n162), .dinb(n159), .dout(n163));
  jnot g091(.din(n163), .dout(n164));
  jxor g092(.dina(G204gat), .dinb(G176gat), .dout(n165));
  jxor g093(.dina(G148gat), .dinb(G120gat), .dout(n166));
  jxor g094(.dina(n166), .dinb(n165), .dout(n167));
  jxor g095(.dina(n167), .dinb(n108), .dout(n168));
  jand g096(.dina(G233gat), .dinb(G230gat), .dout(n169));
  jnot g097(.din(n169), .dout(n170));
  jxor g098(.dina(n170), .dinb(n93), .dout(n171));
  jxor g099(.dina(n171), .dinb(n168), .dout(n172));
  jand g100(.dina(n172), .dinb(n164), .dout(n173));
  jand g101(.dina(n173), .dinb(n155), .dout(n174));
  jand g102(.dina(n174), .dinb(n118), .dout(n175));
  jand g103(.dina(n175), .dinb(n87), .dout(n176));
  jxor g104(.dina(n176), .dinb(G1gat), .dout(G1324gat));
  jnot g105(.din(n132), .dout(n178));
  jand g106(.dina(n175), .dinb(n178), .dout(n179));
  jxor g107(.dina(n179), .dinb(G8gat), .dout(G1325gat));
  jnot g108(.din(n141), .dout(n181));
  jand g109(.dina(n175), .dinb(n181), .dout(n182));
  jxor g110(.dina(n182), .dinb(G15gat), .dout(G1326gat));
  jnot g111(.din(n149), .dout(n184));
  jand g112(.dina(n175), .dinb(n184), .dout(n185));
  jxor g113(.dina(n185), .dinb(G22gat), .dout(G1327gat));
  jnot g114(.din(n102), .dout(n187));
  jand g115(.dina(n116), .dinb(n187), .dout(n188));
  jand g116(.dina(n188), .dinb(n155), .dout(n189));
  jand g117(.dina(n189), .dinb(n173), .dout(n190));
  jand g118(.dina(n190), .dinb(n87), .dout(n191));
  jxor g119(.dina(n191), .dinb(G29gat), .dout(G1328gat));
  jand g120(.dina(n190), .dinb(n178), .dout(n193));
  jxor g121(.dina(n193), .dinb(G36gat), .dout(G1329gat));
  jand g122(.dina(n190), .dinb(n181), .dout(n195));
  jxor g123(.dina(n195), .dinb(G43gat), .dout(G1330gat));
  jand g124(.dina(n190), .dinb(n184), .dout(n197));
  jxor g125(.dina(n197), .dinb(G50gat), .dout(G1331gat));
  jnot g126(.din(n172), .dout(n199));
  jand g127(.dina(n199), .dinb(n163), .dout(n200));
  jand g128(.dina(n155), .dinb(n118), .dout(n201));
  jand g129(.dina(n201), .dinb(n200), .dout(n202));
  jand g130(.dina(n202), .dinb(n87), .dout(n203));
  jxor g131(.dina(n203), .dinb(G57gat), .dout(G1332gat));
  jand g132(.dina(n202), .dinb(n178), .dout(n205));
  jxor g133(.dina(n205), .dinb(G64gat), .dout(G1333gat));
  jand g134(.dina(n202), .dinb(n181), .dout(n207));
  jxor g135(.dina(n207), .dinb(G71gat), .dout(G1334gat));
  jand g136(.dina(n202), .dinb(n184), .dout(n209));
  jxor g137(.dina(n209), .dinb(G78gat), .dout(G1335gat));
  jand g138(.dina(n200), .dinb(n189), .dout(n211));
  jand g139(.dina(n211), .dinb(n87), .dout(n212));
  jxor g140(.dina(n212), .dinb(G85gat), .dout(G1336gat));
  jand g141(.dina(n211), .dinb(n178), .dout(n214));
  jxor g142(.dina(n214), .dinb(G92gat), .dout(G1337gat));
  jand g143(.dina(n211), .dinb(n181), .dout(n216));
  jxor g144(.dina(n216), .dinb(G99gat), .dout(G1338gat));
  jand g145(.dina(n211), .dinb(n184), .dout(n218));
  jxor g146(.dina(n218), .dinb(G106gat), .dout(G1339gat));
  jand g147(.dina(n149), .dinb(n181), .dout(n220));
  jand g148(.dina(n132), .dinb(n87), .dout(n221));
  jxor g149(.dina(n116), .dinb(n102), .dout(n222));
  jand g150(.dina(n222), .dinb(n163), .dout(n223));
  jand g151(.dina(n223), .dinb(n172), .dout(n224));
  jxor g152(.dina(n172), .dinb(n163), .dout(n225));
  jand g153(.dina(n116), .dinb(n102), .dout(n226));
  jand g154(.dina(n226), .dinb(n225), .dout(n227));
  jor  g155(.dina(n227), .dinb(n224), .dout(n228));
  jand g156(.dina(n228), .dinb(n221), .dout(n229));
  jand g157(.dina(n229), .dinb(n220), .dout(n230));
  jand g158(.dina(n230), .dinb(n164), .dout(n231));
  jxor g159(.dina(n231), .dinb(G113gat), .dout(G1340gat));
  jand g160(.dina(n230), .dinb(n199), .dout(n233));
  jxor g161(.dina(n233), .dinb(G120gat), .dout(G1341gat));
  jand g162(.dina(n230), .dinb(n117), .dout(n235));
  jxor g163(.dina(n235), .dinb(G127gat), .dout(G1342gat));
  jand g164(.dina(n230), .dinb(n187), .dout(n237));
  jxor g165(.dina(n237), .dinb(G134gat), .dout(G1343gat));
  jand g166(.dina(n184), .dinb(n141), .dout(n239));
  jand g167(.dina(n229), .dinb(n239), .dout(n240));
  jand g168(.dina(n240), .dinb(n164), .dout(n241));
  jxor g169(.dina(n241), .dinb(G141gat), .dout(G1344gat));
  jand g170(.dina(n240), .dinb(n199), .dout(n243));
  jxor g171(.dina(n243), .dinb(G148gat), .dout(G1345gat));
  jand g172(.dina(n240), .dinb(n117), .dout(n245));
  jxor g173(.dina(n245), .dinb(G155gat), .dout(G1346gat));
  jand g174(.dina(n240), .dinb(n187), .dout(n247));
  jxor g175(.dina(n247), .dinb(G162gat), .dout(G1347gat));
  jand g176(.dina(n178), .dinb(n86), .dout(n249));
  jand g177(.dina(n228), .dinb(n249), .dout(n250));
  jand g178(.dina(n250), .dinb(n220), .dout(n251));
  jand g179(.dina(n251), .dinb(n164), .dout(n252));
  jxor g180(.dina(n252), .dinb(G169gat), .dout(G1348gat));
  jand g181(.dina(n251), .dinb(n199), .dout(n254));
  jxor g182(.dina(n254), .dinb(G176gat), .dout(G1349gat));
  jand g183(.dina(n251), .dinb(n117), .dout(n256));
  jxor g184(.dina(n256), .dinb(G183gat), .dout(G1350gat));
  jand g185(.dina(n251), .dinb(n187), .dout(n258));
  jxor g186(.dina(n258), .dinb(G190gat), .dout(G1351gat));
  jand g187(.dina(n250), .dinb(n239), .dout(n260));
  jand g188(.dina(n260), .dinb(n164), .dout(n261));
  jxor g189(.dina(n261), .dinb(G197gat), .dout(G1352gat));
  jand g190(.dina(n260), .dinb(n199), .dout(n263));
  jxor g191(.dina(n263), .dinb(G204gat), .dout(G1353gat));
  jand g192(.dina(n260), .dinb(n117), .dout(n265));
  jxor g193(.dina(n265), .dinb(G211gat), .dout(G1354gat));
  jand g194(.dina(n260), .dinb(n187), .dout(n267));
  jxor g195(.dina(n267), .dinb(G218gat), .dout(G1355gat));
endmodule


