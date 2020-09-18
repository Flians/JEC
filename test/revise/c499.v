// Benchmark "c499" written by ABC on Sun May 24 21:38:00 2020

module rf_c499 ( 
    Gid0, Gid1, Gid2, Gid3, Gid4, Gid5, Gid6, Gid7, Gid8, Gid9, Gid10,
    Gid11, Gid12, Gid13, Gid14, Gid15, Gid16, Gid17, Gid18, Gid19, Gid20,
    Gid21, Gid22, Gid23, Gid24, Gid25, Gid26, Gid27, Gid28, Gid29, Gid30,
    Gid31, Gic0, Gic1, Gic2, Gic3, Gic4, Gic5, Gic6, Gic7, Gr,
    God0, God1, God2, God3, God4, God5, God6, God7, God8, God9, God10,
    God11, God12, God13, God14, God15, God16, God17, God18, God19, God20,
    God21, God22, God23, God24, God25, God26, God27, God28, God29, God30,
    God31  );
  input  Gid0, Gid1, Gid2, Gid3, Gid4, Gid5, Gid6, Gid7, Gid8, Gid9,
    Gid10, Gid11, Gid12, Gid13, Gid14, Gid15, Gid16, Gid17, Gid18, Gid19,
    Gid20, Gid21, Gid22, Gid23, Gid24, Gid25, Gid26, Gid27, Gid28, Gid29,
    Gid30, Gid31, Gic0, Gic1, Gic2, Gic3, Gic4, Gic5, Gic6, Gic7, Gr;
  output God0, God1, God2, God3, God4, God5, God6, God7, God8, God9, God10,
    God11, God12, God13, God14, God15, God16, God17, God18, God19, God20,
    God21, God22, God23, God24, God25, God26, God27, God28, God29, God30,
    God31;
  wire n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
    n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
    n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111, n112,
    n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123, n124,
    n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135, n136,
    n137, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147, n148,
    n149, n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
    n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171, n172,
    n173, n174, n175, n176, n178, n179, n181, n182, n184, n185, n187, n188,
    n189, n190, n192, n194, n196, n198, n199, n200, n201, n202, n204, n206,
    n208, n210, n211, n212, n214, n216, n218, n220, n221, n222, n223, n224,
    n225, n226, n227, n228, n229, n230, n231, n233, n235, n237, n239, n240,
    n241, n242, n244, n246, n248, n250, n251, n252, n254, n256, n258, n260,
    n261, n263, n265, n267;
  jnot g000(.din(Gic0), .dout(n73));
  jnot g001(.din(Gr), .dout(n74));
  jor  g002(.dina(n74), .dinb(n73), .dout(n75));
  jxor g003(.dina(Gid17), .dinb(Gid16), .dout(n76));
  jxor g004(.dina(Gid19), .dinb(Gid18), .dout(n77));
  jxor g005(.dina(n77), .dinb(n76), .dout(n78));
  jxor g006(.dina(n78), .dinb(n75), .dout(n79));
  jxor g007(.dina(Gid4), .dinb(Gid0), .dout(n80));
  jxor g008(.dina(Gid12), .dinb(Gid8), .dout(n81));
  jxor g009(.dina(n81), .dinb(n80), .dout(n82));
  jxor g010(.dina(Gid21), .dinb(Gid20), .dout(n83));
  jxor g011(.dina(Gid23), .dinb(Gid22), .dout(n84));
  jxor g012(.dina(n84), .dinb(n83), .dout(n85));
  jxor g013(.dina(n85), .dinb(n82), .dout(n86));
  jxor g014(.dina(n86), .dinb(n79), .dout(n87));
  jnot g015(.din(n87), .dout(n88));
  jnot g016(.din(Gic7), .dout(n89));
  jor  g017(.dina(n74), .dinb(n89), .dout(n90));
  jxor g018(.dina(Gid5), .dinb(Gid4), .dout(n91));
  jxor g019(.dina(Gid7), .dinb(Gid6), .dout(n92));
  jxor g020(.dina(n92), .dinb(n91), .dout(n93));
  jxor g021(.dina(n93), .dinb(n90), .dout(n94));
  jxor g022(.dina(Gid13), .dinb(Gid12), .dout(n95));
  jxor g023(.dina(Gid15), .dinb(Gid14), .dout(n96));
  jxor g024(.dina(n96), .dinb(n95), .dout(n97));
  jxor g025(.dina(Gid23), .dinb(Gid19), .dout(n98));
  jxor g026(.dina(Gid31), .dinb(Gid27), .dout(n99));
  jxor g027(.dina(n99), .dinb(n98), .dout(n100));
  jxor g028(.dina(n100), .dinb(n97), .dout(n101));
  jxor g029(.dina(n101), .dinb(n94), .dout(n102));
  jnot g030(.din(Gic6), .dout(n103));
  jor  g031(.dina(n74), .dinb(n103), .dout(n104));
  jxor g032(.dina(Gid1), .dinb(Gid0), .dout(n105));
  jxor g033(.dina(Gid3), .dinb(Gid2), .dout(n106));
  jxor g034(.dina(n106), .dinb(n105), .dout(n107));
  jxor g035(.dina(n107), .dinb(n104), .dout(n108));
  jxor g036(.dina(Gid9), .dinb(Gid8), .dout(n109));
  jxor g037(.dina(Gid11), .dinb(Gid10), .dout(n110));
  jxor g038(.dina(n110), .dinb(n109), .dout(n111));
  jxor g039(.dina(Gid22), .dinb(Gid18), .dout(n112));
  jxor g040(.dina(Gid30), .dinb(Gid26), .dout(n113));
  jxor g041(.dina(n113), .dinb(n112), .dout(n114));
  jxor g042(.dina(n114), .dinb(n111), .dout(n115));
  jxor g043(.dina(n115), .dinb(n108), .dout(n116));
  jnot g044(.din(n116), .dout(n117));
  jand g045(.dina(n117), .dinb(n102), .dout(n118));
  jnot g046(.din(Gic4), .dout(n119));
  jor  g047(.dina(n74), .dinb(n119), .dout(n120));
  jxor g048(.dina(n120), .dinb(n93), .dout(n121));
  jxor g049(.dina(Gid20), .dinb(Gid16), .dout(n122));
  jxor g050(.dina(Gid28), .dinb(Gid24), .dout(n123));
  jxor g051(.dina(n123), .dinb(n122), .dout(n124));
  jxor g052(.dina(n124), .dinb(n107), .dout(n125));
  jxor g053(.dina(n125), .dinb(n121), .dout(n126));
  jnot g054(.din(n126), .dout(n127));
  jnot g055(.din(Gic5), .dout(n128));
  jor  g056(.dina(n74), .dinb(n128), .dout(n129));
  jxor g057(.dina(n129), .dinb(n97), .dout(n130));
  jxor g058(.dina(Gid21), .dinb(Gid17), .dout(n131));
  jxor g059(.dina(Gid29), .dinb(Gid25), .dout(n132));
  jxor g060(.dina(n132), .dinb(n131), .dout(n133));
  jxor g061(.dina(n133), .dinb(n111), .dout(n134));
  jxor g062(.dina(n134), .dinb(n130), .dout(n135));
  jand g063(.dina(n135), .dinb(n127), .dout(n136));
  jnot g064(.din(Gic1), .dout(n137));
  jor  g065(.dina(n74), .dinb(n137), .dout(n138));
  jxor g066(.dina(Gid29), .dinb(Gid28), .dout(n139));
  jxor g067(.dina(Gid31), .dinb(Gid30), .dout(n140));
  jxor g068(.dina(n140), .dinb(n139), .dout(n141));
  jxor g069(.dina(n141), .dinb(n138), .dout(n142));
  jxor g070(.dina(Gid25), .dinb(Gid24), .dout(n143));
  jxor g071(.dina(Gid27), .dinb(Gid26), .dout(n144));
  jxor g072(.dina(n144), .dinb(n143), .dout(n145));
  jxor g073(.dina(Gid5), .dinb(Gid1), .dout(n146));
  jxor g074(.dina(Gid13), .dinb(Gid9), .dout(n147));
  jxor g075(.dina(n147), .dinb(n146), .dout(n148));
  jxor g076(.dina(n148), .dinb(n145), .dout(n149));
  jxor g077(.dina(n149), .dinb(n142), .dout(n150));
  jxor g078(.dina(n150), .dinb(n87), .dout(n151));
  jnot g079(.din(Gic3), .dout(n152));
  jor  g080(.dina(n74), .dinb(n152), .dout(n153));
  jxor g081(.dina(n153), .dinb(n85), .dout(n154));
  jxor g082(.dina(Gid7), .dinb(Gid3), .dout(n155));
  jxor g083(.dina(Gid15), .dinb(Gid11), .dout(n156));
  jxor g084(.dina(n156), .dinb(n155), .dout(n157));
  jxor g085(.dina(n157), .dinb(n141), .dout(n158));
  jxor g086(.dina(n158), .dinb(n154), .dout(n159));
  jnot g087(.din(Gic2), .dout(n160));
  jor  g088(.dina(n74), .dinb(n160), .dout(n161));
  jxor g089(.dina(n161), .dinb(n78), .dout(n162));
  jxor g090(.dina(Gid6), .dinb(Gid2), .dout(n163));
  jxor g091(.dina(Gid14), .dinb(Gid10), .dout(n164));
  jxor g092(.dina(n164), .dinb(n163), .dout(n165));
  jxor g093(.dina(n165), .dinb(n145), .dout(n166));
  jxor g094(.dina(n166), .dinb(n162), .dout(n167));
  jand g095(.dina(n167), .dinb(n159), .dout(n168));
  jand g096(.dina(n168), .dinb(n151), .dout(n169));
  jxor g097(.dina(n167), .dinb(n159), .dout(n170));
  jand g098(.dina(n150), .dinb(n87), .dout(n171));
  jand g099(.dina(n171), .dinb(n170), .dout(n172));
  jor  g100(.dina(n172), .dinb(n169), .dout(n173));
  jand g101(.dina(n173), .dinb(n136), .dout(n174));
  jand g102(.dina(n174), .dinb(n118), .dout(n175));
  jand g103(.dina(n175), .dinb(n88), .dout(n176));
  jxor g104(.dina(n176), .dinb(Gid0), .dout(God0));
  jnot g105(.din(n150), .dout(n178));
  jand g106(.dina(n175), .dinb(n178), .dout(n179));
  jxor g107(.dina(n179), .dinb(Gid1), .dout(God1));
  jnot g108(.din(n167), .dout(n181));
  jand g109(.dina(n175), .dinb(n181), .dout(n182));
  jxor g110(.dina(n182), .dinb(Gid2), .dout(God2));
  jnot g111(.din(n159), .dout(n184));
  jand g112(.dina(n175), .dinb(n184), .dout(n185));
  jxor g113(.dina(n185), .dinb(Gid3), .dout(God3));
  jnot g114(.din(n102), .dout(n187));
  jand g115(.dina(n116), .dinb(n187), .dout(n188));
  jand g116(.dina(n188), .dinb(n174), .dout(n189));
  jand g117(.dina(n189), .dinb(n88), .dout(n190));
  jxor g118(.dina(n190), .dinb(Gid4), .dout(God4));
  jand g119(.dina(n189), .dinb(n178), .dout(n192));
  jxor g120(.dina(n192), .dinb(Gid5), .dout(God5));
  jand g121(.dina(n189), .dinb(n181), .dout(n194));
  jxor g122(.dina(n194), .dinb(Gid6), .dout(God6));
  jand g123(.dina(n189), .dinb(n184), .dout(n196));
  jxor g124(.dina(n196), .dinb(Gid7), .dout(God7));
  jnot g125(.din(n135), .dout(n198));
  jand g126(.dina(n198), .dinb(n126), .dout(n199));
  jand g127(.dina(n199), .dinb(n118), .dout(n200));
  jand g128(.dina(n200), .dinb(n173), .dout(n201));
  jand g129(.dina(n201), .dinb(n88), .dout(n202));
  jxor g130(.dina(n202), .dinb(Gid8), .dout(God8));
  jand g131(.dina(n201), .dinb(n178), .dout(n204));
  jxor g132(.dina(n204), .dinb(Gid9), .dout(God9));
  jand g133(.dina(n201), .dinb(n181), .dout(n206));
  jxor g134(.dina(n206), .dinb(Gid10), .dout(God10));
  jand g135(.dina(n201), .dinb(n184), .dout(n208));
  jxor g136(.dina(n208), .dinb(Gid11), .dout(God11));
  jand g137(.dina(n199), .dinb(n188), .dout(n210));
  jand g138(.dina(n210), .dinb(n173), .dout(n211));
  jand g139(.dina(n211), .dinb(n88), .dout(n212));
  jxor g140(.dina(n212), .dinb(Gid12), .dout(God12));
  jand g141(.dina(n211), .dinb(n178), .dout(n214));
  jxor g142(.dina(n214), .dinb(Gid13), .dout(God13));
  jand g143(.dina(n211), .dinb(n181), .dout(n216));
  jxor g144(.dina(n216), .dinb(Gid14), .dout(God14));
  jand g145(.dina(n211), .dinb(n184), .dout(n218));
  jxor g146(.dina(n218), .dinb(Gid15), .dout(God15));
  jand g147(.dina(n150), .dinb(n88), .dout(n220));
  jand g148(.dina(n181), .dinb(n159), .dout(n221));
  jxor g149(.dina(n116), .dinb(n102), .dout(n222));
  jand g150(.dina(n135), .dinb(n126), .dout(n223));
  jand g151(.dina(n223), .dinb(n222), .dout(n224));
  jxor g152(.dina(n135), .dinb(n126), .dout(n225));
  jand g153(.dina(n116), .dinb(n102), .dout(n226));
  jand g154(.dina(n226), .dinb(n225), .dout(n227));
  jor  g155(.dina(n227), .dinb(n224), .dout(n228));
  jand g156(.dina(n228), .dinb(n221), .dout(n229));
  jand g157(.dina(n229), .dinb(n220), .dout(n230));
  jand g158(.dina(n230), .dinb(n127), .dout(n231));
  jxor g159(.dina(n231), .dinb(Gid16), .dout(God16));
  jand g160(.dina(n230), .dinb(n198), .dout(n233));
  jxor g161(.dina(n233), .dinb(Gid17), .dout(God17));
  jand g162(.dina(n230), .dinb(n117), .dout(n235));
  jxor g163(.dina(n235), .dinb(Gid18), .dout(God18));
  jand g164(.dina(n230), .dinb(n187), .dout(n237));
  jxor g165(.dina(n237), .dinb(Gid19), .dout(God19));
  jand g166(.dina(n167), .dinb(n184), .dout(n239));
  jand g167(.dina(n228), .dinb(n239), .dout(n240));
  jand g168(.dina(n240), .dinb(n220), .dout(n241));
  jand g169(.dina(n241), .dinb(n127), .dout(n242));
  jxor g170(.dina(n242), .dinb(Gid20), .dout(God20));
  jand g171(.dina(n241), .dinb(n198), .dout(n244));
  jxor g172(.dina(n244), .dinb(Gid21), .dout(God21));
  jand g173(.dina(n241), .dinb(n117), .dout(n246));
  jxor g174(.dina(n246), .dinb(Gid22), .dout(God22));
  jand g175(.dina(n241), .dinb(n187), .dout(n248));
  jxor g176(.dina(n248), .dinb(Gid23), .dout(God23));
  jand g177(.dina(n178), .dinb(n87), .dout(n250));
  jand g178(.dina(n229), .dinb(n250), .dout(n251));
  jand g179(.dina(n251), .dinb(n127), .dout(n252));
  jxor g180(.dina(n252), .dinb(Gid24), .dout(God24));
  jand g181(.dina(n251), .dinb(n198), .dout(n254));
  jxor g182(.dina(n254), .dinb(Gid25), .dout(God25));
  jand g183(.dina(n251), .dinb(n117), .dout(n256));
  jxor g184(.dina(n256), .dinb(Gid26), .dout(God26));
  jand g185(.dina(n251), .dinb(n187), .dout(n258));
  jxor g186(.dina(n258), .dinb(Gid27), .dout(God27));
  jand g187(.dina(n240), .dinb(n250), .dout(n260));
  jand g188(.dina(n260), .dinb(n127), .dout(n261));
  jxor g189(.dina(n261), .dinb(Gid28), .dout(God28));
  jand g190(.dina(n260), .dinb(n198), .dout(n263));
  jxor g191(.dina(n263), .dinb(Gid29), .dout(God29));
  jand g192(.dina(n260), .dinb(n117), .dout(n265));
  jxor g193(.dina(n265), .dinb(Gid30), .dout(God30));
  jand g194(.dina(n260), .dinb(n187), .dout(n267));
  jxor g195(.dina(n267), .dinb(Gid31), .dout(God31));
endmodule


